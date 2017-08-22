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

	int getLQuantity();
	void setLQuantity(int amt);

	int getFQuantity();
	void setFQuantity(int amt);

	int getBQuantity();
	void setBQuantity(int amt);

	bool isFreezeActive();
	bool isBlastActive();

	void useLightningSpell();
	void useFreezeSpell();
	void useBlastSpell();

private:
	DamageArea* lightning;
	DamageArea* freeze;
	DamageArea* blast;

protected:
	SpellManager();
	virtual ~SpellManager();

	double lightningReuseTime;

	double freezeReuseTime;
	double freezeDuration;

	double blastReuseTime;
	double blastDuration;

	int lightningQuantity;
	int freezeQuantity;
	int blastQuantity;
};