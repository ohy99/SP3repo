#include "PowerUpManager.h"
#include "MyMath.h"
#include "GlobalVariableManager.h"

#include "HpUp.h"
#include "BoostUp.h"
#include "IncDmg.h"
#include "DmgImm.h"

PowerUpManager::PowerUpManager() {
	for (int i = 0; i < PowerUpTypes::COUNT; ++i)
	{
		for (int j = 0; j < initialPowerupsPerType; ++j)
		{
			PowerUpTypes a = static_cast<PowerUpTypes>(i);
			powerups[a].push_back(generateNewPowerUp(i));
		}
	}
}

PowerUpManager::~PowerUpManager() {
	for each (std::pair<PowerUpTypes, std::vector<Collectibles*>> a in powerups)
	{
		for each(Collectibles* v in a.second)
		{
			delete v;
			v = nullptr;
		}
	}
}

PowerUpManager* PowerUpManager::getInstance() {
	if (!instance)
		instance = new PowerUpManager();
	return instance;
}

unsigned int PowerUpManager::randPowerup()
{
	return Math::RandIntMinMax(0, PowerUpTypes::COUNT - 1);
}

bool PowerUpManager::checkSpawn() {
	return this->chanceToSpawn >= Math::RandFloatMinMax(0.f, 1.f);
}

void PowerUpManager::update(double dt)
{
	for (auto pu : powerups)
	{
		for (auto v : pu.second)
		{
			if (v->active)
			{
				v->collision.mid = v->pos;
				if (!v->collision.isCollide(GlobalVariables::get()->PlayableBox))
				{
					v->active = false;
				}
			}
		}
	}

}
void PowerUpManager::render()
{
	for (auto pu : powerups)
	{
		for each (Collectibles* v in pu.second)
		{
			if (v->active)
			{
				Graphics::getInstance()->modelStack.PushMatrix();
				Graphics::getInstance()->modelStack.Translate(v->pos.x, v->pos.y, v->pos.z);
				Graphics::getInstance()->modelStack.Scale(v->scale.x, v->scale.y, v->scale.z);
				RenderHelper::RenderMesh(v->getMesh(), false);
				Graphics::getInstance()->modelStack.PopMatrix();
			}
		}
	}
}

Collectibles* PowerUpManager::getPowerUp(unsigned int a)
{
	for (auto it : powerups)
	{
		for (auto v : it.second)
		{
			if (it.first == static_cast<PowerUpTypes>(a) && !v->active)
			{
				return v;
			}
		}
	}

	return nullptr;
}

void PowerUpManager::disablePowerUps()
{
	for each (std::pair<PowerUpTypes, std::vector<Collectibles*>> a in powerups)
	{
		for each(Collectibles* v in a.second)
		{
			v->active = false;
		}
	}
}


Collectibles* PowerUpManager::getRandomPowerUp()
{
	return getPowerUp(randPowerup());
}

Collectibles* PowerUpManager::generateNewPowerUp(unsigned int a)
{

	if (a == PowerUpTypes::HPUP)
		return new HpUp();
	else if (a == PowerUpTypes::BOOSTREGEN)
		return new BoostUp();
	else if (a == PowerUpTypes::INCDMG)
		return new IncDmg();
	else if (a == PowerUpTypes::DMGIMM)
		return new DmgImm();
	return nullptr;
}