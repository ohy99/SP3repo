#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "SingletonTemplate.h"
#include <vector>
class GameObj;
#include "Vector3.h"
class Bricks;
class Ball;
class HPArea;
class GameLogic : public Singleton<GameLogic>
{
	friend Singleton;
	std::vector<GameObj*> bricks;

	double elasped_time;

	const Vector3 bricks_scaling;
	float falling_down_speed;
	float world_height;
	float world_width;
	const unsigned int max_bricks_per_row;
	const float start_left_x, end_spacing, between_spacing;
	float spawn_y;
	Bricks* platform;

	void init_borders();

	//game logic shall control how many balls in the field
	std::vector<GameObj*> balls;
	int max_number_of_active_balls;
	const Vector3 default_enemy_ball_scaling;
	//double shoot_delay;
	//double shoot_cooldown;

	double spawn_new_row_delay;
	double spawn_new_row_cd;
	GameObj* get_rand_inactive_brick();

	//hparea for hp
	HPArea* enemy_hp;
	HPArea* player_hp;
	int max_hp_for_players;

	std::vector<GameObj*> big_balls;
	GameObj* get_inactive_big_ball();
	const int max_num_of_big_balls_on_field;
	void update_values_for_powerups(double dt);
	double black_hole_active_time_remaining;
	const double black_hole_active_time;
	double black_hole_cooldown_remaining;
	const double black_hole_cooldown;
	double slow_down_active_time_remaining;
	const double slow_down_active_time;
	double slow_down_cooldown_remaining;
	const double slow_down_cooldown;
	double convert_all_cooldown_remaining;
	const double convert_all_cooldown;
	double spawn_ball_cooldown_remaining;
	const double spawn_ball_cooldown;
	unsigned int available_balls;

	int lvl_increment = 0;
	double increment_time_value = 30.0;
	double next_increment = increment_time_value;

	bool init_ed = false;
public:
	void init();
	void update(double dt);
	void render_info();

	void spawn_row();
	void attach_platform(Bricks* p);

	Ball* get_inactive_ball();

	double min_shoot_delay, max_shoot_delay;
	float ball_max_speed;

	//PowerUps
	//BlackHole
	bool black_hole;
	bool slow_down;
	bool convert_all;
	bool spawn_ball;

	bool game_won;

	void get_world_size_reference(float* width, float* height);
protected:
	GameLogic();
	virtual ~GameLogic();
};


#endif // !GAMELOGIC_H
