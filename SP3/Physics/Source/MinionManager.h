#ifndef MINIONMANAGER_H
#define MINIONMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <list>
#include "Vector3.h"
#include "MinionInfo.h"
class DamageArea;
class Minion;
class Collidable;
class Character;
class MinionManager : public Singleton<MinionManager>
{
public:
	struct MINION_INFO
	{
		int max_hp;
		int dmg;
		float att_spd;
		float att_range;
		float move_spd;
		double cast_time;
		MINION_INFO();
	};
private:
	MINION_INFO default_minion_info[MinionInfo::MINION_TYPE::MINION_TYPE_COUNT];
	MINION_INFO minion_info[MinionInfo::MINION_TYPE::MINION_TYPE_COUNT];
	Character* characterinfo;
	friend Singleton;
	float minion_scale;
	std::vector<Minion*> minions;

	std::list<Collidable*> player_minions;
	std::list<Collidable*> enemy_minions;
	Minion* get_inactive_minion(MinionInfo::MINION_TYPE type = MinionInfo::MINION_TYPE::BASIC_MELEE);

	Vector3 player_movement_direction;
	Vector3 enemy_movement_direction;

	std::vector<DamageArea*> damage_sprite;
	void init_info(float level = 1.f);

	void init_pool();
	void init_info(Minion* minion, MinionInfo::MINION_TYPE type);

	Vector3 ground_spawn_point_relative_to_tower;
	Vector3 air_spawn_point_relative_to_tower;
public:
	void update(double dt);
	bool spawn_minion(bool is_Player_Side = true, MinionInfo::MINION_TYPE type = MinionInfo::MINION_TYPE::BASIC_MELEE);

	DamageArea* request_inactive_collidable(MinionInfo::MINION_TYPE type = MinionInfo::MINION_TYPE::BASIC_MELEE);

	std::list<Collidable*> * get_player_minion_list();
	std::list<Collidable*> * get_enemy_minion_list();

	float get_move_spd_of_type(MinionInfo::MINION_TYPE type);
	float get_minion_scale();

	void adjust_minions_move_speed(float percentage_of_default);
	void reset_minions_move_speed();
	void adjust_minions_dmg(float percentage_of_default);
	void reset_minions_dmg();
	void adjust_minions_att_spd(float percentage_of_default);
	void reset_minions_att_spd();
	void adjust_minions_hp(float percentage_of_default);
	void reset_minions_hp();

	void adjust_minion_difficulty(float difficulty);

	void attach_character(Character* character);

	MINION_INFO get_info(MinionInfo::MINION_TYPE type);
	MINION_INFO get_default_info(MinionInfo::MINION_TYPE type);
protected:
	MinionManager();
	~MinionManager();
};


#endif // !ENEMYMANAGER_H
