#include "Projectile.h"

Projectile::Projectile() : velocity(0,0,0), dmg(0)
{
}
Projectile::~Projectile()
{
}

void Projectile::set_dmg(int dmg)
{
	this->dmg = dmg;
}
int Projectile::get_dmg()
{
	return dmg;
}

void Projectile::collision_response(Collidable* obj)
{
	//add projectile animation sprite
	if (obj->get_faction_side() == this->get_faction_side())
		return;
	this->active = false;
}