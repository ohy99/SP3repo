#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "GameObject.h"
class Particle : public GameObject
{
public:
	
	virtual void update(double dt);
	void init();
	virtual void render();
	Particle() {};
	~Particle() {};
	void set_duration(double duration);
private:
	double active_elapsed;
	double active_duration;

protected:
};

#endif // 
