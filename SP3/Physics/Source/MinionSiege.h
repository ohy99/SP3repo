#ifndef MINIONSIEGE_H
#define MINIONSIEGE_H

#include "Minion.h"

class MinionSiege : public Minion
{
public:
	MinionSiege();
	~MinionSiege();
	virtual void attack();
};

#endif // !MINIONSIEGE_H
