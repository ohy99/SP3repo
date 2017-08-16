#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Collidable.h"

class Projectile : public Collidable
{
	Vector3 velocity;
	int dmg;

	//maybe can add variables to activate particles here
public:
	Projectile();
	virtual ~Projectile();

	void set_dmg(int dmg);
	int get_dmg();

};

#endif // !PROJECTILE_H
