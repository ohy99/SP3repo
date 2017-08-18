#pragma once
#include "Application.h"
#include <iostream>
using namespace std;
class Projectile;
class Spells
{
public:
	Spells();
	~Spells();

	int getLightningQuantity();
	void setLightningQuantity(int amt);

	void lightningSpell(double dt);
	void freezeSpell();
	void blastSpell();

	void renderSpells();

	
protected:
	int lightningQuantity;
	int freezeQuantity;
	int blastQuantity;

	Projectile* lightning;
	double lightningactivetime;
};