#ifndef HUDMANAGER_H
#define HUDMANAGER_H

#include "SingletonTemplate.h"
#include "Vector3.h"
#include "Vertex.h"
class Mesh;
class HUDManager : public Singleton<HUDManager>
{
	friend Singleton;
	Mesh* HUDTHING;
	Mesh* Spell1;
	Mesh* Spell2;
	Mesh* Spell3;
	Mesh* Spell4;
	Mesh* cooldown;

	Mesh* ulti_ready_mesh;
	Vector3 ultbarpos;
	Vector3 ultbarscale;
	Mesh* Ulti_Bar;
	Mesh* Ulti_Charge;
	std::string ulti_ready_text;
	float ulti_charge_percent;
	float ulti_ready_rotate;
	float ulti_ready_rotate_speed;
	float ulti_ready_rotate_limit;
	Vector3 ulti_ready_pos;
	Vector3 ulti_ready_scale;
	Vector3 ulti_ready_dir;
	Color ulti_ready_color;
	void render_ulti_bar();
public:
	void update(double dt);
	void render();

protected:
	HUDManager();
	~HUDManager();
};

#endif // !HUDMANAGER_H

