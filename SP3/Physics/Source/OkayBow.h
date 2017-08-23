#ifndef OKAYBOW_H
#define OKAYBOW_H

#include "Weapon.h"

class OkayBow : public Weapon
{
public:
	OkayBow();
	~OkayBow();

	//upgradable values
	unsigned num_of_shots;
	float distance_btw_shots;

	virtual void Discharge(Vector3 position, Vector3 dir);
};

#endif // !OKAYBOW_H

