#include "Minion.h"

#include "Tower.h"

Minion::Minion()
{
}

Minion::~Minion()
{
}

void Minion::update(double dt)
{
	this->prev_pos = this->pos;
}

void Minion::collision_response(Collidable * obj)
{
	Minion* temp_minion = dynamic_cast<Minion*>(obj);
	Tower* temp_tower = dynamic_cast<Tower*>(obj);
	if (temp_minion)
		this->pos = prev_pos;
	else if (temp_tower)
		if (this->get_faction_side() != obj->get_faction_side())
			this->pos = prev_pos;
}
