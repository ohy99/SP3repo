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
protected:
	TowerManager();
	~TowerManager();
};


#endif // !TOWERMANAGER_H

