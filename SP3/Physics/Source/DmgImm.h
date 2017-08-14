#ifndef _DMGIMM_H
#define _DMGIMM_H

#include "Collectibles.h"

class DmgImm : public Collectibles
{
	const float radius = 3.f;
	const float duration = 3.f;
public:
	DmgImm() : Collectibles(duration) {
		this->collision.setCollisionType(Collision::CollisionType::SPHERE);
		this->collision.mid = this->pos;
		this->collision.radius = this->radius;

		this->scale.Set(radius * 2, radius * 2);

		mesh = EntityBase::getInstance()->getEntity("DMGIMM");

		setActiveDuration(duration);
	}
	virtual ~DmgImm() {

	}

};

#endif