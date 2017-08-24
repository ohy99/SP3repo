#ifndef GOODBOW_H
#define GOODBOW_H

#include "Weapon.h"

class GoodBow : public Weapon
{
public :
	GoodBow();
	~GoodBow();

	//upgradable values
	unsigned num_of_splits;
	double spliting_time;
	float percentage_force_transfered;
	float degree_apart;
	//1.f means total dmg of the splits are same as initial projectile
	float percentage_damage_transfered;

	virtual void Discharge(Vector3 position, Vector3 dir);
};


#endif // !GOODBOW_H

