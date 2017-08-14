#ifndef _ASTEROID_H
#define _ASTEROID_H

#include "GameObj.h"
//#include "Planet.h"
#include "PowerUpManager.h"
#include "Collectibles.h"
#include "GlobalVariableManager.h"

class Asteroid : public GameObj
{
	friend class AsteroidManager;
	const float dmg = 10.0f;
	float hp = 10.f;
	float MAXHP = 10.f;
	float hitDelay = 0.f;
	const float hitattspd = 1.f;

public:
	Vector3 force;

	Asteroid(){
		mesh = EntityBase::getInstance()->getEntity("ASTEROID");
		collision.collisionType = Collision::CollisionType::SPHERE;
		collision.radius = 2.f;
		collision.mid = &this->pos;

		this->scale.Set(collision.radius * 2.f, collision.radius * 2.f, 1);
	}
	~Asteroid() {}

	void updateCollisionMidpt() {
		collision.mid = &this->pos;
	}

	float getDmg() {
		return dmg;
	}

	void reset(){
		hp = MAXHP;
		hitDelay = 0.f;
	}
	void getHit(float dmg) {
		hp -= dmg;
	}


	void update(double dt) {
		if (this->active == false)
			return;

		updateCollisionMidpt();
		if (hitDelay < 1.f / hitattspd)
			hitDelay += (float)dt;


		this->vel = this->vel + (this->force * (1.f / this->mass)) * (float)dt;
		this->pos += this->vel * (float)dt;

		if (hp <= 0)
		{
			if (PowerUpManager::getInstance()->checkSpawn())
			{
				//PowerUpManager::getInstance()->randPowerup()
				Collectibles* temp = PowerUpManager::getInstance()->getRandomPowerUp();
				if (temp)
				{
					temp->active = true;
					temp->pos = this->pos;
				}
			}
			this->active = false;
			GlobalVariables::get()->pScore += 1;
		}

		if (!this->collision.isCollide(GlobalVariables::get()->PlayableBox))
		{
			//out of box
			this->active = false;
			this->reset();
		}
	}

	float gethp() {
		return hp;
	}
	float getMAXHP() {
		return MAXHP;
	}
};


#endif