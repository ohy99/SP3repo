#pragma once
#include "Spells.h"
#include "Application.h"
#include "SpellManager.h"
#include <iostream>

using namespace std;

class Projectile;
class LightningSpell : public Spells, public SpellManager
{
public:
	LightningSpell();
	~LightningSpell();

	void useLightningSpell();
	void renderSpell();

protected:
	//Projectile* lightning;
	double lightningactivetime;
};