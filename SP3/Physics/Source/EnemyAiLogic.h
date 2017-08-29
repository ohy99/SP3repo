#ifndef ENEMYAILOGIC_H
#define ENEMYAILOGIC_H

#include "SingletonTemplate.h"
#include "MinionInfo.h"

#include <utility>
#include <vector>
#include <queue>

class Character;
class Weapon;
class EnemyAiLogic : public Singleton<EnemyAiLogic>
{
	friend Singleton;

	//difficulty. 0 - 4?
	int logic_level;
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

	double random_spawn_cooldown;
	double random_spawn_min_time, random_spawn_max_time;
	double spawn_cooldown;
	double spawn_min_time, spawn_max_time;
	//const double default_spawn_min_time, default_spawn_max_time;

	Character *character;
	int level;

	Weapon* weap;
	void update_weapon(double dt);
public:
	void update(double dt);
	void attachCharacter(Character *character);
	void set_level(int level);
	int get_level();
	EnemyAiLogic(int level = 0);
	~EnemyAiLogic();
protected:
};

#endif // !ENEMYAILOGIC_H

