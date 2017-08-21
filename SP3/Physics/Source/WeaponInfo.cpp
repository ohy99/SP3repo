#include "WeaponInfo.h"
//#include "../Projectile/Projectile.h"

#include <iostream>
using namespace std;
#include "ObjectPoolManager.h"
#include "Projectile.h"

WeaponInfo::WeaponInfo()
	//: magRounds(1)
	//, maxMagRounds(1)
	//, totalRounds(8)
	//, maxTotalRounds(8)
	: timeBetweenShots(0.5)
	, elapsedTime(0.0)
	, bFire(true)
	//, reloadTime(2.0)
{
}


WeaponInfo::~WeaponInfo()
{
}

//// Set the number of ammunition in the magazine for this player
//void CWeaponInfo::SetMagRound(const int magRounds)
//{
//	this->magRounds = magRounds;
//}
//
//// Set the maximum number of ammunition in the magazine for this weapon
//void CWeaponInfo::SetMaxMagRound(const int magRounds)
//{
//	this->magRounds = magRounds;
//}
//
//// The current total number of rounds currently carried by this player
//void CWeaponInfo::SetTotalRound(const int totalRounds)
//{
//	this->totalRounds = totalRounds;
//}
//
//// The max total number of rounds currently carried by this player
//void CWeaponInfo::SetMaxTotalRound(const int maxTotalRounds)
//{
//	this->maxTotalRounds = maxTotalRounds;
//}
//
//
//// Get the number of ammunition in the magazine for this player
//int CWeaponInfo::GetMagRound(void) const
//{
//	return magRounds;
//}
//
//// Get the maximum number of ammunition in the magazine for this weapon
//int CWeaponInfo::GetMaxMagRound(void) const
//{
//	return maxMagRounds;
//}
//
//// Get the current total number of rounds currently carried by this player
//int CWeaponInfo::GetTotalRound(void) const
//{
//	return totalRounds;
//}
//
//// Get the max total number of rounds currently carried by this player
//int CWeaponInfo::GetMaxTotalRound(void) const
//{
//	return maxTotalRounds;
//}

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
	//// The number of ammunition in a magazine for this weapon
	//magRounds = 30;
	//// The maximum number of ammunition for this magazine for this weapon
	//maxMagRounds = 30;
	//// The current total number of rounds currently carried by this player
	//totalRounds = 90;
	//// The max total number of rounds currently carried by this player
	//maxTotalRounds = 90;

	// The time between shots
	timeBetweenShots = 0.5;
	// The elapsed time (between shots)
	elapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;

	//reloadTime = 0.0;
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
		// If there is still ammo in the magazine, then fire
		//if (magRounds > 0)
		//{
			// Create a projectile with a cube mesh. Its position and direction is same as the player.
			// It will last for 3.0 seconds and travel at 500 units per second
			//CProjectile* aProjectile = Create::Projectile("bullet", 
			//												position, 
			//												(target - position).Normalized(), 
			//												2.0f, 
			//												500.0f,
			//												_source);
		Projectile* proj = ObjectPoolManager::GetInstance()->get_projectile(ObjectPoolManager::CANNONBALL);
		if (proj)
		{
			proj->pos = position;
			proj->dir = dir;
			proj->velocity = dir * 20;
			proj->set_dmg(this->get_damage());
			proj->set_faction_side(this->faction.side);
		}
			//aProjectile->SetCollider(true);
			//aProjectile->SetAABB(Vector3(0.5f, 0.5f, 0.5f), Vector3(-0.5f, -0.5f, -0.5f));
			bFire = false;
			//magRounds--;
		//}
	}
}

// Reload this weapon
//void CWeaponInfo::Reload(const double dt)
//{
//	if (magRounds < maxMagRounds)
//	{
//		if (maxMagRounds - magRounds <= totalRounds)
//		{
//			totalRounds -= maxMagRounds - magRounds;
//			magRounds = maxMagRounds;
//		}
//		else
//		{
//			magRounds += totalRounds;
//			totalRounds = 0;
//		}
//	}
//	
//}

//// Add rounds
//void CWeaponInfo::AddRounds(const int newRounds)
//{
//	if (totalRounds + newRounds > maxTotalRounds)
//		totalRounds = maxTotalRounds;
//	else
//		totalRounds += newRounds;
//}

//// Print Self
//void CWeaponInfo::PrintSelf(void)
//{
//	cout << "CWeaponInfo::PrintSelf()" << endl;
//	cout << "========================" << endl;
//	cout << "magRounds\t\t:\t" << magRounds << endl;
//	cout << "maxMagRounds\t\t:\t" << maxMagRounds << endl;
//	cout << "totalRounds\t\t:\t" << totalRounds << endl;
//	cout << "maxTotalRounds\t\t:\t" << maxTotalRounds << endl;
//	cout << "timeBetweenShots\t:\t" << timeBetweenShots << endl;
//	cout << "elapsedTime\t\t:\t" << elapsedTime << endl;
//	cout << "bFire\t\t:\t" << bFire << endl;
//}



void WeaponInfo::set_faction_side(Faction::FACTION_SIDE side)
{
	this->faction.side = side;
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

