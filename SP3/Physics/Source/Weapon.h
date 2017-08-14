#ifndef _WEAPON_H
#define _WEAPON_H

#include "GameObj.h"

#include "Ammo.h"
#include "GlobalVariableManager.h"

class Weapon : public GameObj
{

public:
	Weapon() {}
	virtual ~Weapon() {
		for (Ammo* a : ammo) {
			delete a;
			a = nullptr;
		}
	}

	float getDmg() {
		return dmg;
	}
	float getFrPs() {
		return fireRatePerSec;
	}
	virtual void attack(double dt) = 0;
	virtual void weaponUpdate(double dt) {

	}
	virtual void weaponRender() {
		for (auto it : ammo) {
			if (it->active)
			{
				Graphics::getInstance()->modelStack.PushMatrix();
				//Graphics::getInstance()->modelStack.LoadMatrix(transformation);
				Graphics::getInstance()->modelStack.Translate(it->pos.x, it->pos.y, it->pos.z);
				Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(it->dir.y, it->dir.x)) - 90.f, 0, 0, 1);
				Graphics::getInstance()->modelStack.Scale(it->scale.x, it->scale.y, 1);
				RenderHelper::RenderMesh(it->getMesh(), false);
				Graphics::getInstance()->modelStack.PopMatrix();
			}
		}
	}
	bool isAttack = false;
	std::vector<Ammo*> ammo;
	float dmg;
	float fireRatePerSec;
protected:	
	double activeTime;
	GlobalVariables::Targets target;

};

#endif
