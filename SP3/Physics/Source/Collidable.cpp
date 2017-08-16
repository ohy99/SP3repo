#include "Collidable.h"

Collidable::Collidable()
{
}

Collidable::~Collidable()
{
}

void Collidable::set_faction_side(Faction::FACTION_SIDE side)
{
	this->faction.side = side;
}
Faction::FACTION_SIDE Collidable::get_faction_side()
{
	return this->faction.side;
}

void Collidable::collision_response(Collidable * obj)
{
	return;
}
