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

	double getLcooldown();
	double getFcooldown();
	double getBcooldown();

private:
	DamageArea* lightning;
	DamageArea* freeze;
	DamageArea* blast;
	DamageArea* fire;

protected:
	SpellManager();
	virtual ~SpellManager();

	double lightningCooldown;
	double lightningReuseTime;

	double freezeCooldown;
	double freezeReuseTime;
	double freezeDuration;
		
	double blastCooldown;
	double blastReuseTime;
	double blastDuration;

	double fireCooldown;
	double fireReuseTime;

	//int lightningQuantity;
	//int freezeQuantity;
	//int blastQuantity;
};