#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <list>

class CollisionManager : public Singleton<CollisionManager>
{
	friend Singleton;

public:
	void update(double dt);

protected:
	CollisionManager();
	virtual ~CollisionManager();
};

#endif // !COLLISION_MANAGER_H