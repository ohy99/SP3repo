#pragma once
#include "Application.h"
#include <iostream>
#include "SingletonTemplate.h"

using namespace std;

class DamageArea;
class SpellManager:public Singleton<SpellManager>
{
	friend Singleton;
public:
	void update(double dt);
	DamageArea* lightning;
	void useLightningSpell();

	int getQuantity();
	void setQuantity(int amt);

protected:
	SpellManager();
	virtual ~SpellManager();

	double lightningactivetime;

	int quantity;
};