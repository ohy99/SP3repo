#ifndef BRICKS_H
#define BRICKS_H

#include "CollidableObj.h"
class Turret;

class Bricks : public CollidableObj
{

public:
	enum COLLIDERS
	{
		UPWALL,
		RIGHTWALL,
		TLPILLAR,
		TRPILLAR,
		BRPILLAR,
		BLPILLAR,
		//LPILLAR,
		//RPILLAR,
		COLLIDERCOUNT
	};

	Bricks(bool include_turret = false);
	virtual ~Bricks();

	virtual void update(double dt);

	virtual void deactivate();

	virtual void collision_response(double dt, CollidableObj* other);

	virtual bool check_collision(CollidableObj* ball);
	

	virtual void render();

	Vector3 normal_up;
	Vector3 normal_right;
	Vector3 pillars_pos[4];
	 
	bool is_static;//cannot destroy
	bool is_player_platform;

	CollidableObj* collision[COLLIDERS::COLLIDERCOUNT];

	Turret* turret;
};


#endif