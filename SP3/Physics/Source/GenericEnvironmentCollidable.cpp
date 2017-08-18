#include "GenericEnvironmentCollidable.h"

GenericEnvironmentCollider::GenericEnvironmentCollider()
{
	this->set_faction_side(Faction::FACTION_SIDE::NONE);
	this->active = true;
}

GenericEnvironmentCollider::~GenericEnvironmentCollider()
{
}
