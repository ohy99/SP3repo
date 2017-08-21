#include "MinionManager.h"
#include "Minion.h"
#include "CharacterInfo.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "DamageArea.h"
#include "Collidable.h"
#include "TowerManager.h"
#include "Tower.h"

MinionManager::MinionManager()
{
	init_info();

	for (int i = 0; i < 100; ++i)
	{
		Minion* temp = new Minion;
		temp->scale.Set(5, 5, 5);
		temp->set_collision_type(Collision::AABB);
		temp->update_collider();
		temp->mesh = MeshList::GetInstance()->getMesh("GREENDRAGON");
		temp->init_info(100, 10, 1, 6.f, 5);
		minions.push_back(temp);
		RenderManager::GetInstance()->attach_renderable(temp, 1);
	}

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
}

void MinionManager::spawn_minion(bool is_player_side, MinionInfo::MINION_TYPE type)
{
	Minion* temp_minion = get_inactive_minion();
	if (is_player_side)
	{
		//check if any existing minions are in tower. if there is, dont spawn to avoid collision
		for each (auto& pm in player_minions)
		{
			temp_minion->pos = TowerManager::GetInstance()->player->pos;
			temp_minion->pos.y -= TowerManager::GetInstance()->player->scale.y * 0.275f;
			Minion* temp_check = dynamic_cast<Minion*>(pm);
			if (temp_check)
				if (temp_minion->collider.isCollide(dynamic_cast<Minion*>(pm)->collider))
					return;
		}
	}
	else
	{
		for each (auto& em in enemy_minions)
		{
			temp_minion->pos = TowerManager::GetInstance()->enemy->pos;
			temp_minion->pos.y -= TowerManager::GetInstance()->enemy->scale.y * 0.275f;
			Minion* temp_check = dynamic_cast<Minion*>(em);
			if (temp_check)
				if (temp_minion->collider.isCollide(temp_check->collider))
					return;
		}
	}
	temp_minion->minion_type = type;
	temp_minion->active = true;
	temp_minion->reset();
	init_info(temp_minion, type);

	if (is_player_side)
	{
		temp_minion->pos = TowerManager::GetInstance()->player->pos;
		temp_minion->pos.y -= TowerManager::GetInstance()->player->scale.y * 0.275f;
		temp_minion->set_faction_side(Faction::FACTION_SIDE::PLAYER);
		temp_minion->attach_list_of_targets(&enemy_minions);
		temp_minion->set_walking_direction(this->player_movement_direction);
		player_minions.push_back(temp_minion);
	}
	else
	{
		temp_minion->pos = TowerManager::GetInstance()->enemy->pos;
		temp_minion->pos.y -= TowerManager::GetInstance()->enemy->scale.y * 0.275f;
		temp_minion->set_faction_side(Faction::FACTION_SIDE::ENEMY);
		temp_minion->attach_list_of_targets(&player_minions);
		temp_minion->set_walking_direction(this->enemy_movement_direction);
		enemy_minions.push_back(temp_minion);
	}
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

Minion* MinionManager::get_inactive_minion()
{
	for each (auto &m in minions)
	{
		if (m->active)
			continue;
		return m;
	}
	return nullptr;
}


void MinionManager::init_info()
{
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].max_hp = 100;
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].dmg = 10;
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].att_spd = 1.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].att_range = 1.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_MELEE].move_spd = 5.f;

	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].max_hp = 80;
	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].dmg = 8;
	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].att_spd = 1.5f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].att_range = 3.f;
	minion_info[MinionInfo::MINION_TYPE::BASIC_RANGE].move_spd = 10.f;
}

void MinionManager::init_info(Minion * minion, MinionInfo::MINION_TYPE type)
{
	minion->init_info(minion_info[type].max_hp,
		minion_info[type].dmg,
		minion_info[type].att_spd,
		minion_info[type].att_range,
		minion_info[type].move_spd);
}

MinionManager::MINION_INFO::MINION_INFO() : max_hp(0), dmg(0), att_spd(0.f), att_range(0.f), move_spd(0.f)
{
}
