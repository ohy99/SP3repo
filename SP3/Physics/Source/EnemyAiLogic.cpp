#include "EnemyAiLogic.h"

#include "MinionManager.h"
#include "CharacterInfo.h"
#include <string>
#include "TowerManager.h"
#include "Tower.h"

EnemyAiLogic::EnemyAiLogic(int level) : logic_level(level),
	resource(0), resource_gain(0), resource_gain_delay(0.0), resource_gain_elapsed_time(0.0),
	player_threat_level(0), 
	random_spawn_cooldown(0.0), random_spawn_min_time(10.0), random_spawn_max_time(15.0),
	spawn_cooldown(0.0), spawn_min_time(3.0), spawn_max_time(5.0),
	level(1)
{
	set_spawn_pattern();
}

EnemyAiLogic::~EnemyAiLogic()
{
}

void EnemyAiLogic::attachCharacter(Character *character)
{
	this->character = character;
}

void EnemyAiLogic::set_level(int level)
{
	this->level = level;
}

void EnemyAiLogic::update(double dt)
{
	resource_gain_elapsed_time += dt;
	spawn_cooldown = Math::Max(spawn_cooldown - dt, 0.0);
	random_spawn_cooldown = Math::Max(random_spawn_cooldown - dt, 0.0);

	//std::cout << "gen rand: " << random_spawn_cooldown << "   spawn cd: " << spawn_cooldown << std::endl;
	float enemy_armor = Math::Max(100 * (1 + level) - (int)resource_gain_elapsed_time, 100);
	float enemy_dmg_reduction = 1.0f - (100.f / (100.f + enemy_armor));
	TowerManager::GetInstance()->set_enemy_dmg_reduction(enemy_dmg_reduction);

	random_spawn();
	attempt_to_unqueue_spawn();
}


void EnemyAiLogic::random_spawn()
{
	if (random_spawn_cooldown > 0.0)
		return;
	//higher threat, more tendency to spawn harder minions

	//index to limit which one will spawn
	//int lower_index, higher_index;
	//int difference_index = higher_index - lower_index;

	//find probability 0 - 1
	//float probability = 
	//current tower hp, player existing minions, difference in minion count, 
	//player coin, player total level, 

	//level = 1 + (character->getcurrenthighscore() / 1000);

	//temp
	int max_spawns = 1 + (level) * 5;
	int minion_size = MinionManager::GetInstance()->get_enemy_minion_list()->size();
	if (minion_size >= max_spawns)
		return;

	int left_over_space = max_spawns - minion_size;

	int rand = Math::RandIntMinMax(0, spawn_pattern.size() - 1);
	while (spawn_pattern.at(rand).first > level || spawn_pattern.at(rand).second.size() > left_over_space)
		rand = Math::RandIntMinMax(0, spawn_pattern.size() - 1);

	queue_spawn_horde(spawn_pattern.at(rand).second);
	//depending on how big the pattern is 
	random_spawn_min_time = spawn_pattern.at(rand).second.size() * 3.0;//adjust this 3.f
	random_spawn_max_time = random_spawn_min_time * 1.5;

	random_spawn_cooldown = Math::RandFloatMinMax(random_spawn_min_time, random_spawn_max_time);
}

void EnemyAiLogic::queue_spawn_horde(std::string pattern)
{
	for (int i = 0; i < pattern.size(); ++i)
	{
		spawn_queue.push(pattern.at(i));
	}
	std::cout << pattern << std::endl;
}

void EnemyAiLogic::attempt_to_unqueue_spawn()
{
	//when to pop
	if (spawn_cooldown > 0.0)
		return;

	if (spawn_queue.size() == 0)
		return;


	char type = spawn_queue.front();
	spawn_queue.pop();
	switch (type)
	{
	case 'R':
		MinionManager::GetInstance()->spawn_minion(false, MinionInfo::MINION_TYPE::BASIC_RANGE);
		spawn_min_time = MinionManager::GetInstance()->get_minion_scale()* 1.5f /
			MinionManager::GetInstance()->get_move_spd_of_type(MinionInfo::MINION_TYPE::BASIC_RANGE);
		spawn_max_time = spawn_min_time * 1.5f;
		break;
	case 'S':
		MinionManager::GetInstance()->spawn_minion(false, MinionInfo::MINION_TYPE::BASIC_SIEGE);
		spawn_min_time = MinionManager::GetInstance()->get_minion_scale()* 1.5f /
			MinionManager::GetInstance()->get_move_spd_of_type(MinionInfo::MINION_TYPE::BASIC_SIEGE);
		spawn_max_time = spawn_min_time * 1.5f;
		break;
	case 'H':
		MinionManager::GetInstance()->spawn_minion(false, MinionInfo::MINION_TYPE::BASIC_HEALER);
		spawn_min_time = MinionManager::GetInstance()->get_minion_scale()* 1.5f /
			MinionManager::GetInstance()->get_move_spd_of_type(MinionInfo::MINION_TYPE::BASIC_HEALER);
		spawn_max_time = spawn_min_time * 1.5f;
		break;
	default:
		MinionManager::GetInstance()->spawn_minion(false);
		spawn_min_time = MinionManager::GetInstance()->get_minion_scale()* 1.5f /
			MinionManager::GetInstance()->get_move_spd_of_type(MinionInfo::MINION_TYPE::BASIC_MELEE);
		spawn_max_time = spawn_min_time * 1.5f;
		break;
	}
	
	//adjust depends on what type is spawned
	spawn_cooldown = (double)Math::RandFloatMinMax(spawn_min_time, spawn_max_time);
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

	//bonus weird stuffs
	temp.second = "HRSH";
	spawn_pattern.push_back(temp);
	temp.second = "HHS";
	spawn_pattern.push_back(temp);
	temp.second = "MRSHS";
	spawn_pattern.push_back(temp);
}

