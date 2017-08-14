#include "EnemyManager.h"

#include "Mtx44.h"
#include "Graphics.h"
#include "RenderHelper.h"

#include "GlobalVariableManager.h"
#include "Player.h"
//#include "Enemy.h"

EnemyManager::EnemyManager()
{
	for (int i = 0; i < defaultNumOfEnemies; ++i) {
		enemies.push_back(new Enemy(GlobalVariables::get()->player));
	}
	GlobalVariables::get()->enemies = &(this->enemies);
}

EnemyManager::~EnemyManager()
{
	for (auto it : enemies)
	{
		delete it;
		it = nullptr;
	}

	//if (instance)
	//	delete instance;
	//instance = nullptr;
}

EnemyManager* EnemyManager::getinstance()
{
	if (!instance)
		instance = new EnemyManager();
	return instance;
}

void EnemyManager::update(double dt)
{
	for (auto it : enemies)
	{
		if (it->active) {

			if (it->collision.isCollide(GlobalVariables::get()->player->collision)) {
				GlobalVariables::get()->player->getHit(it->getDmg());
			}
			//it->pos += it->vel * (float)dt;

			it->update(dt);
		}

	}

	spawnDelay += (float)dt;
	if (spawnDelay >= spawnDelayTrigger)
	{
		spawnRandomEnemy();
		spawnDelay = 0.f;
		
		//int counter = 0;
		//for (auto it : enemies) {
		//	if (it->active)
		//		++counter;
		//}
		//std::cout << counter << std::endl;
	}
}

void EnemyManager::render()
{
	for (auto it : enemies) {

		if (it->active)
		{
			it->render();//render the bullets. idk why is it here but i too lazy change
			//Mtx44 transformation(it->right.x * it->scale.x, it->right.y * it->scale.y, it->right.z * it->scale.z, 0,
			//	it->up.x * it->scale.x, it->up.y * it->scale.y, it->up.z * it->scale.z, 0,
			//	it->dir.x * it->scale.x, it->dir.y * it->scale.y, it->dir.z * it->scale.z, 0,
			//	it->pos.x, it->pos.y, it->pos.z, 1);

			Graphics::getInstance()->modelStack.PushMatrix();
			//Graphics::getInstance()->modelStack.LoadMatrix(transformation);
			Graphics::getInstance()->modelStack.Translate(it->pos.x, it->pos.y, it->pos.z);
			Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(it->dir.y, it->dir.x)) - 90.f, 0, 0, 1);
			Graphics::getInstance()->modelStack.Scale(it->scale.x, it->scale.y, it->scale.z);
			RenderHelper::RenderMesh(it->getMesh(), false);
			Graphics::getInstance()->modelStack.PopMatrix();

			//pos + offset to up
			GlobalVariables::get()->hpbar->pos.Set(it->pos.x, it->pos.y + it->scale.y * 1.75f, it->pos.z);
			GlobalVariables::get()->hpbar->scale.Set(5.f, 1.5f, 1);
			GlobalVariables::get()->hpbar->render(it->gethp() / it->getMAXHP());

		}
	}
}

void EnemyManager::spawnRandomEnemy()
{
	Enemy* ast = getInactive();
	if (ast == nullptr)
		return;
	ast->active = true;
	int randSides = Math::RandIntMinMax(0, 3);
	if (randSides == 0)//left
	{
		ast->pos.Set(GlobalVariables::get()->PlayableBox.min.x + GlobalVariables::get()->PlayableBox.mid.x,
			Math::RandFloatMinMax(GlobalVariables::get()->PlayableBox.min.y, GlobalVariables::get()->PlayableBox.max.y) + GlobalVariables::get()->PlayableBox.mid.y);
	}
	else if (randSides == 1)//top
	{
		ast->pos.Set(Math::RandFloatMinMax(GlobalVariables::get()->PlayableBox.min.x, GlobalVariables::get()->PlayableBox.max.x) + GlobalVariables::get()->PlayableBox.mid.x,
			GlobalVariables::get()->PlayableBox.max.y + GlobalVariables::get()->PlayableBox.mid.y);
	}
	else if (randSides == 2)//right
	{
		ast->pos.Set(GlobalVariables::get()->PlayableBox.max.x + GlobalVariables::get()->PlayableBox.mid.x,
			Math::RandFloatMinMax(GlobalVariables::get()->PlayableBox.min.y, GlobalVariables::get()->PlayableBox.max.y) + GlobalVariables::get()->PlayableBox.mid.y);
	}
	else if (randSides == 3)//bot
	{
		ast->pos.Set(Math::RandFloatMinMax(GlobalVariables::get()->PlayableBox.min.x, GlobalVariables::get()->PlayableBox.max.x) + GlobalVariables::get()->PlayableBox.mid.x,
			GlobalVariables::get()->PlayableBox.min.y + GlobalVariables::get()->PlayableBox.mid.y);
	}
	ast->reset();
}

void EnemyManager::disableEnemies()
{
	for (auto it : enemies) {
		it->active = false;
	}
}

Enemy* EnemyManager::getInactive()
{
	for (auto it : enemies)
	{
		if (it->active == false)
			return it;
	}
	return nullptr; //for now force crash if out of range
}