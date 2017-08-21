#include "DamageArea.h"

#include "Minion.h"

DamageArea::DamageArea() : active_duration(0.0), active_elapsed(0.0), damage(0)
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
	for each (auto c in collided)
		if (c == obj)//hit once alr
			return;

	Minion* temp_minion = dynamic_cast<Minion*>(obj);
	if (temp_minion)
	{
		//if is minion
		temp_minion->get_hit(this->get_damage());
		collided.push_back(obj);
	}
}

void DamageArea::set_damage(int dmg)
{
	this->damage = dmg;
}

int DamageArea::get_damage()
{
	return this->damage;
}

void DamageArea::set_duration(double duration)
{
	this->active_duration = duration;
}


