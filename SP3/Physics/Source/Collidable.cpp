#include "Collidable.h"

Collidable::Collidable()
{
	this->collider.mid = &this->pos;
	this->collider.collisionType = Collision::CollisionType::AABB;
	CollisionManager::GetInstance()->add_collider(this);
}

Collidable::~Collidable()
{
}

void Collidable::set_faction_side(Faction::FACTION_SIDE side)
{
	this->faction.side = side;
}
Faction::FACTION_SIDE Collidable::get_faction_side()
{
	return this->faction.side;
}

void Collidable::collision_response(Collidable * obj)
{
	return;
}

void Collidable::update_collider()
{
	if (this->collider.collisionType == Collision::CollisionType::AABB)
	{
		this->collider.min.Set(-this->scale.x * 0.5f, -this->scale.y * 0.5f);
		this->collider.max.Set(this->scale.x * 0.5f, this->scale.y * 0.5f);
	}
	else if (this->collider.collisionType == Collision::CollisionType::SPHERE)
	{
		this->collider.radius = this->scale.x;
	}
}
bool Collidable::check_collision(Collision & tat)
{
	return this->collider.isCollide(tat);
}
Collision & Collidable::get_collider()
{
	return collider;
}
void Collidable::set_collision_type(Collision::CollisionType type)
{
	this->collider.collisionType = type;
}

void Collidable::update(double dt)
{

}