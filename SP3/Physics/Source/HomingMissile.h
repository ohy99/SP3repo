#ifndef _HOMINGMISSILE_H
#define _HOMINGMISSILE_H

#include "Weapon.h"
#include "Missile.h"

class HomingMissile : public Weapon
{
public:
	HomingMissile() {
		this->dmg = 20;
		this->fireRatePerSec = 2;
		this->activeTime = 0.0;

		for (int i = 0; i < 25; ++i) {
			Missile* temp = new Missile();
			ammo.push_back(temp);
		}
		
	}
	virtual ~HomingMissile() {

	}


	void weaponUpdate(double dt) {
		attack(dt);

		//moves ammo and check if it leaves screen. checking on collision to target is on ship class itself
		for (auto it : ammo) {
			if (it->active) {

				//it->pos += it->vel * (float)dt;
				//it->collision.mid = it->pos;

				Missile* temp = dynamic_cast<Missile*>(it);
				temp->update(dt);
				//if (!(it->collision.isCollide(GlobalVariables::get()->PlayableBox))) {
				//	//Out of playable box
				//	it->active = false;
				//}
			}
		}
	}

	virtual void weaponRender() {
		for (auto it : ammo) {
			if (it->active)
			{
				Graphics::getInstance()->modelStack.PushMatrix();
				//Graphics::getInstance()->modelStack.LoadMatrix(transformation);
				Graphics::getInstance()->modelStack.Translate(it->pos.x, it->pos.y, it->pos.z);
				Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(it->dir.y, it->dir.x)) - 90.f, 0, 0, 1);
				if (it->scale.x > 1 || it->scale.y > 1.f)
				{
					it->scale.x = 0.5f;
					it->scale.y = 1.f;
				}
				Graphics::getInstance()->modelStack.Scale(it->scale.x, it->scale.y, 1);
				RenderHelper::RenderMesh(it->getMesh(), false);
				Graphics::getInstance()->modelStack.PopMatrix();
			}
		}
	}

	void attack(double dt) {
		activeTime += dt;
		if (activeTime > 1.0 / (double)fireRatePerSec) {
			activeTime = 0.0;
		}

		if (!isAttack) {
			return;
		}

		if (activeTime != 0.0)
		{
			return;
		}

		//SHOOT!
		Missile* temp = getInactive();
		if (temp)
		{
			temp->active = true;
			temp->dir = this->dir;
			temp->vel = temp->dir * temp->projSpd;
			temp->pos = this->pos;
		}
			activeTime += dt;
	}

	Missile* getInactive() {
		for (auto it : ammo) {
			if (!it->active) {
				return dynamic_cast<Missile*>(it);
			}
		}
		return nullptr;
	}
};

#endif