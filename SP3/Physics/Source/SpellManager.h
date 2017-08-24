#pragma once
#include "Application.h"
#include <iostream>
#include "SingletonTemplate.h"

using namespace std;

class DamageArea;
class SpellManager :public Singleton<SpellManager>
{
	friend Singleton;
public:
	void update(double dt);

	//int getLQuantity();
	//void setLQuantity(int amt);

	//int getFQuantity();
	//void setFQuantity(int amt);

	//int getBQuantity();
	//void setBQuantity(int amt);

	bool isFreezeActive();
	bool isBlastActive();

	void useLightningSpell();
	void useFreezeSpell();
	void useBlastSpell();
	void useFireSpell();

private:
	DamageArea* lightning;
	DamageArea* freeze;
	DamageArea* blast;
	DamageArea* fire;

protected:
	SpellManager();
	virtual ~SpellManager();

	double lightningReuseTime;

	double freezeReuseTime;
	double freezeDuration;

	double blastReuseTime;
	double blastDuration;

	double fireReuseTime;

	//int lightningQuantity;
	//int freezeQuantity;
	//int blastQuantity;
};