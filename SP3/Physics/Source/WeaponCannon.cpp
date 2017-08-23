#include "WeaponCannon.h"

Cannon::Cannon()
{
	this->set_attackspeed(0.8f);
	this->damage = 50;
	this->force = 50.f;
	this->projectile_mass = 5.f;
}

Cannon::~Cannon()
{
}
