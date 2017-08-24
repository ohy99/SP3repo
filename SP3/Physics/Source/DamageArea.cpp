#include "DamageArea.h"

#include "Minion.h"
#include "Tower.h"

DamageArea::DamageArea() : active_duration(0.0), active_elapsed(0.0), damage(0), hit_once(true), hits_per_sec(0.f)
{
}

DamageArea::~DamageArea()
{
	collided.clear();
}

void DamageArea::update(double dt)
{
	if (!this->active)
		return;

	active_elapsed += dt;

	if (active_elapsed >= active_duration)
	{
		this->active = false;
		active_elapsed = 0.0;
		collided.clear();
	}
}

void DamageArea::collision_response(Collidable * obj)
{
	//damage area will be responsible for dealing dmg
	if (hit_once)
	{
		for each (auto c in collided)
			if (c == obj)//hit once alr
				return;
	}
	

	Minion* temp_minion = dynamic_cast<Minion*>(obj);
	Tower* temp_tower = dynamic_cast<Tower*>(obj);
	if (this->get_faction_side() == obj->get_faction_side())
		return;
	if (temp_minion)
	{
		//if is minion
		temp_minion->get_hit(this->get_damage());
		collided.push_back(obj);
	}
	else if (temp_tower)
	{
		temp_tower->get_hit(this->get_damage());
		collided.push_back(obj);
	}
}

void DamageArea::set_damage(int dmg, bool once_only, float hits_per_sec)
{
	this->damage = dmg;
	this->hit_once = once_only;
	this->hits_per_sec = hits_per_sec;
}

int DamageArea::get_damage()
{
	return this->damage;
}

void DamageArea::set_duration(double duration)
{
	this->active_duration = duration;
}


