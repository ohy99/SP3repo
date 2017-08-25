#ifndef HUDMANAGER_H
#define HUDMANAGER_H

#include "SingletonTemplate.h"
class Mesh;
class HUDManager : public Singleton<HUDManager>
{
	friend Singleton;
	Mesh* HUDTHING;
	Mesh* Spell1;
	Mesh* Spell2;
	Mesh* Spell3;
	Mesh* Spell4;
	Mesh* Ulti;
	Mesh* cooldown;
public:
	void update(double dt);
	void render();
protected:
	HUDManager();
	~HUDManager();
};

#endif // !HUDMANAGER_H

