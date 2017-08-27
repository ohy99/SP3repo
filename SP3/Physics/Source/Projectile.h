#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Collidable.h"

class Projectile : public Collidable
{
	int dmg;
	float mass;
	//maybe can add variables to activate particles here
	bool start_timer;
	double active_remaining_elapsed_timer;
	double active_remaining_duration;

	void start_countdown(bool sure_start);
public:
	Vector3 velocity;

	Projectile();
	virtual ~Projectile();

	virtual void update(double dt);

	void set_dmg(int dmg);
	int get_dmg();
	void set_mass(float mass);
	float get_mass();

	virtual void collision_response(Collidable* obj);
};

#endif // !PROJECTILE_H
