#ifndef MINIONAIR_H
#define MINIONAIR_H

#include "Minion.h"

class MinionAir : public Minion
{
public:
	MinionAir();
	~MinionAir();
	virtual void attack();
	//virtual void update_state();
	//virtual void find_nearest_target(Vector3 &pos, Vector3 &scale);

	virtual void set_faction_side(Faction::FACTION_SIDE side);
	//virtual void walk(double dt);
};

#endif // !MINIONHEALER_H
