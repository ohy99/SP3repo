#include "GameObjManager.h"
#include "GameObj.h"

#include "Ball.h"
#include "Bricks.h"
//#include "CollidableObj.h"
#include "Wall.h"
#include "Pillar.h"
#include "HPArea.h"

GameObjManager::GameObjManager() {

}
GameObjManager::~GameObjManager() {
	for each (auto &go in all_game_objs)
	{
		delete go;
	}
	all_game_objs.clear();
}

void GameObjManager::update_all_game_objs(double dt) {
	for each (auto const &go in all_game_objs)
	{
		if (go->active == true)
			go->update(dt);
	}
}

void GameObjManager::render_all_game_objs()
{
	for each (auto const &go in all_game_objs)
	{
		if (go->active == true)
			go->render();
	}
}

void GameObjManager::add_game_obj(GameObj* g) {
	all_game_objs.push_back(g);
}

GameObj* GameObjManager::request_new(OBJ_TYPE type)
{
	GameObj* temp = nullptr;
	switch (type)
	{
	case OBJ_TYPE::BALL:
		temp = new Ball();
		break;
	case OBJ_TYPE::WALL:
		temp = new Wall();
		break;
	case OBJ_TYPE::PILLAR:
		temp = new Pillar();
		break;
	case OBJ_TYPE::BRICK:
		temp = new Bricks();
		break;
	case OBJ_TYPE::BRICK_WITH_TURRET:
		temp = new Bricks(true);
		break;
	case OBJ_TYPE::HPAREA:
		temp = new HPArea();
		break;
	}
	if (temp)
		all_game_objs.push_back(temp);
	return temp;
}