#include "GameLogic.h"

#include "Application.h"
#include "MinionManager.h"

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::update(double dt)
{
	update_world_size();

	debuging_things();
}

void GameLogic::update_world_size()
{
	this->world_height = world_width * (float)Application::GetWindowHeight()
		/ Application::GetWindowWidth();
	//this->world_width = world_height * (float)Application::GetWindowWidth()
	//	/ (float)Application::GetWindowHeight();
}

void GameLogic::set_world_width(float world_width)
{
	this->world_width = world_width;
	this->world_height = world_width * (float)Application::GetWindowHeight()
		/ Application::GetWindowWidth();
	//this->world_height = world_width;
	//this->world_width = world_height * (float)Application::GetWindowWidth()
	//	/ (float)Application::GetWindowHeight();
}
void GameLogic::get_world_size(float& world_width, float& world_height)
{
	world_width = this->world_width;
	world_height = this->world_height;
}




void GameLogic::debuging_things()
{
	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('1') && !dakeypressed)
		{
			MinionManager::GetInstance()->spawn_minion();
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('1') && dakeypressed)
		{
			dakeypressed = false;
		}
	}
	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('2') && !dakeypressed)
		{
			MinionManager::GetInstance()->spawn_minion(true, MinionInfo::MINION_TYPE::BASIC_RANGE);
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('2') && dakeypressed)
		{
			dakeypressed = false;
		}
	}
	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('3') && !dakeypressed)
		{
			MinionManager::GetInstance()->spawn_minion(false);
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('3') && dakeypressed)
		{
			dakeypressed = false;
		}
	}
	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('4') && !dakeypressed)
		{
			MinionManager::GetInstance()->spawn_minion(false, MinionInfo::MINION_TYPE::BASIC_RANGE);
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('4') && dakeypressed)
		{
			dakeypressed = false;
		}
	}
}