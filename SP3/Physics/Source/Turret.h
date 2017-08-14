#ifndef TURRET_H
#define TURRET_H

#include "GameObj.h"
#include "Vector3.h"
#include "GameLogic.h"
#include "Ball.h"
#include "PhysicsManager.h"
class Turret : public GameObj
{
public:
	float ejection_speed;
	double shoot_cooldown;
	double shoot_delay;
	Turret(){
		ejection_speed = 25.f;
		parent = nullptr;
		this->mesh = EntityBase::getInstance()->getEntity("MISSILE");
		this->up.Set(0, -1, 0);//upside down cone
		this->scale.Set(3, 3);
		GameLogic* g = GameLogic::GetInstance();
		shoot_delay = (double)Math::RandFloatMinMax(g->min_shoot_delay, g->max_shoot_delay);
		shoot_cooldown = shoot_delay;
	}
	virtual ~Turret(){}

	virtual void update(double dt) {
		if (parent)
			this->pos = this->parent->pos;
		shoot_cooldown -= dt;
		if (shoot_cooldown <= 0) {
			GameLogic* g = GameLogic::GetInstance();
			shoot_delay = (double)Math::RandFloatMinMax(g->min_shoot_delay, g->max_shoot_delay);
			Vector3 dir(Math::RandFloatMinMax(-2.f, 2.f), -1.f);
			dir.Normalize();
			shoot(dir);
			shoot_cooldown = shoot_delay;
		}
	}

	void shoot(Vector3 dir = Vector3(0, -1, 0))
	{
		Ball* temp = GameLogic::GetInstance()->get_inactive_ball();
		if (temp == nullptr)
			return;
		temp->active = true;
		temp->vel = dir * ejection_speed;
		temp->pos = this->pos;
		temp->faction = CollidableObj::FACTION_SIDE::ENEMY;
		
		//rotate
		//this->up = -dir;
		//this->up = -this->up;
		this->up = dir;
	}

	CollidableObj* parent;
};

#endif // !TURRET_H
