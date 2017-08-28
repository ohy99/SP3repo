#ifndef TOWER_H
#define TOWER_H

#include "Collidable.h"
#include "AudioPlayer.h"
class TowerManager;

class Tower : public Collidable
{
	friend TowerManager;

	float dmg_reduction;

	bool show_stats_info;
	Vector3 stats_info_pos;
	void show_stats(Vector3 pos, bool render_right = true);
public:
	AudioPlayer audioPlayer;
	int maxhealth;
	int health;

	Tower();
	Tower(Faction::FACTION_SIDE side);
	virtual ~Tower();
	virtual void update(double dt);
	virtual void render();
	void get_hit(int dmg);
	int get_health() { return health; }

	void set_dmg_reduction(float value);
	float get_dmg_reduction();
};


#endif // !TOWER_H
