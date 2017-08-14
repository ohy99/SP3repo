#ifndef _ENEMY_H
#define _ENEMY_H

#include "GameObj.h"
#include "ShipBase.h"
#include "Weapon.h"
#include "MG.h"
#include "Engine.h"
#include "Planet.h"

class Enemy : public ShipBase
{
	const float MAXHP = 100;
	float hp;
	float dmg;
	float moveSpd;
	float MAXSPD;
	float shootRange;
	ShipBase* target;

	Weapon* weap;
	Engine thruster;

	bool shoot;
	float shootTime;

	float shipRamDmgDelay;
	const float shipRamDmgAttSpd = 1.0f;

public:
	Enemy(ShipBase* target){
		mesh = EntityBase::getInstance()->getEntity("ENEMY");
		this->scale.Set(1, 2, 1);
		this->dir.Set(0, 1, 0);
		this->up.Set(0, 0, 1);
		this->right.Set(1, 0, 0);
		this->mass = 10.f;
		
		this->collision.setCollisionType(Collision::CollisionType::AABB);
		this->collision.mid = this->pos;
		this->collision.min.Set(-this->scale.x * 0.5f, -this->scale.y * 0.5f);
		this->collision.max.Set(this->scale.x * 0.5f, this->scale.y * 0.5f);

		this->target = target;
		this->reset();
		shootRange = 50;
		weap = new MachineGun();
		weap->fireRatePerSec = 2;

		thruster.setOwner(this);
		thruster.pos.Set(0, -1, 0);//relative to ship pos
		thruster.dir.Set(0, 1, 0);

		this->MAXSPD = 15.f;
		
		this->shipRamDmgDelay = 0.0f;
	}
	virtual ~Enemy() {
		if (weap)
		{
			delete weap;
			weap = nullptr;
		}
		target = nullptr;
	}
	void reset() {
		hp = MAXHP;
		dmg = 10;
		moveSpd = 5.f;
	}

	void update(double dt) {
	
		if (this->active == false)
			return;

		if (this->shipRamDmgDelay < 1.f / this->shipRamDmgAttSpd) {
			this->shipRamDmgDelay += (float)dt;
		}

		if (this->collision.isCollide(target->collision))//if i collide with u i hit u
		{
			if (this->shipRamDmgDelay >= 1.f / this->shipRamDmgAttSpd) {
				target->getHit(this->dmg);
				this->shipRamDmgDelay = 0.0f;
			}
		}
		

		
			this->dir = (-this->pos + target->pos).Normalized();
			thruster.active = true;
			//Vector3(0,1,0)
			this->rotateAngle = Math::RadianToDegree((float)atan2(1, 0) - atan2(this->dir.y, -this->dir.x));
			thruster.update(dt);

			//this->vel = this->dir * moveSpd;
			this->right = this->dir.Cross(this->up);

			for (auto p : *(GlobalVariables::get()->planetPointer))
			{
				if (p->active)
				{
					Vector3 meToP = (-this->pos + p->pos);
					if (meToP.LengthSquared() < p->gravitationalRadius * p->gravitationalRadius)
					{
						//less affeced by grevity
						meToP *= ((float)p->updateGravitationalForce(this->pos, this->mass) * 0.1f);
						this->force += meToP;
					}

					if (this->shipRamDmgDelay >= 1.f / this->shipRamDmgAttSpd) {
						if (this->collision.isCollide(p->collision)) {
							p->getHit(this->dmg);
							this->shipRamDmgDelay = 0.0f;
						}
					}

				}
			}


			//update force
			this->vel = this->vel + (this->force * (1.f / this->mass)) * (float)dt;
			if (this->vel.LengthSquared() > MAXSPD * MAXSPD)
			{
				this->vel.Normalize();
				this->vel *= MAXSPD;
			}

			if ((-this->pos + target->pos).LengthSquared() < shootRange * shootRange) 
			{
				weap->dir = this->dir;
				weap->pos = this->pos;
				this->pos += this->vel * (float)dt;
				weap->isAttack = true;
			}
			else
			{
				this->pos += this->vel * (float)dt;// *m_speed;
				weap->isAttack = false;
			}

		


		this->force.SetZero();

		weap->weaponUpdate(dt);
		for (auto it : weap->ammo)
		{
			if (it->active)
			{
				if (it->collision.isCollide(target->collision)) {
					target->getHit(this->dmg);
					it->active = false;
				}

				for (auto a : AsteroidManager::getinstance()->asteroids) {
					if (a->active) {
						if (it->collision.isCollide(a->collision)) {
							a->getHit(this->dmg);
							it->active = false;
						}
					}
				}
			}
		

		}

		if (this->hp <= 0)
		{
			this->active = false;
			GlobalVariables::get()->pScore += 5;
		}
		this->collision.mid = this->pos;

		if (!this->collision.isCollide(GlobalVariables::get()->PlayableBox))
		{
			//IF OUT OF PLAYING BOX
			this->active = false;
			this->reset();
		}
	}
	void render(){
		weap->weaponRender();
	}


	inline float gethp() {
		return hp;
	}
	inline float getMAXHP() {
		return MAXHP;
	}
	inline float getDmg() {
		return dmg;
	}

	void getHit(float dmg) {
		hp -= dmg;
	}

};

#endif
