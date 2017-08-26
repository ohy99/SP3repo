#ifndef TOWER_H
#define TOWER_H

#include "Collidable.h"
#include "AudioPlayer.h"
class TowerManager;

class Tower : public Collidable
{
	friend TowerManager;
public:
	AudioPlayer audioPlayer;
	int maxhealth;
	int health;

	Tower();
	Tower(Faction::FACTION_SIDE side);
	virtual ~Tower();
	virtual void render();
	void get_hit(int dmg);
	
};


#endif // !TOWER_H
