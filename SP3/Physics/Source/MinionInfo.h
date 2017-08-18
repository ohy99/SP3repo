#ifndef MINIONINFO_H
#define MINIONINFO_H

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
};

#endif // !MINIONINFO_H
