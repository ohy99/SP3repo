#ifndef GENERICENVIRONMENTCOLLIDER_H
#define GENERICENVIRONMENTCOLLIDER_H

#include "Collidable.h"

class GenericEnvironmentCollider : public Collidable
{
public:
	GenericEnvironmentCollider(bool is_ground = false);
	~GenericEnvironmentCollider();
};


#endif // !GENERICENVIRONMENTCOLLIDER_G
