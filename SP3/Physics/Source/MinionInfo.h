#ifndef MINIONINFO_H
#define MINIONINFO_H

#include "Vector3.h"

class MinionInfo
{
	int health;
	int max_health;
public:
	enum State
	{
		DEAD = 0,
		WALK,
		ATTACK
	} current_state;
	MinionInfo();
	virtual ~MinionInfo();

	void get_hit(int dmg);
	void reset();

protected:
	Vector3 prev_pos;
};

#endif // !MINIONINFO_H
