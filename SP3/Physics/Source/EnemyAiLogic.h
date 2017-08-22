#ifndef ENEMYAILOGIC_H
#define ENEMYAILOGIC_H

#include "SingletonTemplate.h"
#include "MinionInfo.h"

#include <utility>
#include <vector>
#include <queue>

class EnemyAiLogic : public Singleton<EnemyAiLogic>
{
	friend Singleton;

	//difficulty. 0 - 4?
	const int logic_level;
	//to determine how much/ what can be spawned
	int resource;
	int resource_gain;
	double resource_gain_delay;
	double resource_gain_elapsed_time;
	//estimate the threat level of player using player item levels/resource counts
	int player_threat_level;

	std::queue<char> spawn_queue;
	void random_spawn();
	void queue_spawn_horde(std::string pattern);
	void attempt_to_unqueue_spawn();

	std::vector< std::pair<int, std::string> > spawn_pattern;
	void set_spawn_pattern();
public:
	void update(double dt);
protected:
	EnemyAiLogic(int level = 0);
	~EnemyAiLogic();
};

#endif // !ENEMYAILOGIC_H

