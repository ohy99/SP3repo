#ifndef MINIONMELEE_H
#define MINIONMELEE_H

#include "Minion.h"

class MinionMelee : public Minion
{
public:
	MinionMelee();
	~MinionMelee();
	virtual void attack();
};

#endif // !MINIONMELEE_H
