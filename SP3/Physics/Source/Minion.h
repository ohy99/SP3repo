#ifndef MINION_H
#define MINION_H

#include "Collidable.h"
#include "MinionInfo.h"
class MinionManager;
#include "SpriteAnimation.h"
#include "AudioPlayer.h"
class Minion : public Collidable, public MinionInfo
{
	friend MinionManager;
	bool attacked;
	Animation animation;
	AudioPlayer audioPlayer;

	double heal_elapsed;
	double heal_duration;

	bool show_stats_info;
	Vector3 stats_info_pos;
	void show_stats(Vector3 pos);
public:
	Mesh* mesh_state[MinionInfo::STATE::STATE_COUNT];
	Minion();
	virtual ~Minion();

	virtual void update(double dt);

	//every minion different attack style
	virtual void walk(double dt);
	virtual void attack();
	virtual void update_state();
	void respond_to_state(double dt);

	virtual void get_hit(int dmg);
	virtual void collision_response(Collidable* obj);

	virtual void render();
};

#endif // !MINION_H
