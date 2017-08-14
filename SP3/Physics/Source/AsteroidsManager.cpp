#include "AsteroidsManager.h"

#include "Mtx44.h"
#include "Graphics.h"
#include "RenderHelper.h"

#include "GlobalVariableManager.h"
#include "Player.h"

AsteroidManager::AsteroidManager()
{
	for (int i = 0; i < defaultNumOfAsteroids; ++i) {
		asteroids.push_back(new Asteroid());
	}
}

AsteroidManager::~AsteroidManager()
{
	for (auto it : asteroids)
	{
		delete it;
		it = nullptr;
	}

	//if (instance)
	//	delete instance;
	//instance = nullptr;
}

AsteroidManager* AsteroidManager::getinstance()
{
	if (!instance)
		instance = new AsteroidManager();
	return instance;
}

void AsteroidManager::update(double dt)
{
	for (auto it : asteroids)
	{
		if (it->active) {

			it->update(dt);

			if (it->hitDelay >= 1.f / it->hitattspd)
			{
				if (it->collision.isCollide(GlobalVariables::get()->player->collision)) {
					GlobalVariables::get()->player->getHit(it->getDmg());
				}
			}
			//for (auto p : *(GlobalVariables::get()->planetPointer)) {
			//	//if(p->a)
			//}
			//CANNOt include planet here because planet include me alr
			//i should have a higher level manager for planets as well
			//it->pos += it->vel * (float)dt;

		}
		
	}
	
	spawnDelay += (float)dt;
	if (spawnDelay >= spawnDelayTrigger)
	{
		spawnRandomAsteroid();
		spawnDelay = 0.f;
	}

}

void AsteroidManager::render() 
{
	for (auto it : asteroids) {

		if (it->active)
		{
			Mtx44 transformation(it->right.x * it->scale.x, it->right.y * it->scale.y, it->right.z * it->scale.z, 0,
				it->up.x * it->scale.x, it->up.y * it->scale.y, it->up.z * it->scale.z, 0,
				it->dir.x * it->scale.x, it->dir.y * it->scale.y, it->dir.z * it->scale.z, 0,
				it->pos.x, it->pos.y, it->pos.z, 1);

			Graphics::getInstance()->modelStack.PushMatrix();
			Graphics::getInstance()->modelStack.LoadMatrix(transformation);
			//Graphics::getInstance()->modelStack.Translate(it->pos.x, it->pos.y, it->pos.z);
			//Graphics::getInstance()->modelStack.Scale(5, 5, 5);
			RenderHelper::RenderMesh(it->getMesh(), false);
			Graphics::getInstance()->modelStack.PopMatrix();

			//pos + offset to up
			GlobalVariables::get()->hpbar->pos.Set(it->pos.x , it->pos.y + it->scale.y , it->pos.z);
			GlobalVariables::get()->hpbar->scale.Set(5.f, 1.5f, 1);
			GlobalVariables::get()->hpbar->render(it->gethp() / it->getMAXHP());

		}
	}
}

void AsteroidManager::spawnRandomAsteroid()
{
	Asteroid* ast = getInactive();
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
		ast->pos.Set( GlobalVariables::get()->PlayableBox.max.x + GlobalVariables::get()->PlayableBox.mid.x,
			Math::RandFloatMinMax(GlobalVariables::get()->PlayableBox.min.y, GlobalVariables::get()->PlayableBox.max.y) + GlobalVariables::get()->PlayableBox.mid.y);
	}
	else if (randSides == 3)//bot
	{
		ast->pos.Set(Math::RandFloatMinMax(GlobalVariables::get()->PlayableBox.min.x, GlobalVariables::get()->PlayableBox.max.x) + GlobalVariables::get()->PlayableBox.mid.x,
			GlobalVariables::get()->PlayableBox.min.y + GlobalVariables::get()->PlayableBox.mid.y);
	}
	
	ast->force.Set(Math::RandFloatMinMax(-randInitialForceX, randInitialForceX), Math::RandFloatMinMax(-randInitialForceY, randInitialForceY));
	ast->mass = Math::RandFloatMinMax(randMinMass, randMaxMass);
	float scale = Math::RandFloatMinMax(2, 10);
	ast->scale.Set(scale, scale, 1);
	ast->MAXHP = scale * 5;
	ast->reset();
}

void AsteroidManager::disableAsteroids()
{
	for (auto it : asteroids) {
		it->active = false;
	}
}

Asteroid* AsteroidManager::getInactive()
{
	for (auto it : asteroids)
	{
		if (it->active == false)
			return it;
	}
	return nullptr; //for now force crash if out of range
}