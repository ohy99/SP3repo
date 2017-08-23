#ifndef MINIONRANGE_H
#define MINIONMELEE_H

#include "Minion.h"

class MinionRange : public Minion
{
public:
	MinionRange();
	~MinionRange();
	virtual void attack();
};

#endif // !MINIONMELEE_H
