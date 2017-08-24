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
	bool hit_once;
	float hits_per_sec;
	double elapsed_time;
public:
	DamageArea();
	~DamageArea();
	void update(double dt);

	virtual void collision_response(Collidable* obj);

	void set_damage(int dmg, bool once_only = true, float hits_per_sec = 1.f);
	int get_damage();
	void set_duration(double duration);
};

#endif // !DAMAGEAREA_H

