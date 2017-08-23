#ifndef TOWER_H
#define TOWER_H

#include "Collidable.h"
class TowerManager;

class Tower : public Collidable
{
	friend TowerManager;
public:

	int maxhealth;
	int health;

	Tower();
	Tower(Faction::FACTION_SIDE side);
	virtual ~Tower();
	virtual void render();
	void get_hit(int dmg);
	
};


#endif // !TOWER_H
