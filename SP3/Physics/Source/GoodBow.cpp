#include "GoodBow.h"

#include "Projectile.h"
#include "ObjectPoolManager.h"
#include "ProjectileRainArrow.h"

GoodBow::GoodBow()
{
	this->set_attackspeed(2.f);
	this->damage = 40;
	this->force = 30.f;
	this->projectile_mass = 2.f;

	this->num_of_splits = 3.f;
	this->spliting_time = 1.f;
	this->percentage_force_transfered = 0.75f;
	this->degree_apart = 20.f;
	this->percentage_damage_transfered = 2.f;
}

GoodBow::~GoodBow()
{
}

void GoodBow::Discharge(Vector3 position, Vector3 dir)
{
	if (bFire)
	{
		Projectile* proj = ObjectPoolManager::GetInstance()->get_projectile(ObjectPoolManager::CANNONBALL, 1);
		if (proj)
		{
			proj->pos = position;
			proj->dir = dir;
			proj->velocity = dir * force;
			proj->set_dmg(this->get_damage());
			proj->set_faction_side(this->faction.side);
			proj->set_mass(projectile_mass);

			ProjectileRainArrow* pra = dynamic_cast<ProjectileRainArrow*>(proj);
			pra->set_degree_apart(degree_apart);
			pra->set_num_of_splits(num_of_splits);
			pra->set_percentage_force_transfered(percentage_force_transfered);
			pra->set_spliting_time(spliting_time);
			pra->set_total_percentage_split_damage(percentage_damage_transfered);
		}
		bFire = false;
	}
}