#include "Weapon.h"


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

// Initialise this instance to default values
void Weapon::Init(void)
{
	// Call the parent's Init method
	WeaponInfo::Init();

	//// The number of ammunition in a magazine for this weapon
	//magRounds = 30;
	//// The maximum number of ammunition for this magazine for this weapon
	//maxMagRounds = 30;
	//// The current total number of rounds currently carried by this player
	//totalRounds = 90;
	//// The max total number of rounds currently carried by this player
	//maxTotalRounds = 90;

	// The time between shots
	timeBetweenShots = 0.1;
	// The elapsed time (between shots)
	elapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;

	//reloadTime = 5.0;

}
