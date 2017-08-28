#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H

#include "SingletonTemplate.h"
class Tower;

class TowerManager : public Singleton<TowerManager>
{
	friend Singleton;
public:
	//temp
	Tower* player;
	Tower* enemy;

	void set_enemy_dmg_reduction(float value);
	void set_player_dmg_reduction(float value);

	void update(double dt);
protected:
	TowerManager();
	~TowerManager();
};


#endif // !TOWERMANAGER_H

