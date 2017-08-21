#pragma once
#include "Application.h"
#include <iostream>
#include "SingletonTemplate.h"

using namespace std;

class Projectile;
class SpellManager:public Singleton<SpellManager>
{
public:
	friend Singleton;
	void update(double dt);
	Projectile* lightning;

protected:
	SpellManager();
	virtual ~SpellManager();

	double lightningactivetime;
};