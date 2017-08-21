#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "SingletonTemplate.h"

class GameLogic : public Singleton<GameLogic>
{
	friend Singleton;

	float world_width;
	float world_height;

	void update_world_size();
	void debuging_things();
public:
	void update(double dt);

	void set_world_width(float world_width);
	void get_world_size(float& world_width, float& world_height);
protected:
	GameLogic();
	~GameLogic();
};

#endif // !1
