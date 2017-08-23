#pragma once

#include "Vector3.h"
#include "Faction.h"

class WeaponInfo
{
public:
	WeaponInfo();
	virtual ~WeaponInfo();
protected:
	// The time between shots in milliseconds
	// The elapsed time (between shots) in milliseconds
	double elapsedTime;
	double timeBetweenShots;
	// Boolean flag to indicate if weapon can fire now
	bool bFire;
	int damage;
	float force;
	float projectile_mass;
	Faction faction;
public:
	// Set the time between shots
	virtual void SetTimeBetweenShots(const double timeBetweenShots);
	// Set the firing rate in rounds per min
	virtual void SetFiringRate(const int firingRate);
	// Set the firing flag
	virtual void SetCanFire(const bool bFire);

	// Get the time between shots
	virtual double GetTimeBetweenShots(void) const;
	// Get the firing rate
	virtual int GetFiringRate(void) const;
	// Get the firing flag
	virtual bool GetCanFire(void) const;

	// Initialise this instance to default values
	virtual void Init(void);
	// Update the elapsed time
	void Update(const double dt);
	// Discharge this weapon
	virtual void Discharge(Vector3 position, Vector3 dir);

	void set_damage(int dmg);
	int get_damage();

	Faction::FACTION_SIDE get_faction_side();
	void set_faction_side(Faction::FACTION_SIDE side);

	void set_attackspeed(float attspd);
	float get_attackspeed();
};
