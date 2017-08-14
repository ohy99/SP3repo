#ifndef _MISSILE_H
#define _MISSILE_H

#include "Ammo.h"
#include "Mtx44.h"
#include "GlobalVariableManager.h"

class Missile : public Ammo
{
	
	Vector3 lockedPosition;//why do i have a pos and a game obj
	float rotateSpd;
public:
	GameObj* locked;//this can be used for homing missile, then the v3 pos can be used for guided
	bool isLockedOn;
	Missile() {
		isLockedOn = false;
		this->projSpd = 20;
		rotateSpd = 2;//30degrees per sec

		this->collision.setCollisionType(Collision::CollisionType::POINT);
		this->collision.point = this->dir;//colllision point is point relative to pos
		this->collision.mid = this->pos;
		this->scale.Set(0.5f, 1.f, 0.5f);

		mesh = EntityBase::getInstance()->getEntity("MISSILE");

		locked = nullptr;
	}
	virtual ~Missile() {

	}

	void update(double dt) {
		if (locked) {
			if (locked->active == false)
				isLockedOn = false;
		}

		if (isLockedOn) {

			Vector3 targetDir = (-this->pos + lockedPosition);
			targetDir.Normalize();
			
			float angleBtwTargetAndMe = Math::RadianToDegree(acos(this->dir.Dot(targetDir)));
			Vector3 ourNormal;
			try {
				ourNormal = this->dir.Cross(targetDir);
				ourNormal.Normalize();

			}
			catch (DivideByZero) {
				ourNormal.Set(0, 0, 1);
			}

			Mtx44 missileRotate;
			missileRotate.SetToRotation(Math::Min(angleBtwTargetAndMe,rotateSpd), ourNormal.x, ourNormal.y, ourNormal.z);
			this->dir = missileRotate * this->dir;
		}

		this->vel = this->dir * projSpd;
		this->pos += this->vel * (float)dt;
		this->collision.mid = this->pos;
		this->collision.point = this->dir;

		if (!(this->collision.isCollide(GlobalVariables::get()->PlayableBox))) {
			//Out of playable box
			this->active = false;
			this->reset();
		}
	}

	bool setLockedOn(Vector3 pos)
	{
		if (isLockedOn)
			return false;
		//if got lock on liao then zao

		isLockedOn = true;
		lockedPosition = pos;
		return true;
	}
	bool setLockedOn(GameObj* tat)
	{
		if (isLockedOn)
			return false;
		//if got lock on liao then zao

		isLockedOn = true;
		locked = tat;
		return true;
	}

	void updateLockedPos(Vector3 pos) {
		if (locked == nullptr)
			lockedPosition = pos;
		else//i lock someting alr
			lockedPosition = locked->pos;
	}

	void updateLockedPos() {
		if (locked)
		{
			if (locked->active)
				lockedPosition = locked->pos;
		}
	}

	void reset() {
		locked = nullptr;
		isLockedOn = false;
	}

};

#endif