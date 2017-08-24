#include "MinionInfo.h"
#include "MyMath.h"
#include "Minion.h"
#include "CharacterInfo.h"

Character* MinionInfo::character = nullptr;

MinionInfo::MinionInfo() : health(0), max_health(100), attack_damage(0),
attack_speed(0), attack_range(0), move_speed(0), attack_delay(0.0), move_direction(0, 0, 0), is_CCed(false), 
knockback_direction(0, 0, 0), knockback_duration(0.0), knockback_force(0.0), knockback_elapsed(0.0),
nearest_target(nullptr), cast_time(0.0), cast_elapsed(0.0)
{
}

MinionInfo::~MinionInfo()
{
}

void MinionInfo::attach_list_of_targets(std::list<Collidable*>* list)
{
	this->enemy_target = list;
}

void MinionInfo::attach_list_of_ally(std::list<Collidable*>* list)
{
	this->ally_target = list;
}

void MinionInfo::set_walking_direction(Vector3 dir)
{
	this->move_direction = dir;
}

void MinionInfo::init_info(int max_hp, int att_dmg, float att_spd, float att_range, float move_spd, double cast_time)
{
	this->health = max_hp;
	this->max_health = max_hp;
	this->attack_damage = att_dmg;
	this->attack_speed = att_spd;
	this->attack_range = att_range;
	this->move_speed = move_spd;
	this->cast_time = cast_time;
}

void MinionInfo::get_hit(int dmg)
{
	this->health = Math::Clamp(health - dmg, 0, max_health);
	//ShowHpManager::GetInstance()->generate_hp_text(this->)
}

void MinionInfo::reset()
{
	this->health = this->max_health;
	this->current_state = WALK;
	this->enemy_target = nullptr;
	this->nearest_target = nullptr;
	this->is_CCed = false;
}

void MinionInfo::update_info(double dt)
{
	if (current_state != STATE::ATTACK)
		attack_delay = Math::Max(attack_delay - dt, 0.0);
	else
		cast_elapsed = Math::Min(cast_elapsed + dt, cast_time);
}

void MinionInfo::find_nearest_target(Vector3 &pos, Vector3 &scale)
{
	if (this->can_attack() == false)
	{
		this->current_state = WALK;
		return;
	}

	//finding nearest target
	Collision temp;
	temp.setCollisionType(Collision::CollisionType::SPHERE);
	temp.mid = &pos;
	temp.radius = (scale.x * 0.5f) * attack_range * 1.1f;//1.1 is da offset

	for each (auto &target in *enemy_target)
	{
		if (target->check_collision(temp))
		{
			//now set as attack the first one if first one is inside
			this->current_state = ATTACK;
			nearest_target = &target->pos;
			if (dynamic_cast<Minion*>(target))
				break;//if the target is minion, break
		}
		else
		{
			//nothing in range
			this->current_state = WALK;
			nearest_target = nullptr;
		}
	}
}

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

void MinionInfo::set_knockback(Vector3 direction, float knockback_duration, float knockback_force)
{
	this->knockback_direction = direction;
	this->knockback_duration = knockback_duration;
	this->knockback_force = knockback_force;
	this->current_state = STATE::KNOCKBACK;
	this->is_CCed = true;
}

void MinionInfo::attach_character(Character * character)
{
	this->character = character;
}

void MinionInfo::add_coin_to_character(int value)
{
	this->character->add_coins(value);
}
