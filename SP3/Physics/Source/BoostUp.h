#ifndef _BOOSTUP_H
#define _BOOSTUP_H

#include "Collectibles.h"

class BoostUp : public Collectibles
{
	const float radius = 3.f;
	const float duration = 5.f;
public:
	BoostUp() : Collectibles(duration) {
		this->collision.setCollisionType(Collision::CollisionType::SPHERE);
		this->collision.mid = this->pos;
		this->collision.radius = this->radius;

		this->scale.Set(radius * 2, radius * 2);

		mesh = EntityBase::getInstance()->getEntity("BOOSTUP");

		setActiveDuration(duration);
	}
	virtual ~BoostUp() {

	}

};

#endif