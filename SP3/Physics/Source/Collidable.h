#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "GameObject.h"
#include "Faction.h"
#include "Collision.h"
#include "CollisionManager.h"

class Collidable : public GameObject
{
	friend CollisionManager;
	Faction faction;
	bool is_collidable;
public:
	Faction::FACTION_SIDE get_faction_side();
	virtual void set_faction_side(Faction::FACTION_SIDE side);
	virtual void collision_response(Collidable* obj);
	virtual void update(double dt);

	void set_collision_type(Collision::CollisionType type);
	void update_collider();
	bool check_collision(Collision& tat);
	Collision& get_collider();

	void set_isCollidable(bool is_collidable);
	bool get_isCollidable();
protected:
	Collidable();
	virtual ~Collidable();
	Collision collider;

};

#endif // !COLLIDABLE_H
