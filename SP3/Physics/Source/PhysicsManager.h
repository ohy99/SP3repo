#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
class GameObj;
#include "Vector3.h"

class PhysicsManager :public Singleton<PhysicsManager>
{
	friend Singleton;

public:
	void update(double dt);
	//void add_obj(GameObj* go);

protected:
	PhysicsManager();
	virtual ~PhysicsManager();
};



#endif // !
