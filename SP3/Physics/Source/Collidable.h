#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "GameObject.h"
#include "Faction.h"

class Collidable : public GameObject
{
	Faction faction;
public:
	Faction::FACTION_SIDE get_faction_side();
	void set_faction_side(Faction::FACTION_SIDE side);
	virtual void collision_response(Collidable* obj);
protected:
	Collidable();
	virtual ~Collidable();
};

#endif // !COLLIDABLE_H
