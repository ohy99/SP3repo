#ifndef _INCDMG_H
#define _INCDMG_H

#include "Collectibles.h"

class IncDmg : public Collectibles
{
	const float radius = 3.f;
	const float duration = 5.f;
public:
	IncDmg() : Collectibles(duration) {
		this->collision.setCollisionType(Collision::CollisionType::SPHERE);
		this->collision.mid = this->pos;
		this->collision.radius = this->radius;

		this->scale.Set(radius * 2, radius * 2);

		mesh = EntityBase::getInstance()->getEntity("INCDMG");

		setActiveDuration(duration);
	}
	virtual ~IncDmg() {

	}

};

#endif