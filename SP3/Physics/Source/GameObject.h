#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"

struct GameObject
{

	Vector3 pos;
	Vector3 dir;
	Vector3 vel;
	Vector3 scale;
	
	bool active;

	GameObject();
	~GameObject();
};

#endif