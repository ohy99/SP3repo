#ifndef DAMAGEAREA_H
#define DAMAGEAREA_H

#include "Collidable.h"
#include <vector>

class DamageArea : public Collidable
{
	std::vector<Collidable*> collided;
	double active_elapsed;
	double active_duration;
	int damage;
public:
	DamageArea();
	~DamageArea();
	void update(double dt);

	virtual void collision_response(Collidable* obj);

	void set_damage(int dmg);
	int get_damage();
	void set_duration(double duration);
};

#endif // !DAMAGEAREA_H

