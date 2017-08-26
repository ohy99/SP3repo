#ifndef MINIONHEALER_H
#define MINIONHEALER_H

#include "Minion.h"

class MinionHealer : public Minion
{
public:
	MinionHealer();
	~MinionHealer();
	virtual void attack();
	virtual void update_state();
	virtual void find_nearest_target(Vector3 &pos, Vector3 &scale);

	virtual void set_faction_side(Faction::FACTION_SIDE side);
};

#endif // !MINIONHEALER_H
