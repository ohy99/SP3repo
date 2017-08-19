#include "MinionInfo.h"
#include "MyMath.h"

MinionInfo::MinionInfo() :health(0), max_health(100)
{
}

MinionInfo::~MinionInfo()
{
}

void MinionInfo::get_hit(int dmg)
{
	this->health = Math::Clamp(health - dmg, 0, max_health);
}

void MinionInfo::reset()
{
	this->health = this->max_health;
	this->current_state = WALK;
}
