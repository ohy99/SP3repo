#include "WeaponInfo.h"
//#include "../Projectile/Projectile.h"

#include <iostream>
using namespace std;
#include "ObjectPoolManager.h"
#include "Projectile.h"

WeaponInfo::WeaponInfo()
	: timeBetweenShots(0.5)
	, elapsedTime(0.0)
	, bFire(true)
	, damage(0)
	, force(1.f)
	, projectile_mass(1.f)
{
}


WeaponInfo::~WeaponInfo()
{
}

// Set the time between shots
void WeaponInfo::SetTimeBetweenShots(const double timeBetweenShots)
{
	this->timeBetweenShots = timeBetweenShots;
}

// Set the firing rate in rounds per min
void WeaponInfo::SetFiringRate(const int firingRate)
{
	timeBetweenShots = 60.0 / (double)firingRate;	// 60 seconds divided by firing rate
}

// Set the firing flag
void WeaponInfo::SetCanFire(const bool bFire)
{
	this->bFire = bFire;
}

// Get the time between shots
double WeaponInfo::GetTimeBetweenShots(void) const
{
	return timeBetweenShots;
}

// Get the firing rate
int WeaponInfo::GetFiringRate(void) const
{
	return (int)(60.0 / timeBetweenShots);	// 60 seconds divided by timeBetweenShots
}

// Get the firing flag
bool WeaponInfo::GetCanFire(void) const
{
	return bFire;
}

// Initialise this instance to default values
void WeaponInfo::Init(void)
{
	// The time between shots
	timeBetweenShots = 0.5;
	// The elapsed time (between shots)
	elapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;
	force = 20;
}

// Update the elapsed time
void WeaponInfo::Update(const double dt)
{
	elapsedTime += dt;
	if (elapsedTime > timeBetweenShots)
	{
		bFire = true;
		elapsedTime = 0.0;
	}
}

// Discharge this weapon
void WeaponInfo::Discharge(Vector3 position, Vector3 dir)
{
	if (bFire)
	{
		Projectile* proj = ObjectPoolManager::GetInstance()->get_projectile(ObjectPoolManager::CANNONBALL);
		if (proj)
		{
			proj->pos = position;
			proj->dir = dir;
			proj->velocity = dir * force;
			proj->set_dmg(this->get_damage());
			proj->set_faction_side(this->faction.side);
			proj->set_mass(projectile_mass);
		}
		bFire = false;
	}
}

void WeaponInfo::set_faction_side(Faction::FACTION_SIDE side)
{
	this->faction.side = side;
}
void WeaponInfo::set_attackspeed(float attspd)
{
	this->timeBetweenShots = 1.f / attspd;
}
float WeaponInfo::get_attackspeed()
{
	return 1.f / timeBetweenShots;
}
Faction::FACTION_SIDE WeaponInfo::get_faction_side()
{
	return this->faction.side;
}

void WeaponInfo::set_damage(int dmg)
{
	this->damage = dmg;
}

int WeaponInfo::get_damage()
{
	return this->damage;
}

