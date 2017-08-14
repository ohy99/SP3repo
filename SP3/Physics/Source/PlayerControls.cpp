#include "PlayerControls.h"

#include "Bricks.h"
#include "Ball.h"
#include "Application.h"
#include "GlobalVariableManager.h"
#include "GameObjManager.h"
#include "PhysicsManager.h"

#include <iostream>
using std::cout;
using std::endl;
#include "GameLogic.h"

PlayerControls::PlayerControls() {
	init_ed = false;
}
PlayerControls::~PlayerControls() {
	
}

void PlayerControls::init() {
	if (init_ed)
		return;
	platform = (Bricks*)GameObjManager::GetInstance()->request_new(GameObjManager::OBJ_TYPE::BRICK);
	this->platform->scale.Set(20, 3, 1);
	this->platform->active = true;
	this->platform->is_static = true;
	this->platform->is_player_platform = true;
	this->platform->faction = CollidableObj::FACTION_SIDE::PLAYER;
	//GameObjManager::GetInstance()->add_game_obj(platform);
	GameLogic::GetInstance()->attach_platform(this->platform);
	init_ed = true;
}
void PlayerControls::update(double dt) {

	GlobalVariables::get();
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float posX = static_cast<float>(x) / w * *GlobalVariables::get()->worldWidth - *GlobalVariables::get()->worldWidth * 0.5f;
	//float posY = (h - static_cast<float>(y)) / h * *GlobalVariables::get()
	//	->worldHeight - *GlobalVariables::get()->worldHeight * 0.5f;
	float posY = *GlobalVariables::get()->worldHeight * 0.1f - *GlobalVariables::get()->worldHeight * 0.5f;

	float displacement = posX - this->platform->pos.x;
	displacement = Math::Clamp(displacement, -50 * (float)dt, 50 * (float)dt);
	this->platform->pos.Set(this->platform->pos.x + displacement, posY);
	if (this->platform->pos.x - this->platform->scale.x * 0.5f < -50.f)
		this->platform->pos.x = -50.f + this->platform->scale.x * 0.5f;
	else if (this->platform->pos.x + this->platform->scale.x * 0.5f > 50.f)
		this->platform->pos.x = 50.f - this->platform->scale.x * 0.5f;
	

	//DEBUG
	//temp_debug();


	skill1();
	skill2();
	skill3();
	skill4();

}

void PlayerControls::skill1() {
	
	static bool is_pressed = false;
	if (Application::IsKeyPressed('Q') && is_pressed == false)
	{
		GameLogic::GetInstance()->spawn_ball = true;
		is_pressed = true;
	}
	else if (Application::IsKeyPressed('Q') == false && is_pressed == true)
		is_pressed = false;
	
}
void PlayerControls::skill2() {
	static bool is_pressed = false;
	if (Application::IsKeyPressed('W') && is_pressed == false)
	{
		GameLogic::GetInstance()->slow_down = true;
		is_pressed = true;
	}
	else if (Application::IsKeyPressed('W') == false && is_pressed == true)
		is_pressed = false;
}
void PlayerControls::skill3() {
	static bool is_pressed = false;
	if (Application::IsKeyPressed('E') && is_pressed == false)
	{
		GameLogic::GetInstance()->black_hole = true;
		is_pressed = true;
	}
	else if (Application::IsKeyPressed('E') == false && is_pressed == true)
		is_pressed = false;
}
void PlayerControls::skill4() {
	static bool is_pressed = false;
	if (Application::IsKeyPressed('R') && is_pressed == false)
	{
		GameLogic::GetInstance()->convert_all = true;
		is_pressed = true;
	}
	else if (Application::IsKeyPressed('R') == false && is_pressed == true)
		is_pressed = false;
}


void PlayerControls::temp_debug()
{
	static bool is_pressed = false;
	if (Application::IsKeyPressed(VK_SPACE) && is_pressed == false)
	{

		is_pressed = true;
	}
	else if (Application::IsKeyPressed(VK_SPACE) == false && is_pressed == true)
		is_pressed = false;

	static bool is_pressed2 = false;
	if (Application::IsKeyPressed('V') && is_pressed2 == false)
	{
		Ball* ball = (Ball*)GameObjManager::GetInstance()->request_new(GameObjManager::OBJ_TYPE::BALL);
		ball->pos.SetZero();
		ball->pos.y = this->platform->pos.y;
		ball->pos.x = 20.f;
		ball->scale.Set(1, 1, 1);
		ball->vel.Set(-10, 0, 0);
		PhysicsManager::GetInstance()->add_obj(ball);
		ball->active = true;
		ball->faction = CollidableObj::FACTION_SIDE::ENEMY;
		ball->is_collidable = true;
		is_pressed2 = true;
	}
	else if (Application::IsKeyPressed('V') == false && is_pressed2 == true)
		is_pressed2 = false;

	{
		static bool is_pressed3 = false;
		if (Application::IsKeyPressed('C') && is_pressed3 == false)
		{
			Ball* ball = (Ball*)GameObjManager::GetInstance()->request_new(GameObjManager::OBJ_TYPE::BALL);
			ball->pos.SetZero();
			ball->pos.y = this->platform->pos.y;
			ball->pos.x = -20.f;
			ball->scale.Set(1, 1, 1);
			ball->vel.Set(10, 0, 0);
			PhysicsManager::GetInstance()->add_obj(ball);
			ball->active = true;
			ball->faction = CollidableObj::FACTION_SIDE::ENEMY;
			ball->is_collidable = true;
			is_pressed3 = true;
		}
		else if (Application::IsKeyPressed('C') == false && is_pressed3 == true)
			is_pressed3 = false;

	}

	{
		static bool is_pressed3 = false;
		if (Application::IsKeyPressed('I') && is_pressed3 == false)
		{
			Ball* ball = (Ball*)GameObjManager::GetInstance()->request_new(GameObjManager::OBJ_TYPE::BALL);
			ball->pos.SetZero();
			ball->pos.y = 25.f;
			ball->pos.x = -20.f;
			ball->scale.Set(1, 1, 1);
			ball->vel.Set(10, 0, 0);
			PhysicsManager::GetInstance()->add_obj(ball);
			ball->active = true;
			ball->faction = CollidableObj::FACTION_SIDE::PLAYER;
			ball->is_collidable = true;
			is_pressed3 = true;
		}
		else if (Application::IsKeyPressed('I') == false && is_pressed3 == true)
			is_pressed3 = false;
	}

	{
		static bool is_pressed3 = false;
		if (Application::IsKeyPressed('O') && is_pressed3 == false)
		{
			Ball* ball = (Ball*)GameObjManager::GetInstance()->request_new(GameObjManager::OBJ_TYPE::BALL);
			ball->pos.SetZero();
			ball->pos.y = 25.f;
			ball->pos.x = 20.f;
			ball->scale.Set(1, 1, 1);
			ball->vel.Set(-10, 0, 0);
			PhysicsManager::GetInstance()->add_obj(ball);
			ball->active = true;
			ball->faction = CollidableObj::FACTION_SIDE::PLAYER;
			ball->is_collidable = true;
			is_pressed3 = true;
		}
		else if (Application::IsKeyPressed('O') == false && is_pressed3 == true)
			is_pressed3 = false;
	}

	{
		static bool is_pressed3 = false;
		if (Application::IsKeyPressed('B') && is_pressed3 == false)
		{
			Ball* ball = (Ball*)GameObjManager::GetInstance()->request_new(GameObjManager::OBJ_TYPE::BALL);
			ball->pos.SetZero();
			ball->pos.y = this->platform->pos.y - 1.f;
			ball->pos.x = -20.f;
			ball->scale.Set(1, 1, 1);
			ball->vel.Set(10, 1, 0);
			PhysicsManager::GetInstance()->add_obj(ball);
			ball->active = true;
			ball->faction = CollidableObj::FACTION_SIDE::ENEMY;
			ball->is_collidable = true;
			is_pressed3 = true;
		}
		else if (Application::IsKeyPressed('B') == false && is_pressed3 == true)
			is_pressed3 = false;
	}

	{
		static bool is_pressed3 = false;
		if (Application::IsKeyPressed('N') && is_pressed3 == false)
		{
			Ball* ball = (Ball*)GameObjManager::GetInstance()->request_new(GameObjManager::OBJ_TYPE::BALL);
			ball->pos.SetZero();
			ball->pos.y = this->platform->pos.y - 1.f;
			ball->pos.x = 20.f;
			ball->scale.Set(1, 1, 1);
			ball->vel.Set(-10, 1, 0);
			PhysicsManager::GetInstance()->add_obj(ball);
			ball->active = true;
			ball->faction = CollidableObj::FACTION_SIDE::ENEMY;
			ball->is_collidable = true;
			is_pressed3 = true;
		}
		else if (Application::IsKeyPressed('N') == false && is_pressed3 == true)
			is_pressed3 = false;
	}
}