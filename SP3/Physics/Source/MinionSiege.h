#ifndef MINIONSIEGE_H
#define MINIONSIEGE_H

#include "Minion.h"

class MinionSiege : public Minion
{
public:
	MinionSiege();
	~MinionSiege();
	virtual void attack();

	virtual void set_faction_side(Faction::FACTION_SIDE side);
};

#endif // !MINIONSIEGE_H
