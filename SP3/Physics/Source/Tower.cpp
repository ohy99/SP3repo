#include "Tower.h"

#include "HpBar.h"
#include "MyMath.h"
#include "TowerManager.h"

Tower::Tower()
{
	this->active = true;
}

Tower::Tower(Faction::FACTION_SIDE side)
{
	this->active = true;
	this->set_faction_side(side);

	this->maxhealth = 1000;
	this->health = this->maxhealth;

	if (side == Faction::FACTION_SIDE::PLAYER)
		TowerManager::GetInstance()->player = this;
	else
		TowerManager::GetInstance()->enemy = this;
}

Tower::~Tower()
{
}

void Tower::render()
{
	GameObject::render();

	HpBar* hp = HpBar::GetInstance();
	hp->pos = this->pos;
	hp->pos.y += this->scale.y * 0.55f;
	hp->scale.Set(this->scale.x, 1);
	hp->render((float)this->health / (float)this->maxhealth);
}

void Tower::get_hit(int dmg)
{
	this->health = Math::Clamp(health - dmg, 0, maxhealth);
}