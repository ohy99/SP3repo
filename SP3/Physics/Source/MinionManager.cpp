#include "MinionManager.h"
#include "Minion.h"
#include "CharacterInfo.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "DamageArea.h"
#include "Collidable.h"
#include "TowerManager.h"
#include "Tower.h"
#include "SpellManager.h"
#include "MinionMelee.h"
#include "MinionRange.h"
#include "MinionSiege.h"
#include "MinionHealer.h"
#include "MinionAir.h"

//to fix:
//have a attack timer
//so the animation can play

MinionManager::MinionManager()
{
	init_info();
	minion_scale = 5.f;
	init_pool();

	player_movement_direction.Set(1, 0, 0);
	enemy_movement_direction.Set(-1, 0, 0);

	for (int i = 0; i < 50; ++i)
	{
		DamageArea* temp = new DamageArea;
		temp->scale.Set(2.5f, 2.5f, 2.5f);
		temp->set_collision_type(Collision::AABB);
		temp->update_collider();
		temp->mesh = MeshList::GetInstance()->getMesh("CANNONBALL");
		damage_sprite.push_back(temp);
		RenderManager::GetInstance()->attach_renderable(temp, 2);
	}

	player_minions.push_back(TowerManager::GetInstance()->player);
	enemy_minions.push_back(TowerManager::GetInstance()->enemy);

	ground_spawn_point_relative_to_tower.Set(0, -TowerManager::GetInstance()->player->scale.y * 0.275f, 0);
	air_spawn_point_relative_to_tower.Set(0, TowerManager::GetInstance()->enemy->scale.y * 0.5f, 0);
}

MinionManager::~MinionManager()
{
	for each (auto &m in minions)
		delete m;
	minions.clear();

	for each (auto &ds in damage_sprite)
		delete ds;
	damage_sprite.clear();
}

void MinionManager::update(double dt)
{
	for (std::list<Collidable*>::iterator player_minion_iter = player_minions.begin(); player_minion_iter != player_minions.end(); )
	{
		if (!(*player_minion_iter)->active)//remove from list
		{
			player_minion_iter = player_minions.erase(player_minion_iter);
			continue;
		}

		//update
		(*player_minion_iter)->update(dt);

		++player_minion_iter;
	}

	if (SpellManager::GetInstance()->isFreezeActive())
		return;

	for (std::list<Collidable*>::iterator enemy_minion_iter = enemy_minions.begin(); enemy_minion_iter != enemy_minions.end(); )
	{
		if (!(*enemy_minion_iter)->active)//remove from list
		{
			enemy_minion_iter = enemy_minions.erase(enemy_minion_iter);
			continue;
		}

		//update
		(*enemy_minion_iter)->update(dt);

		++enemy_minion_iter;
	}

	//update temporary dmg sprite
	for each (auto & ds in damage_sprite)
	{
		if (ds->active)
			ds->update(dt);
	}


	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('0') && !dakeypressed)
		{
			if (MinionManager::GetInstance()->spawn_minion(false, MinionInfo::MINION_TYPE::BASIC_AIR))
				dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('0') && dakeypressed)
		{
			dakeypressed = false;
		}
	}
}

bool MinionManager::spawn_minion(bool is_player_side, MinionInfo::MINION_TYPE type)
{
	Minion* temp_minion = get_inactive_minion(type);
	if (is_player_side)
	{
		//check if any existing minions are in tower. if there is, dont spawn to avoid collision
		for each (auto& pm in player_minions)
		{
			temp_minion->pos = TowerManager::GetInstance()->player->pos;
			if (temp_minion->is_air_unit)
				temp_minion->pos += air_spawn_point_relative_to_tower;
			else
				temp_minion->pos += ground_spawn_point_relative_to_tower;
			Minion* temp_check = dynamic_cast<Minion*>(pm);
			if (temp_check)
				if (temp_minion->collider.isCollide(dynamic_cast<Minion*>(pm)->collider))
					return false;
		}
	}
	else
	{
		for each (auto& em in enemy_minions)
		{
			temp_minion->pos = TowerManager::GetInstance()->enemy->pos;
			if (temp_minion->is_air_unit)
				temp_minion->pos += air_spawn_point_relative_to_tower;
			else
				temp_minion->pos += ground_spawn_point_relative_to_tower;
			Minion* temp_check = dynamic_cast<Minion*>(em);
			if (temp_check)
				if (temp_minion->collider.isCollide(temp_check->collider))
					return false;
		}
	}
	//temp_minion->minion_type = type;
	temp_minion->active = true;
	//std::cout << "ENTER" << std::endl;
	temp_minion->reset();
	init_info(temp_minion, type);
	temp_minion->heal_elapsed = 0.0;

	if (is_player_side)
	{
		temp_minion->pos = TowerManager::GetInstance()->player->pos;
		temp_minion->pos += ground_spawn_point_relative_to_tower;
		temp_minion->set_faction_side(Faction::FACTION_SIDE::PLAYER);
		temp_minion->attach_list_of_targets(&enemy_minions);
		temp_minion->attach_list_of_ally(&player_minions);
		temp_minion->set_walking_direction(this->player_movement_direction);
		player_minions.push_back(temp_minion);

		//lastly check if it is a healer. if it is then let it fly
		if (temp_minion->is_air_unit) {
			temp_minion->pos = TowerManager::GetInstance()->player->pos;
			temp_minion->pos += air_spawn_point_relative_to_tower;
		}
	}
	else
	{
		temp_minion->pos = TowerManager::GetInstance()->enemy->pos;
		temp_minion->pos += ground_spawn_point_relative_to_tower;
		temp_minion->set_faction_side(Faction::FACTION_SIDE::ENEMY);
		temp_minion->attach_list_of_targets(&player_minions);
		temp_minion->attach_list_of_ally(&enemy_minions);
		temp_minion->set_walking_direction(this->enemy_movement_direction);
		enemy_minions.push_back(temp_minion);
		if (temp_minion->is_air_unit)
		{
			temp_minion->pos = TowerManager::GetInstance()->enemy->pos;
			temp_minion->pos += air_spawn_point_relative_to_tower;
		}
	}

	return true;
}

DamageArea * MinionManager::request_inactive_collidable(MinionInfo::MINION_TYPE type)
{
	switch (type)
	{
	case MinionInfo::MINION_TYPE::BASIC_MELEE:
		for each (auto &d in damage_sprite)
		{
			if (d->active)
				continue;
			return d;
		}
	}
	return nullptr;
}

std::list<Collidable*>* MinionManager::get_player_minion_list()
{
	return &this->player_minions;
}

std::list<Collidable*>* MinionManager::get_enemy_minion_list()
{
	return &this->enemy_minions;
}

float MinionManager::get_move_spd_of_type(MinionInfo::MINION_TYPE type)
{
	return minion_info[type].move_spd;
}

float MinionManager::get_minion_scale()
{
	return minion_scale;
}

Minion* MinionManager::get_inactive_minion(MinionInfo::MINION_TYPE type)
{
	for each (auto &m in minions)
	{
		if (m->active)
			continue;
		if (m->minion_type == type)
			return m;
	}
	return nullptr;
}


void MinionManager::init_info(float level)
{
	//att range is the number of half scales. 3.f is 2unit range
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].max_hp = 150 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].dmg = 12 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].att_spd = 1.f * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].att_range = 1.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].move_spd = 5.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].cast_time = 2.f;

	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].max_hp = 120 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].dmg = 15 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].att_spd = 1.5f * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].att_range = 3.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].move_spd = 10.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].cast_time = 1.f;

	minion_info[MinionInfo::MINION_TYPE::BASIC_SIEGE].max_hp = 100 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_SIEGE].dmg = 35 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_SIEGE].att_spd = 0.5f * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_SIEGE].att_range = 5.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_SIEGE].move_spd = 3.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_SIEGE].cast_time = 3.f;

	minion_info[MinionInfo::MINION_TYPE::BASIC_HEALER].max_hp = 60 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_HEALER].dmg = 30 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_HEALER].att_spd = 1.f * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_HEALER].att_range = 10.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_HEALER].move_spd = 7.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_HEALER].cast_time = 3.f;

	minion_info[MinionInfo::MINION_TYPE::BASIC_AIR].max_hp = 80 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_AIR].dmg = 9 * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_AIR].att_spd = 3.f * ((1.f + level) / 2.f);
	minion_info[MinionInfo::MINION_TYPE::BASIC_AIR].att_range = 8.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_AIR].move_spd = 5.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_AIR].cast_time = 0.6f;

	for (int i = 0; i < MinionInfo::MINION_TYPE::MINION_TYPE_COUNT; ++i)
		default_minion_info[i] = minion_info[i];

}

void MinionManager::init_pool()
{
	for (int i = 0; i < 20; ++i)
	{
		Minion* temp = new MinionMelee;
		temp->scale.Set(minion_scale, minion_scale, 5);
		temp->set_collision_type(Collision::AABB);
		temp->update_collider();
		temp->init_info(100, 10, 1, 6.f, 5);
		minions.push_back(temp);
		RenderManager::GetInstance()->attach_renderable(temp, 1);
	}

	for (int i = 0; i < 20; ++i)
	{
		Minion* temp = new MinionRange;
		temp->scale.Set(minion_scale, minion_scale, 5);
		temp->set_collision_type(Collision::AABB);
		temp->update_collider();
		temp->init_info(100, 10, 1, 6.f, 5);
		minions.push_back(temp);
		RenderManager::GetInstance()->attach_renderable(temp, 1);
	}

	for (int i = 0; i < 20; ++i)
	{
		Minion* temp = new MinionSiege;
		temp->scale.Set(minion_scale, minion_scale, 5);
		temp->set_collision_type(Collision::AABB);
		temp->update_collider();
		temp->init_info(100, 10, 1, 6.f, 5);
		minions.push_back(temp);
		RenderManager::GetInstance()->attach_renderable(temp, 1);
	}

	for (int i = 0; i < 20; ++i)
	{
		Minion* temp = new MinionHealer;
		temp->scale.Set(minion_scale, minion_scale, 5);
		temp->set_collision_type(Collision::AABB);
		temp->update_collider();
		temp->init_info(100, 10, 1, 6.f, 5);
		minions.push_back(temp);
		RenderManager::GetInstance()->attach_renderable(temp, 1);
	}

	for (int i = 0; i < 20; ++i)
	{
		Minion* temp = new MinionAir;
		temp->scale.Set(minion_scale, minion_scale, 5);
		temp->set_collision_type(Collision::AABB);
		temp->update_collider();
		//temp->init_info(100, 10, 1, 6.f, 5);
		minions.push_back(temp);
		RenderManager::GetInstance()->attach_renderable(temp, 1);
	}
}

void MinionManager::init_info(Minion * minion, MinionInfo::MINION_TYPE type)
{
	minion->init_info(minion_info[type].max_hp,
		minion_info[type].dmg,
		minion_info[type].att_spd,
		minion_info[type].att_range,
		minion_info[type].move_spd,
		minion_info[type].cast_time);
}

void MinionManager::adjust_minions_move_speed(float percentage_of_default)
{
	for (int i = 0; i < MinionInfo::MINION_TYPE::MINION_TYPE_COUNT; ++i)
		minion_info[i].move_spd = default_minion_info[i].move_spd * percentage_of_default/100;
}

void MinionManager::reset_minions_move_speed()
{
	for (int i = 0; i < MinionInfo::MINION_TYPE::MINION_TYPE_COUNT; ++i)
		minion_info[i].move_spd = default_minion_info[i].move_spd;
}

void MinionManager::adjust_minions_dmg(float percentage_of_default)
{
	for (int i = 0; i < MinionInfo::MINION_TYPE::MINION_TYPE_COUNT; ++i)
		minion_info[i].dmg = default_minion_info[i].dmg * percentage_of_default/100;
}

void MinionManager::reset_minions_dmg()
{
	for (int i = 0; i < MinionInfo::MINION_TYPE::MINION_TYPE_COUNT; ++i)
		minion_info[i].dmg = default_minion_info[i].dmg;
}

void MinionManager::adjust_minions_att_spd(float percentage_of_default)
{
	for (int i = 0; i < MinionInfo::MINION_TYPE::MINION_TYPE_COUNT; ++i)
	{
		minion_info[i].att_spd = default_minion_info[i].att_spd * percentage_of_default/100;
		minion_info[i].cast_time = default_minion_info[i].cast_time * percentage_of_default / 100;
	}
}

void MinionManager::reset_minions_att_spd()
{
	for (int i = 0; i < MinionInfo::MINION_TYPE::MINION_TYPE_COUNT; ++i)
	{
		minion_info[i].att_spd = default_minion_info[i].att_spd;
		minion_info[i].cast_time = default_minion_info[i].cast_time;
	}
}

void MinionManager::adjust_minions_hp(float percentage_of_default)
{
	for (int i = 0; i < MinionInfo::MINION_TYPE::MINION_TYPE_COUNT; ++i)
		minion_info[i].max_hp = default_minion_info[i].max_hp * percentage_of_default/100;
}

void MinionManager::reset_minions_hp()
{
	for (int i = 0; i < MinionInfo::MINION_TYPE::MINION_TYPE_COUNT; ++i)
		minion_info[i].max_hp = default_minion_info[i].max_hp;
}

void MinionManager::attach_character(Character * character)
{
	this->characterinfo = character;
	minions.at(0)->attach_character(this->characterinfo);//static ma
}

MinionManager::MINION_INFO MinionManager::get_info(MinionInfo::MINION_TYPE type)
{
	return minion_info[type];
}

MinionManager::MINION_INFO MinionManager::get_default_info(MinionInfo::MINION_TYPE type)
{
	return default_minion_info[type];
}


MinionManager::MINION_INFO::MINION_INFO() : max_hp(0), dmg(0), att_spd(0.f), att_range(0.f),
	move_spd(0.f), cast_time(0.0)
{
}


void MinionManager::adjust_minion_difficulty(float difficulty)
{
	init_info(difficulty);
}