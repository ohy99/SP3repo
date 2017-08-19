#ifndef MINIONMANAGER_H
#define MINIONMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <list>
class Minion;
class MinionManager : public Singleton<MinionManager>
{
	friend Singleton;
	std::vector<Minion*> minions;

	std::list<Minion*> player_minions;
	std::list<Minion*> enemy_minions;
	Minion* get_inactive_minion();
public:
	enum MINIONTYPE
	{
		MELEE,
		RANGE
	};
	void update(double dt);
	void spawn_minion(bool is_Player_Side = true, MINIONTYPE type = MINIONTYPE::MELEE);
protected:
	MinionManager();
	~MinionManager();
};


#endif // !ENEMYMANAGER_H
