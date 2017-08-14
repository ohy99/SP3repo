#ifndef _AMMO_H
#define _AMMO_H

#include "GameObj.h"
//#include "GlobalVariableManager.h"
//#include "Enemy.h"

class Ammo : public GameObj
{
public:
	Ammo(){}
	virtual ~Ammo(){}
	float projSpd;

	//GlobalVariables::Targets target;

	//void checkCollision(GlobalVariables::Targets target, float dmg)
	//{
	//	if (target == GlobalVariables::Targets::ENEMY) {
	//		for (auto e : GlobalVariables::get()->enemies) {
	//			if (e->active)
	//			{
	//				if (this->collision.isCollide(e->collision)) {
	//					e->getHit(dmg);
	//					this->active = false;
	//				}
	//			}
	//		}
	//		for (auto a : AsteroidManager::getinstance()->asteroids) {
	//			if (a->active) {
	//				if (this->collision.isCollide(a->collision)) {
	//					a->getHit(dmg);
	//					this->active = false;
	//				}
	//			}
	//		}
	//	}
	//	else if (target == GlobalVariables::Targets::PLAYER) {

	//		if (this->collision.isCollide(GlobalVariables::get()->player->collision)) {
	//			GlobalVariables::get()->player->getHit(dmg);
	//			this->active = false;
	//		}
	//	}
	//}
};

#endif