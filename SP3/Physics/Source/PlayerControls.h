#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include "SingletonTemplate.h"
class Bricks;

class PlayerControls : public Singleton<PlayerControls>
{
	friend Singleton;
	Bricks* platform;

	void skill1();
	void skill2();
	void skill3();
	void skill4();
	void temp_debug();

	bool init_ed;
public:
	void init();
	void update(double dt);
protected:
	PlayerControls();
	virtual ~PlayerControls();
};

#endif // !PLAYERCONTROLS_H
