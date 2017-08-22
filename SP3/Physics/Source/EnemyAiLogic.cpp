#include "EnemyAiLogic.h"

EnemyAiLogic::EnemyAiLogic(int level) : logic_level(level),
	resource(0), resource_gain(0), resource_gain_delay(0.0), resource_gain_elapsed_time(0.0),
	player_threat_level(0)
{
	set_spawn_pattern();
}

EnemyAiLogic::~EnemyAiLogic()
{
}

void EnemyAiLogic::update(double dt)
{
	resource_gain_elapsed_time += dt;

	attempt_to_unqueue_spawn();
}


void EnemyAiLogic::random_spawn()
{
	//higher threat, more tendency to spawn harder minions

	//index to limit which one will spawn
	int lower_index, higher_index;
	int difference_index = higher_index - lower_index;

	//find probability 0 - 1
	//float probability = 
	//current tower hp, player existing minions, difference in minion count, 
	//player coin, player total level, 

	//temp
	int rand = Math::RandIntMinMax(0, spawn_pattern.size() - 1);

	queue_spawn_horde(spawn_pattern.at(0).second);
}

void EnemyAiLogic::queue_spawn_horde(std::string pattern)
{
	for (int i = 0; i < pattern.size() - 1; ++i)
	{
		spawn_queue.push(pattern.at(i));
	}
}

void EnemyAiLogic::attempt_to_unqueue_spawn()
{
	char type = spawn_queue.front();
	spawn_queue.pop();
	switch (type)
	{
	case 'R':
		break;
	case 'S':
		break;
	default:
		break;
	}
}

void EnemyAiLogic::set_spawn_pattern()
{
	std::pair<int, std::string> temp;

	//lvl 1
	temp.first = 1;
	temp.second = "M";
	spawn_pattern.push_back(temp);
	temp.second = "MM";
	spawn_pattern.push_back(temp);

	//lvl 2
	temp.first = 2;
	temp.second = "RR";
	spawn_pattern.push_back(temp);
	temp.second = "MR";
	spawn_pattern.push_back(temp);
	temp.second = "MRR";
	spawn_pattern.push_back(temp);

	//lvl 3
	temp.first = 3;
	temp.second = "MS";
	spawn_pattern.push_back(temp);
	temp.second = "MRS";
	spawn_pattern.push_back(temp);
	temp.second = "MSS";
	spawn_pattern.push_back(temp);
	temp.second = "SRS";
	spawn_pattern.push_back(temp);

	//lvl 4
	temp.first = 4;
	temp.second = "MH";
	spawn_pattern.push_back(temp);
	temp.second = "MRH";
	spawn_pattern.push_back(temp);
	temp.second = "MHS";
	spawn_pattern.push_back(temp);
	temp.second = "MRSH";
	spawn_pattern.push_back(temp);

	//bonus wierd stuffs
	temp.second = "HRSH";
	spawn_pattern.push_back(temp);
	temp.second = "HHS";
	spawn_pattern.push_back(temp);
	temp.second = "MRSHS";
	spawn_pattern.push_back(temp);
}
