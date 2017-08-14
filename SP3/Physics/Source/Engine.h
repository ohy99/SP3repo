#ifndef _ENGINE_H
#define _ENGINE_H

#include "GameObj.h"
#include "ShipBase.h"
#include "Mtx44.h"

class Engine : public GameObj
{
	//position is relative to ship center
	ShipBase* owner;
	//bool active to activate engine
public:
	float power;
	bool boosted;
	float boostPowerMultiplier;

	Engine() {
		owner = nullptr;
		power = 100;
		this->owner;
		boosted = false;
		boostPowerMultiplier = 5.f;
	}

	void setOwner(ShipBase* owner) {
		this->owner = owner;
	}

	//Vector3 forceDir;
	void update(double dt) {
		if (!this->active || owner == nullptr)//if not active, or belonging to no one, zao
			return;

		//find angle
		float finalPower = power;
		if (boosted)
		{
			finalPower *= boostPowerMultiplier;
		}

		Mtx44 rotate;
		rotate.SetToRotation(owner->rotateAngle, 0, 0, 1);
		owner->force += (rotate * this->dir) * finalPower;
		//owner->force.x = this->dir.x * power;
		
	}
	~Engine() {
		owner = nullptr;
	}

	Vector3 getTorque() {
		//m_torque = (owner->dir.Cross(Vector3(0, 0, 1)).Normalized() - owner->dir).Cross(owner->dir * 5);
		return this->pos.Cross(this->dir * power);
	}
};

#endif