#ifndef _SHIPBASE_H
#define _SHIPBASE_H

#include "GameObj.h"

class ShipBase : public GameObj
{
public:
	ShipBase() {};
	virtual ~ShipBase() {}

	virtual void getHit(float dmg) {}

	Vector3 force;
	Vector3 torque;
	float rotateAngle;
};

#endif