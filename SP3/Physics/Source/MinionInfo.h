#ifndef MINIONINFO_H
#define MINIONINFO_H

#include "Vector3.h"
#include <list>
#include "Faction.h"
class Minion;
class Collidable;
class MinionInfo
{

public:
	enum STATE
	{
		DEAD = 0,
		WALK,
		ATTACK,

		//CC
		KNOCKBACK,

		STATE_COUNT
	} current_state;
	enum MINION_TYPE
	{
		BASIC_MELEE,
		BASIC_RANGE,

		MINION_TYPE_COUNT
	} minion_type;
	MinionInfo();
	virtual ~MinionInfo();

	void attach_list_of_targets(std::list<Collidable*>* list);
	void set_walking_direction(Vector3 dir);

	void init_info(int max_hp, int att_dmg, float att_spd, float att_range, float move_spd);
	virtual void get_hit(int dmg);
	void reset();

	void update_info(double dt);

	//void attack(Faction::FACTION_SIDE side);
	//void update_state(Vector3 m_pos);

	int get_attack_damage();
	float get_move_speed();
	bool can_attack();
	void reset_attack();

	void set_knockback(Vector3 direction, float knockback_duration, float knockback_force);
protected:
	int health;
	int max_health;
	int attack_damage;
	float attack_speed;//how many hits per sec
	float attack_range;
	float move_speed;

	double attack_delay;

	Vector3 prev_pos;
	Vector3 move_direction;
	bool is_CCed;
	Vector3 knockback_direction;
	double knockback_duration;
	double knockback_force;
	double knockback_elapsed;
	Vector3 *nearest_target;

	std::list<Collidable*> *enemy_target;
};

#endif // !MINIONINFO_H
