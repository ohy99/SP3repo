#include "NoobBow.h"

#include "MeshList.h"

NoobBow::NoobBow()
{
	this->set_attackspeed(2.f);
	this->damage = 30;
	this->force = 40.f;
	this->projectile_mass = 2.f;

	this->mesh = MeshList::GetInstance()->getMesh("NOOBBOW");
}

NoobBow::~NoobBow()
{
}
