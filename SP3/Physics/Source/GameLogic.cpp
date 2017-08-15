#include "GameLogic.h"

#include "Application.h"

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::update(double dt)
{
	update_world_size();
}

void GameLogic::update_world_size()
{
	this->world_height = world_width * (float)Application::GetWindowHeight()
		/ Application::GetWindowWidth();
}

void GameLogic::set_world_width(float world_width)
{
	this->world_width = world_width;
	this->world_height = world_width * (float)Application::GetWindowHeight()
		/ Application::GetWindowWidth();
}
void GameLogic::get_world_size(float& world_width, float& world_height)
{
	world_width = this->world_width;
	world_height = this->world_height;
}