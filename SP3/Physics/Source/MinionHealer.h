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
};

#endif // !MINIONHEALER_H
