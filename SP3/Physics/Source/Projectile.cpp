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