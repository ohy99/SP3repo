#include "Tower.h"

Tower::Tower()
{
	this->active = true;
}

Tower::Tower(Faction::FACTION_SIDE side)
{
	this->active = true;
	this->set_faction_side(side);
}

Tower::~Tower()
{
}