#ifndef _COLLIDABLEOBJ_H
#define _COLLIDABLEOBJ_H

#include "GameObj.h"
#include "CollisionManager.h"


class CollidableObj abstract : public GameObj
{

public:

	CollidableObj(bool add = true) {
		collision_type = BALL;
		faction = FACTION_SIDE::FS_NONE;
		is_collidable = true;
		collided_at_this_frame = false;
		collision_type = CollidableObj::COLLISION_TYPE::NONE;
		if (add)
			CollisionManager::GetInstance()->add_collider_obj(this);
	}
	virtual ~CollidableObj() {}
	
	virtual void collision_response(double dt, CollidableObj* other) {

	}


	enum COLLISION_TYPE
	{
		NONE,
		BALL,
		WALL,
		BRICK,
		HPAREA,
		//BOX,//brick
		PILLAR
	}collision_type;
	enum FACTION_SIDE
	{
		FS_NONE,
		PLAYER,
		ENEMY
	}faction;

	bool is_collidable;
	Vector3 normal;

	bool collided_at_this_frame;
};

#endif