#include "MinionManager.h"
#include "Minion.h"
#include "CharacterInfo.h"
#include "MeshList.h"
#include "RenderManager.h"

MinionManager::MinionManager()
{
	for (int i = 0; i < 100; ++i)
	{
		Minion* temp = new Minion;
		temp->scale.Set(5, 5, 5);
		temp->set_collision_type(Collision::AABB);
		temp->update_collider();
		temp->mesh = MeshList::GetInstance()->getMesh("CANNON");
		minions.push_back(temp);
		RenderManager::GetInstance()->attach_renderable(temp, 1);
	}
}

MinionManager::~MinionManager()
{
	for each (auto &m in minions)
		delete m;
	minions.clear();
}

void MinionManager::update(double dt)
{
	for (std::list<Minion*>::iterator player_minion_iter = player_minions.begin(); player_minion_iter != player_minions.end(); )
	{
		if (!(*player_minion_iter)->active)//remove from list
		{
			player_minions.erase(player_minion_iter);
			continue;
		}

		//go right
		Minion* pm = (*player_minion_iter);

		//update
		pm->update(dt);

		//move
		pm->pos += Vector3(10, 0, 0) * (float)dt;

		++player_minion_iter;
	}


	for (std::list<Minion*>::iterator enemy_minion_iter = enemy_minions.begin(); enemy_minion_iter != enemy_minions.end(); )
	{
		if (!(*enemy_minion_iter)->active)//remove from list
		{
			enemy_minions.erase(enemy_minion_iter);
			continue;
		}

		//go left
		Minion* em = (*enemy_minion_iter);

		//update
		em->update(dt);

		//move
		em->pos += Vector3(-10, 0, 0) * (float)dt;

		++enemy_minion_iter;
	}
}

void MinionManager::spawn_minion(bool is_player_side, MINIONTYPE type)
{
	Minion* temp_minion = get_inactive_minion();
	if (is_player_side)
	{
		//check if any existing minions are in tower. if there is, dont spawn to avoid collision
		for each (auto& pm in player_minions)
		{
			temp_minion->pos = Vector3(5, 12.5, 0);
			if (temp_minion->collider.isCollide(pm->collider))
				return;
		}
	}
	else
	{
		for each (auto& em in enemy_minions)
		{
			temp_minion->pos = Vector3(50, 12.5, 0);
			if (temp_minion->collider.isCollide(em->collider))
				return;
		}
	}
	switch (type)
	{
	case MINIONTYPE::MELEE:
		temp_minion->active = true;
		temp_minion->reset();
		break;
	case MINIONTYPE::RANGE:
		break;
	}
	if (is_player_side)
	{
		temp_minion->pos = Vector3(5, 12.5, 0);
		temp_minion->set_faction_side(Faction::FACTION_SIDE::PLAYER);
		player_minions.push_back(temp_minion);
	}
	else
	{
		temp_minion->pos = Vector3(50, 12.5, 0);
		temp_minion->set_faction_side(Faction::FACTION_SIDE::ENEMY);
		enemy_minions.push_back(temp_minion);
	}
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