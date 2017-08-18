#ifndef TOWER_H
#define TOWER_H

#include "Collidable.h"

class Tower : public Collidable
{
public:
	Tower();
	Tower(Faction::FACTION_SIDE side);
	virtual ~Tower();
};


#endif // !TOWER_H
