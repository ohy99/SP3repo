#ifndef MINIONMELEE_H
#define MINIONMELEE_H

#include "Minion.h"

class MinionMelee : public Minion
{
public:
	MinionMelee();
	~MinionMelee();
	virtual void attack();

	virtual void set_faction_side(Faction::FACTION_SIDE side);
};

#endif // !MINIONMELEE_H
