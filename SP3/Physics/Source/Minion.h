#ifndef MINION_H
#define MINION_H

#include "Collidable.h"
#include "MinionInfo.h"

class Minion : public Collidable, public MinionInfo
{
public:
	Minion();
	virtual ~Minion();

	virtual void collision_response(Collidable* obj);
};

#endif // !MINION_H
