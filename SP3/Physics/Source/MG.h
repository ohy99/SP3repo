#ifndef _MG_H
#define _MG_H

#include "Weapon.h"
#include <vector>
#include "Bullets.h"
#include "AsteroidsManager.h"

#include "Graphics.h"
#include "RenderHelper.h"

//#include "GlobalVariableManager.h"
#include "ShipBase.h"
#include "Player.h"


class MachineGun : public Weapon
{
	//ShipBase* target;
public:
	MachineGun(GlobalVariables::Targets target = GlobalVariables::Targets::ENEMY) {
		dmg = 5; 
		fireRatePerSec = 5;
		activeTime = 0.0;
		for (int i = 0; i < 100; ++i) {
			Bullet* temp = new Bullet();
			temp->scale.Set(0.2f, 0.2f, 0.2f);
			temp->collision.setCollisionType(Collision::CollisionType::SPHERE);
			temp->collision.radius = 0.2f;
			ammo.push_back(temp);
		}
		this->target = target;//doesnt matter for now
	}
	~MachineGun() {

	}

	void weaponUpdate(double dt) {
		attack(dt);

		//moves ammo and check if it leaves screen. checking on collision to target is on ship class itself
		for (auto it : ammo) {
			if (it->active) {

				it->pos += it->vel * (float)dt;
				it->collision.mid = it->pos;

				
				if (!(it->collision.isCollide(GlobalVariables::get()->PlayableBox))) {
					//Out of playable box
					it->active = false;
				}
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
		Bullet* temp = getInactive();
		if (temp)
		{
			temp->active = true;
			temp->dir = this->dir;
			temp->vel = temp->dir * temp->projSpd;
			temp->pos = this->pos;
		}


		activeTime += dt;
	}

	Bullet* getInactive() {
		for (auto it : ammo) {
			if (!it->active) {
				return dynamic_cast<Bullet*>(it);
			}
		}
		return nullptr;
	}

};

#endif
