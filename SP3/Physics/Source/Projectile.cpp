#include "Projectile.h"

#include "Minion.h"
#include "Tower.h"

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
	Minion* temp_minion = dynamic_cast<Minion*>(obj);
	Tower* temp_tower = dynamic_cast<Tower*>(obj);

	if (temp_minion)
	{
		temp_minion->get_hit(this->get_dmg());
		this->active = false;
	}
	else if (temp_tower)
	{
		temp_tower->get_hit(this->get_dmg());
		this->active = false;
	}
	//else if (temp_tower)

	//if proj - proj, ignore

}