#include "GenericEnvironmentCollidable.h"

#include "CollisionManager.h"

GenericEnvironmentCollider::GenericEnvironmentCollider(bool is_ground)
{
	this->set_faction_side(Faction::FACTION_SIDE::NONE);
	this->active = true;

	if (is_ground)
		CollisionManager::GetInstance()->add_ground(this);
}

GenericEnvironmentCollider::~GenericEnvironmentCollider()
{
}
