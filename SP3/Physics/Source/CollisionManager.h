#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <list>
class Collidable;
class CollisionManager : public Singleton<CollisionManager>
{
	friend Singleton;
	std::vector<Collidable*> colliders;
public:
	void update(double dt);
	void add_collider(Collidable* collidable);
protected:
	CollisionManager();
	virtual ~CollisionManager();
};

#endif // !COLLISION_MANAGER_H