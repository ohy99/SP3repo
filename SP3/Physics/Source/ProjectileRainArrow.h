#ifndef PROJECTILERAINARROW_H
#define PROJECTILERAINARROW_H

#include "Projectile.h"

class ProjectileRainArrow : public Projectile
{
	//play cheat. get the splitted arrows from objectpool HEH
	unsigned num_of_splits;
	double elapsed_time;
	double spliting_time;
	float percentage_force_transfered;
	float degree_apart;
	int percent_split_dmg;
public:
	ProjectileRainArrow();
	~ProjectileRainArrow();

	virtual void update(double dt);
	void set_spliting_time(double time);
	void set_num_of_splits(unsigned num);
	unsigned get_num_of_splits();
	void set_percentage_force_transfered(float percentage);
	void set_degree_apart(float degree);
	void set_total_percentage_split_damage(float splitdmg);
};

#endif // !PROJECTILERAINARROW_H

