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
class MinionManager : public Singleton<MinionManager>
{
	struct MINION_INFO
	{
		int max_hp;
		int dmg;
		float att_spd;
		float att_range;
		float move_spd;
		MINION_INFO();
	};
	MINION_INFO minion_info[MinionInfo::MINION_TYPE::MINION_TYPE_COUNT];
	friend Singleton;
	std::vector<Minion*> minions;

	std::list<Collidable*> player_minions;
	std::list<Collidable*> enemy_minions;
	Minion* get_inactive_minion();

	Vector3 player_movement_direction;
	Vector3 enemy_movement_direction;

	std::vector<DamageArea*> damage_sprite;
	void init_info();

	void init_info(Minion* minion, MinionInfo::MINION_TYPE type);
public:
	void update(double dt);
	void spawn_minion(bool is_Player_Side = true, MinionInfo::MINION_TYPE type = MinionInfo::MINION_TYPE::BASIC_MELEE);

	DamageArea* request_inactive_collidable(MinionInfo::MINION_TYPE type = MinionInfo::MINION_TYPE::BASIC_MELEE);
protected:
	MinionManager();
	~MinionManager();
};


#endif // !ENEMYMANAGER_H
