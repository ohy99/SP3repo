#ifndef PILLAR_H
#define PILLAR_H

#include "CollidableObj.h"

class Pillar : public CollidableObj
{
public:
	Pillar(bool add = true) : CollidableObj(add) {
		this->collision_type = COLLISION_TYPE::PILLAR;

		this->mesh = EntityBase::getInstance()->getEntity("BALL");
		//radius = 1.f;
		parent = nullptr;
	}
	virtual ~Pillar() {

	}

	virtual void collision_response(double dt, CollidableObj* other) {
		if (parent)//if belong to brick, call brick
			return parent->collision_response(dt, other);
	}

	//float radius;
	CollidableObj* parent;
};

#endif // !WALL_H
