#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Collidable.h"

class Projectile : public Collidable
{
	int dmg;
	//maybe can add variables to activate particles here
public:
	Vector3 velocity;

	Projectile();
	virtual ~Projectile();

	void set_dmg(int dmg);
	int get_dmg();

	virtual void collision_response(Collidable* obj);
};

#endif // !PROJECTILE_H
