#ifndef _PLANET_H
#define _PLANET_H

#include "GameObj.h"
#include "Graphics.h"
#include "RenderHelper.h"
//#include "ShipBase.h"
//#include "AsteroidsManager.h"
//#include "EnemyManager.h"
//#include "Enemy.h"

class Planet : public GameObj
{
	const double GravitationalConstant = 0.0000000000667408;
	const double offset = 1000;//looks correct can alr
	float mass;//in 100k -kg
	float radius;//coz this cannot be super big, mass will be smaller


public:
	float gravitationalRadius;
	float hp;
	float dmg;
	float MAXHP;
	float hitDelay;
	const float attSpd = 1.f;

	Planet() {
		this->collision.setCollisionType(Collision::CollisionType::SPHERE);
		this->collision.mid = this->pos;
		this->collision.radius = this->radius;

		//mass = 10000;
		//radius = 10;
		//hp = 10000;
		//dmg = 1000;
		this->reset();
		this->MAXHP = hp;

		gravitationalRadius = radius * 10.f;
		this->scale.Set(radius * 2, radius * 2, 1);

		this->mesh = EntityBase::getInstance()->getEntity("PLANET");

		hitDelay = 0.0f;


	}

	virtual ~Planet() {

	}

	void set(float mass, float radius) {
		this->mass = mass;
		this->radius = radius;
	}
	void reset(float hp = 10000, float dmg = 1000, float mass = 100, float radius = 10)
	{
		this->hp = hp;
		this->dmg = dmg;
		this->mass = mass;
		this->radius = radius;
	}

	void update(double dt) {
		if (this->active == false)
			return;

		if (hitDelay < 1.f / attSpd)
			hitDelay += (float)dt;

		this->collision.mid = this->pos;
		this->collision.radius = this->radius;

		if (this->hp <= 0) {
			this->active = false;
			this->reset();
			this->MAXHP = hp;
		}


	}

	void render() {
		Graphics::getInstance()->modelStack.PushMatrix();
		Graphics::getInstance()->modelStack.Translate(this->pos.x, this->pos.y, 0);
		Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)) - 90.f, 0, 0, 1);
		Graphics::getInstance()->modelStack.Scale(this->scale.x, this->scale.y, this->scale.z);
		RenderHelper::RenderMesh(this->mesh, false);
		Graphics::getInstance()->modelStack.PopMatrix();

		HpBar* temphp = GlobalVariables::get()->hpbar;

		temphp->pos.Set(this->pos.x, this->pos.y + 0.5f * radius, 0);
		temphp->scale.Set(7.5f, 5.f, 1);
		temphp->render(this->hp / this->MAXHP);
	}

	double updateGravitationalForce(Vector3 pos, float mass) {
		//returns force
		Vector3 dist = -this->pos + pos;
		float virtualMass = this->mass * Math::PI * radius * radius;
		return (GravitationalConstant * offset) * (double)(((mass * offset) * (virtualMass * offset)) / (Math::Max(dist.LengthSquared(), 1.0f)));
	}

	void getHit(float dmg) {
		this->hp -= dmg;
	}
};

#endif