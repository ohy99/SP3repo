#include "OkayBow.h"

#include "Projectile.h"
#include "ObjectPoolManager.h"

OkayBow::OkayBow()
{
	this->set_attackspeed(5.f);
	this->damage = 3;
	this->force = 75.f;
	this->projectile_mass = 5.f;

	this->num_of_shots = 3;
	this->distance_btw_shots = 2.f;
}

OkayBow::~OkayBow()
{
}

void OkayBow::Discharge(Vector3 position, Vector3 dir)
{
	if (elapsedTime < timeBetweenShots)
		return;
	Vector3 right = dir.Cross(Vector3(0, 0, 1)).Normalize();
	Vector3 furthest_left = -right * distance_btw_shots * (num_of_shots / 2);
	for (int i = 0; i < num_of_shots; ++i)
	{
		Projectile* proj = ObjectPoolManager::GetInstance()->get_projectile(ObjectPoolManager::CANNONBALL);
		if (proj)
		{
			proj->pos = position + furthest_left + right * i * distance_btw_shots;
			proj->dir = dir;
			proj->velocity = dir * force;
			proj->set_dmg(this->get_damage());
			proj->set_faction_side(this->faction.side);
			proj->set_mass(projectile_mass);
		}
	}
	elapsedTime = 0.0;
}
