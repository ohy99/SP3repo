#ifndef MINIONINFO_H
#define MINIONINFO_H

#include "Vector3.h"
#include <list>
#include "Faction.h"
class Minion;
class Collidable;
class Character;
class MinionInfo
{
	static Character* character;
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
		BASIC_SIEGE,
		BASIC_HEALER,

		MINION_TYPE_COUNT
	} minion_type;
	MinionInfo();
	virtual ~MinionInfo();

	void attach_list_of_targets(std::list<Collidable*>* list);
	void attach_list_of_ally(std::list<Collidable*>* list);
	void set_walking_direction(Vector3 dir);

	void init_info(int max_hp, int att_dmg, float att_spd, float att_range, float move_spd, double cast_time = 1.f);
	virtual void get_hit(int dmg);
	void reset();

	void update_info(double dt);
	virtual void find_nearest_target(Vector3 &pos, Vector3 &scale);

	int get_attack_damage();
	float get_move_speed();
	bool can_attack();
	void reset_attack();

	void set_knockback(Vector3 direction, float knockback_duration, float knockback_force);

	void attach_character(Character* character);
	//void attach_wallet(Wallet* wallet);
	void add_coin_to_character(int value);
	void send_damage_feedback_to_character(int dmg, bool killed_target = false, int target_hp = 0);
protected:
	int health;
	int max_health;
	int attack_damage;
	float attack_speed;//how many hits per sec
	float attack_range;
	float move_speed;
	double cast_time;
	double cast_elapsed;

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
	std::list<Collidable*> *ally_target;
};

#endif // !MINIONINFO_H
