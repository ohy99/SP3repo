#ifndef _HPUP_H
#define _HPUP_H

#include "Collectibles.h"

class HpUp : public Collectibles
{
	const float radius = 3.f;
	const float duration = 2.f;
public:
	HpUp() : Collectibles(duration){
		this->collision.setCollisionType(Collision::CollisionType::SPHERE);
		this->collision.mid = this->pos;
		this->collision.radius = this->radius;

		this->scale.Set(radius * 2, radius * 2);

		mesh = EntityBase::getInstance()->getEntity("HPUP");

		setActiveDuration(duration);
	}
	virtual ~HpUp() {

	}

};

#endif