#ifndef _ENEMYMANAGER_H
#define _ENEMYMANAGER_H

#include "Enemy.h"
#include <vector>
//class Enemy;

class EnemyManager
{
	const int defaultNumOfEnemies = 100;

	static EnemyManager* instance;
	EnemyManager();

	Enemy* getInactive();

	float spawnDelay = 0.f;
	const float spawnDelayTrigger = 3.f;
public:
	static EnemyManager* getinstance();
	~EnemyManager();
	void update(double dt);
	void render();

	void spawnRandomEnemy();
	void disableEnemies();


	std::vector<Enemy*>enemies;
};

#endif