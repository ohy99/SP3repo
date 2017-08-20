#ifndef MINION_H
#define MINION_H

#include "Collidable.h"
#include "MinionInfo.h"
class MinionManager;

class Minion : public Collidable, public MinionInfo
{
	friend MinionManager;
public:
	Minion();
	virtual ~Minion();

	virtual void update(double dt);

	void attack();
	void update_state();
	void respond_to_state(double dt);

	virtual void collision_response(Collidable* obj);

	virtual void render();
};

#endif // !MINION_H
