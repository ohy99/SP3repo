#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
class GameObj;
#include "Vector3.h"

class PhysicsManager :public Singleton<PhysicsManager>
{
	friend Singleton;
	std::vector<GameObj*> gameobjs;
	float ball_max_speed;
public:
	void update(double dt);
	void add_obj(GameObj* go);

	void set_ball_max_speed(float& ball_max_speed);

	void exert_external_force_on_all_obj(Vector3 pos_of_thing);
protected:
	PhysicsManager();
	virtual ~PhysicsManager();
};



#endif // !
