#include "PhysicsManager.h"

#include "GameObject.h"
#include "Projectile.h"

PhysicsManager::PhysicsManager() : gravity(0, -10, 0)
{

}
PhysicsManager::~PhysicsManager() {

}

void PhysicsManager::update(double dt) {

	for each (auto &go in objects)
	{
		if (go->active == false)
			continue;

		//go->update(dt);
		Projectile* proj = dynamic_cast<Projectile*>(go);
		if (proj)
		{
			proj->velocity += gravity * (float)dt;
			proj->pos += proj->velocity * (float)dt;
		}
	}
}

void PhysicsManager::add_object(GameObject* go)
{
	objects.push_back(go);
}