#ifndef WALL_H
#define WALL_H

#include "CollidableObj.h"

class Wall : public CollidableObj
{
public:
	Wall(bool add = true) : CollidableObj(add) {
		this->collision_type = COLLISION_TYPE::WALL;
		this->normal.Set(0, 1, 0);
		this->mesh = EntityBase::getInstance()->getEntity("BRICK");
		parent = nullptr;

		GameObj::collision.collisionType = Collision::AABB;
		GameObj::collision.mid = &this->pos;
		GameObj::collision.min.Set(-this->scale.x, -this->scale.y);
		GameObj::collision.max.Set(this->scale.x, this->scale.y);
	}
	virtual ~Wall() {

	}

	virtual void collision_response(double dt, CollidableObj* other) {
		if (parent)//if belong to brick, call brick
			return parent->collision_response(dt, other);
	}

	virtual void update(double dt) {
		if (parent)
			return;
		GameObj::collision.min.Set(-scale.x, -scale.y);
		GameObj::collision.max.Set(scale.x, scale.y);
	}

	//Vector3 normal;
	CollidableObj* parent;
};

#endif // !WALL_H
