#ifndef _BULLET_H
#define _BULLET_H

#include "Ammo.h"

class Bullet : public Ammo
{

public:
	Bullet(){
		mesh = EntityBase::getInstance()->getEntity("BULLET");
		projSpd = 50;
	}
	virtual ~Bullet() {}


	
};

#endif
