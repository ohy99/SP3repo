#include "TowerManager.h"

#include "Tower.h"

void TowerManager::set_enemy_dmg_reduction(float value)
{
	this->enemy->set_dmg_reduction(value);
}

void TowerManager::set_player_dmg_reduction(float value)
{
	this->player->set_dmg_reduction(value);
}

TowerManager::TowerManager()
{
}

TowerManager::~TowerManager()
{
}

void TowerManager::update(double dt)
{
	
	enemy->update(dt);
	player->update(dt);

}