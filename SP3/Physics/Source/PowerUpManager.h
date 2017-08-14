#ifndef _POWERUPMANAGER_H
#define _POWERUPMANAGER_H

class Collectibles;
#include <map>
#include <vector>

class PowerUpManager
{
	PowerUpManager();
	static PowerUpManager* instance;
	const float chanceToSpawn = 0.2f;
	const int initialPowerupsPerType = 10;

	Collectibles* generateNewPowerUp(unsigned int a);
	Collectibles* getPowerUp(unsigned int a);
public:
	static PowerUpManager* getInstance();
	~PowerUpManager();

	enum PowerUpTypes
	{
		HPUP,
		BOOSTREGEN,
		INCDMG,
		DMGIMM,
		COUNT
	};

	unsigned int randPowerup();
	bool checkSpawn();
	Collectibles* getRandomPowerUp();
	void disablePowerUps();

	void update(double dt);
	void render();

	std::map<PowerUpTypes, std::vector<Collectibles*>> powerups;
};

#endif