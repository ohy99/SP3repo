#include "GameLogic.h"
#include "GameObjManager.h"
#include "GameObj.h"
#include "EntityBase.h"
#include "Application.h"
#include "GlobalVariableManager.h"
#include "Wall.h"
#include "Ball.h"
#include "Bricks.h"
#include "PhysicsManager.h"
#include "Turret.h"
#include "HPArea.h"
#include "TextManager.h"
#include <sstream>
#include "SceneManager.h"

GameLogic::GameLogic() :
	bricks_scaling(7, 3),
	default_enemy_ball_scaling(1.f, 1.f),
	max_bricks_per_row(9), 
	start_left_x(-50.f),
	end_spacing(6.5f),
	between_spacing(3.f),
	black_hole_active_time(3.0),
	black_hole_cooldown(15.0),
	slow_down_active_time(5.0),
	slow_down_cooldown(8.0),
	spawn_ball_cooldown(4.0),
	convert_all_cooldown(30.0),
	max_num_of_big_balls_on_field(3)
{
	world_height = 100.f;
	world_width = world_height * (float)Application::GetWindowWidth() /
		(float)Application::GetWindowHeight();
	GlobalVariables::get()->worldHeight = &world_height;
	GlobalVariables::get()->worldWidth = &world_width;
	enemy_hp = nullptr;
	player_hp = nullptr;
	init_ed = false;
}
GameLogic::~GameLogic() {

}

void GameLogic::init() {



	min_shoot_delay = 5.f;
	max_shoot_delay = 10.f;
	spawn_new_row_delay = 5.f;
	spawn_new_row_cd = 3.f;
	spawn_y = world_height * 0.4f;
	falling_down_speed = 0.3f;
	available_balls = 0;

	lvl_increment = 0;
	increment_time_value = 30.0;
	next_increment = increment_time_value;

	if (enemy_hp && player_hp)
	{
		max_hp_for_players = 20;
		enemy_hp->set_max_hp(max_hp_for_players);
		enemy_hp->hp = max_hp_for_players;
		player_hp->set_max_hp(max_hp_for_players);
		player_hp->hp = max_hp_for_players;
	}
	elasped_time = 0.0;
	game_won = false;

	//powerup
	black_hole = false;
	black_hole_active_time_remaining = black_hole_active_time;
	black_hole_cooldown_remaining = 0.0;

	slow_down = false;
	slow_down_active_time_remaining = slow_down_active_time;
	slow_down_cooldown_remaining = 0.0;

	convert_all = false;
	convert_all_cooldown_remaining = 0.0;

	spawn_ball = false;
	spawn_ball_cooldown_remaining = 0.0;

	//set all active to inactive
	for each (auto b in bricks)
		b->active = false;
	for each (auto b in balls)
		b->active = false;
	for each (auto b in big_balls)
		b->active = false;

	if (init_ed)
		return;

	init_borders();

	for (unsigned i = 0; i < max_bricks_per_row * 10; ++i)
	{
		int randint = Math::RandIntMinMax(0, 3);
		GameObj* temp = nullptr;
		if ( randint != 0)
			temp = GameObjManager::GetInstance()->request_new(GameObjManager::BRICK);
		else
			temp = GameObjManager::GetInstance()->request_new(GameObjManager::BRICK_WITH_TURRET);

		Bricks* temp_brick = static_cast<Bricks*>(temp);
		temp_brick->faction = CollidableObj::FACTION_SIDE::ENEMY;
		temp->scale = bricks_scaling;

		temp->pos.Set(start_left_x + end_spacing + (between_spacing + bricks_scaling.x) * i + 
			bricks_scaling.x * 0.5f, (world_height + bricks_scaling.y) * 0.5f);
		//temp->pos.Set(-45.f + i * 10.f, (world_height + bricks_scaling.y) * 0.5f);
		if (i % 3 == 0) temp->mesh = EntityBase::getInstance()->getEntity("RED");
		if (i % 3 == 1) temp->mesh = EntityBase::getInstance()->getEntity("GREEN");
		if (i % 3 == 2) temp->mesh = EntityBase::getInstance()->getEntity("BLUE");
		temp->active = false;
		bricks.push_back(temp);
	}



	//CONTROLLING BALL
	max_number_of_active_balls = 25;
	for (int i = 0; i < max_number_of_active_balls; ++i) {
		GameObj* temp = GameObjManager::GetInstance()->request_new(GameObjManager::BALL);
		Ball* temp_ball = static_cast<Ball*>(temp);
		temp->scale = default_enemy_ball_scaling;
		temp_ball->faction = CollidableObj::FACTION_SIDE::ENEMY;
		temp->active = false;
		balls.push_back(temp);
		PhysicsManager::GetInstance()->add_obj(temp);
	}
	//shoot_delay = 3.f;
	//shoot_cooldown = shoot_delay;

	ball_max_speed = 50.f;
	PhysicsManager::GetInstance()->set_ball_max_speed(ball_max_speed);

	//set hp area
	max_hp_for_players = 20;
	enemy_hp = dynamic_cast<HPArea*>(GameObjManager::GetInstance()->request_new(GameObjManager::HPAREA));
	enemy_hp->faction = CollidableObj::FACTION_SIDE::ENEMY;
	enemy_hp->scale.Set(abs(start_left_x * 2), world_height * 0.1f);
	enemy_hp->pos.Set(0, world_height* 0.5f + enemy_hp->scale.y * 0.5f);
	enemy_hp->active = true;
	enemy_hp->mesh = nullptr;
	enemy_hp->set_max_hp(max_hp_for_players);
	enemy_hp->hp = max_hp_for_players;

	player_hp = dynamic_cast<HPArea*>(GameObjManager::GetInstance()->request_new(GameObjManager::HPAREA));
	player_hp->faction = CollidableObj::FACTION_SIDE::PLAYER;
	player_hp->scale.Set(abs(start_left_x * 2), world_height * 0.1f);
	player_hp->pos.Set(0, -world_height* 0.5f - player_hp->scale.y * 0.5f);
	player_hp->active = true;
	player_hp->mesh = nullptr;
	player_hp->set_max_hp(max_hp_for_players);
	player_hp->hp = max_hp_for_players;

	for (int i = 0; i < max_num_of_big_balls_on_field; ++i) {
		GameObj* temp = GameObjManager::GetInstance()->request_new(GameObjManager::BALL);
		Ball* temp_ball = static_cast<Ball*>(temp);
		temp->scale = default_enemy_ball_scaling * 2.f;
		temp_ball->faction = CollidableObj::FACTION_SIDE::PLAYER;
		temp->active = false;
		big_balls.push_back(temp);
		PhysicsManager::GetInstance()->add_obj(temp);
	}
	//available_balls = 0;

	//elasped_time = 0.0;
	//game_won = false;
	init_ed = true;
}
void GameLogic::update(double dt) {

	elasped_time += dt;

	world_height = 100.f;
	world_width = world_height * (float)Application::GetWindowWidth() /
		(float)Application::GetWindowHeight();

	if (enemy_hp->hp <= 0)
	{
		game_won = true;
		SceneManager::getInstance()->setNextScene("ENDGAME");
		return;
	}
	else if (player_hp->hp <= 0)
	{
		game_won = false;
		SceneManager::getInstance()->setNextScene("ENDGAME");
		return;
	}


	update_values_for_powerups(dt);
	if (slow_down)
		dt /= 3.0;

	for each (auto const &brick in bricks) {
		if (brick->active == false)
			continue;

		if (brick->pos.y > -world_height * 0.3f)
			brick->pos.y -= bricks_scaling.y * falling_down_speed * (float)dt;

		if (brick->pos.y < -world_height * 0.5f - bricks_scaling.y * 0.5f)
			brick->deactivate();

		//controlling ball shoot
		Bricks* temp_brick = static_cast<Bricks*>(brick);
		if (temp_brick)
			if (temp_brick->turret)
				temp_brick->turret->update(dt);
		
	}

	spawn_new_row_cd -= dt;
	if (spawn_new_row_cd <= 0)
	{
		spawn_row();
		spawn_new_row_cd = spawn_new_row_delay;
	}

	//every 30s
	//static int lvl_increment = 0;
	//static double increment_time_value = 30.0;
	//static double next_increment = increment_time_value;
	if (elasped_time >= next_increment)
	{
		spawn_new_row_delay = Math::Max(spawn_new_row_delay - 0.1, 3.0);
		falling_down_speed = Math::Min(falling_down_speed + 0.1f, 1.f);

		//5, 10
		min_shoot_delay = Math::Max(min_shoot_delay - 0.1, 2.0);
		max_shoot_delay = Math::Max(max_shoot_delay - 0.1, 5.0);
		++lvl_increment;
		next_increment += increment_time_value;
	}

}


void GameLogic::spawn_row()
{
	for (int i = 0; i < max_bricks_per_row; ++i)
	{
		GameObj* temp = nullptr;
		temp = get_rand_inactive_brick();
		if (temp == nullptr)
			break;

		temp->scale = bricks_scaling;

		temp->pos.Set(start_left_x + end_spacing + (between_spacing + bricks_scaling.x) * i +
			bricks_scaling.x * 0.5f, spawn_y);
		if (i % 3 == 0) temp->mesh = EntityBase::getInstance()->getEntity("RED");
		if (i % 3 == 1) temp->mesh = EntityBase::getInstance()->getEntity("GREEN");
		if (i % 3 == 2) temp->mesh = EntityBase::getInstance()->getEntity("BLUE");

		temp->active = true;
		Bricks* temp_brick = static_cast<Bricks*>(temp);
		temp_brick->is_collidable = true;
		//temp_brick->
		
		//bricks.push_back(temp);
	}
}


void GameLogic::attach_platform(Bricks* p)
{
	this->platform = p;
}

Ball* GameLogic::get_inactive_ball()
{
	for each (const auto& b in balls)
	{
		if (b->active)
			continue;
		return static_cast<Ball*>(b);
	}
	return nullptr;
}
GameObj* GameLogic::get_rand_inactive_brick()
{
	for each (const auto& b in bricks)
	{
		if (b->active)
			continue;
		return b;
	}
	return nullptr;
}

void GameLogic::update_values_for_powerups(double dt)
{
	//reduce all cd
	black_hole_cooldown_remaining = Math::Max(black_hole_cooldown_remaining - dt, 0.0);
	slow_down_cooldown_remaining = Math::Max(slow_down_cooldown_remaining - dt, 0.0);
	spawn_ball_cooldown_remaining = Math::Max(spawn_ball_cooldown_remaining - dt, 0.0);
	convert_all_cooldown_remaining = Math::Max(convert_all_cooldown_remaining - dt, 0.0);

	std::stringstream ss;
	ss << std::fixed;
	ss.precision(2);
	if (convert_all_cooldown_remaining > 0.0) ss << convert_all_cooldown_remaining;
	else ss << "Active";
	TextManager::GetInstance()->add_text(2, "Skill R : " + ss.str());
	ss.str("");
	if (black_hole_cooldown_remaining > 0.0) ss << black_hole_cooldown_remaining;
	else ss << "Active";
	TextManager::GetInstance()->add_text(3, "Skill E : " + ss.str());
	ss.str("");
	if (slow_down_cooldown_remaining > 0.0) ss << slow_down_cooldown_remaining;
	else ss << "Active";
	TextManager::GetInstance()->add_text(4, "Skill W : " + ss.str());
	ss.str("");
	if (spawn_ball_cooldown_remaining > 0.0) ss << spawn_ball_cooldown_remaining;
	else ss << "Active";
	TextManager::GetInstance()->add_text(5, "Skill Q : " + ss.str());
	ss.str("");

	//BLACKHOLE
	if (black_hole) {
		if (black_hole_cooldown_remaining > 0)
			black_hole = false;
		else {
			if (black_hole_active_time_remaining > 0) {

				PhysicsManager::GetInstance()->exert_external_force_on_all_obj(Vector3(0, -world_height * 0.1f));
				black_hole_active_time_remaining -= dt;
				if (black_hole_active_time_remaining <= 0)
				{
					black_hole_cooldown_remaining = black_hole_cooldown;
					black_hole = false;
					black_hole_active_time_remaining = black_hole_active_time;
				}
			}
		}
	}

	if (slow_down) {
		if (slow_down_cooldown_remaining > 0) 
			slow_down = false;
		else {
			if (slow_down_active_time_remaining > 0) {

				slow_down_active_time_remaining -= dt;
				if (slow_down_active_time_remaining <= 0)
				{
					slow_down_cooldown_remaining = slow_down_cooldown;
					slow_down = false;
					slow_down_active_time_remaining = slow_down_active_time;
				}
			}
		}
	}

	if (spawn_ball)
	{
		if (available_balls)
		{
			Ball* ball = dynamic_cast<Ball*>(get_inactive_big_ball());
			if (ball)
			{
				ball->pos.SetZero();
				ball->vel.Set(0, -25, 0);
				ball->active = true;
				--available_balls;
			}
		}
		spawn_ball = false;
	}
	if (available_balls == max_num_of_big_balls_on_field) {
		spawn_ball_cooldown_remaining = spawn_ball_cooldown;
	}
	if (available_balls < max_num_of_big_balls_on_field && spawn_ball_cooldown_remaining <= 0.0) {
		//spawn ball
		++available_balls;
		spawn_ball_cooldown_remaining = spawn_ball_cooldown;
	}
	

	if (convert_all) {
		if (convert_all_cooldown_remaining > 0)
			convert_all = false;
		else {
			//convert all balls
			for each (const auto &b in balls) {
				if (b->active == false)
					continue;
				Ball* ball = dynamic_cast<Ball*>(b);
				if (ball) {
					ball->faction = CollidableObj::FACTION_SIDE::PLAYER;
				}
			}
			convert_all_cooldown_remaining = convert_all_cooldown;
			convert_all = false;
		}
	}
}

GameObj* GameLogic::get_inactive_big_ball()
{
	for each (const auto &b in big_balls) {
		if (b->active)
			continue;
		return b;
	}
	return nullptr;
}


void GameLogic::render_info()
{
	static float scale = 5.f;

	std::stringstream ss;
	ss << std::fixed;
	ss.precision(2);
	ss << "Time: " << elasped_time;
	
	float halfWindowWidth = *GlobalVariables::get()->worldWidth * 0.5f;
	float halfWindowHeight = *GlobalVariables::get()->worldHeight * 0.5f;


		MS &ms = Graphics::getInstance()->modelStack;
		ms.PushMatrix();
		ms.Translate(halfWindowWidth * 0.7f, halfWindowHeight * 0.85f, 0);
		ms.Scale(scale, scale, scale);
		RenderHelper::RenderText(&TextManager::GetInstance()->calibri,
			ss.str(), Color(1, 1, 1));
		ms.PopMatrix();
}



void GameLogic::init_borders()
{
	float left_x = 50;
	float thickness_of_wall = 3.f;

	//Left wall
	GameObj* temp = GameObjManager::GetInstance()->request_new(GameObjManager::WALL);
	Wall* wall = static_cast<Wall*>(temp);
	wall->normal.Set(1, 0, 0);
	//wall->up.Set(0, 1, 0);
	//wall->scale.Set(thickness_of_wall, 100);
	wall->up.Set(1, 0, 0);
	wall->scale.Set(100, thickness_of_wall);
	wall->pos.Set(-(left_x + thickness_of_wall * 0.5f), 0);
	wall->active = true;

	//Right
	temp = GameObjManager::GetInstance()->request_new(GameObjManager::WALL);
	wall = static_cast<Wall*>(temp);
	wall->normal.Set(-1, 0, 0);
	//wall->up.Set(0, 1, 0);
	//wall->scale.Set(thickness_of_wall, 100);
	wall->up.Set(-1, 0, 0);
	wall->scale.Set(100, thickness_of_wall);
	wall->pos.Set((left_x + thickness_of_wall * 0.5f), 0);
	wall->active = true;

	//bottom left slant
	temp = GameObjManager::GetInstance()->request_new(GameObjManager::WALL);
	wall = static_cast<Wall*>(temp);
	wall->normal.Set(1, 2, 0);
	wall->normal.Normalize();
	wall->up.Set(1, 2, 0);
	wall->up.Normalize();
	wall->scale.Set(30, thickness_of_wall);
	wall->pos.Set(-(left_x + thickness_of_wall * 0.5f) + 12.5f,
		-world_height * 0.45f);
	wall->active = true;

	//bottom right slant
	temp = GameObjManager::GetInstance()->request_new(GameObjManager::WALL);
	wall = static_cast<Wall*>(temp);
	wall->normal.Set(-1, 2, 0);
	wall->normal.Normalize();
	wall->up.Set(-1, 2, 0);
	wall->up.Normalize();
	wall->scale.Set(30, thickness_of_wall);
	wall->pos.Set((left_x + thickness_of_wall * 0.5f) - 12.5f,
		-world_height * 0.45f);
	wall->active = true;

	//top left slant
	temp = GameObjManager::GetInstance()->request_new(GameObjManager::WALL);
	wall = static_cast<Wall*>(temp);
	wall->normal.Set(1, -2, 0);
	wall->normal.Normalize();
	wall->up.Set(1, -2, 0);
	wall->up.Normalize();
	wall->scale.Set(30, thickness_of_wall);
	wall->pos.Set(-(left_x + thickness_of_wall * 0.5f) + 12.5f,
		world_height * 0.45f);
	wall->active = true;

	//top right slant
	temp = GameObjManager::GetInstance()->request_new(GameObjManager::WALL);
	wall = static_cast<Wall*>(temp);
	wall->normal.Set(-1, -2, 0);
	wall->normal.Normalize();
	wall->up.Set(-1, -2, 0);
	wall->up.Normalize();
	wall->scale.Set(30, thickness_of_wall);
	wall->pos.Set((left_x + thickness_of_wall * 0.5f) - 12.5f,
		world_height * 0.45f);
	wall->active = true;
}

void GameLogic::get_world_size_reference(float* width, float* height)
{
	width = &this->world_width;
	height = &this->world_height;
}