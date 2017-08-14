#ifndef _ASTEROIDSMANAGER_H
#define _ASTEROIDSMANAGER_H

#include "Asteroid.h"
#include <vector>

class AsteroidManager
{

	const int defaultNumOfAsteroids = 100;

	static AsteroidManager* instance;
	AsteroidManager();

	Asteroid* getInactive();

	const float randInitialForceX = 100;
	const float randInitialForceY = 100;
	const float randMinMass = 5;
	const float randMaxMass = 100;

	float spawnDelay = 0.f;
	const float spawnDelayTrigger = 0.2f;
public:
	static AsteroidManager* getinstance();
	~AsteroidManager();
	void update(double dt);
	void render();

	void spawnRandomAsteroid();
	void disableAsteroids();
	
	
	std::vector<Asteroid*>asteroids;
};

#endif