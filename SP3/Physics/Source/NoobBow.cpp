#include "NoobBow.h"

#include "MeshList.h"
#include "Projectile.h"
#include "ObjectPoolManager.h"

NoobBow::NoobBow()
{
	this->set_attackspeed(2.f);
	this->damage = 30;
	this->force = 40.f;
	this->projectile_mass = 2.f;

	this->mesh = MeshList::GetInstance()->getMesh("NOOBBOW");
}

NoobBow::~NoobBow()
{
}

void NoobBow::Discharge(Vector3 position, Vector3 dir)
{
	if (elapsedTime < timeBetweenShots)
		return;

	Projectile* proj = ObjectPoolManager::GetInstance()->get_projectile(ObjectPoolManager::ARROWS);
	if (proj)
	{
		proj->pos = position;
		proj->dir = dir;
		proj->velocity = dir * force;
		proj->set_dmg(this->get_damage());
		proj->set_faction_side(this->faction.side);
		proj->set_mass(projectile_mass);
	}

	elapsedTime = 0.0;

}