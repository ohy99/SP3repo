#ifndef MINIONRANGE_H
#define MINIONMELEE_H

#include "Minion.h"

class MinionRange : public Minion
{
public:
	MinionRange();
	~MinionRange();
	virtual void attack();

	virtual void set_faction_side(Faction::FACTION_SIDE side);
};

#endif // !MINIONMELEE_H
