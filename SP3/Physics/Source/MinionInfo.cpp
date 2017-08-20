#include "MinionInfo.h"
#include "MyMath.h"
#include "Minion.h"

MinionInfo::MinionInfo() : health(0), max_health(100), attack_damage(0),
attack_speed(0), attack_range(0), move_speed(0), attack_delay(0.0), move_direction(0, 0, 0),
nearest_target(nullptr)
{
}

MinionInfo::~MinionInfo()
{
}

void MinionInfo::attach_list_of_targets(std::list<Collidable*>* list)
{
	this->enemy_target = list;
}

void MinionInfo::set_walking_direction(Vector3 dir)
{
	this->move_direction = dir;
}

void MinionInfo::init_info(int max_hp, int att_dmg, float att_spd, float att_range, float move_spd)
{
	this->health = max_hp;
	this->max_health = max_hp;
	this->attack_damage = att_dmg;
	this->attack_speed = att_spd;
	this->attack_range = att_range;
	this->move_speed = move_spd;
}

void MinionInfo::get_hit(int dmg)
{
	this->health = Math::Clamp(health - dmg, 0, max_health);
}

void MinionInfo::reset()
{
	this->health = this->max_health;
	this->current_state = WALK;
	this->enemy_target = nullptr;
	this->nearest_target = nullptr;
}

void MinionInfo::update_info(double dt)
{
	attack_delay = Math::Max(attack_delay - dt, 0.0);
}

//void MinionInfo::attack(Faction::FACTION_SIDE side)
//{
//	if (attack_delay > 0.0)
//		return;
//
//
//}

//void MinionInfo::update_state(Vector3 m_pos)
//{
//	if (this->health <= 0)
//	{
//		this->current_state = DEAD;
//		return;
//	}
//	if (enemy_target->size() == 0)
//	{
//		nearest_target = nullptr;
//		this->current_state = WALK;
//		return;
//	}
//	for each (auto &target in *enemy_target)
//	{
//		if ((target->pos - m_pos).LengthSquared() < attack_range * attack_range * 1.1f)//offset
//		{
//			//now set as attack the first one
//			this->current_state = ATTACK;
//			nearest_target = &target->pos;
//			break;
//		}
//		else
//		{
//			//nothing in range
//			this->current_state = WALK;
//			nearest_target = nullptr;
//			break;
//		}
//	}
//}

int MinionInfo::get_attack_damage()
{
	return this->attack_damage;
}

float MinionInfo::get_move_speed()
{
	return this->move_speed;
}

bool MinionInfo::can_attack()
{
	if (attack_delay <= 0.0)
		return true;
	return false;
}

void MinionInfo::reset_attack()
{
	this->attack_delay = 1.0 / this->attack_speed;
}
