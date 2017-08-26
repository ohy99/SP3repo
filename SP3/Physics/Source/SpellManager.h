#pragma once
#include "Application.h"
#include <iostream>
#include "SingletonTemplate.h"

using namespace std;
class Character;
class DamageArea;
class GameObject;
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

	bool useLightningSpell();
	bool useFreezeSpell();
	bool useBlastSpell();
	bool useFireSpell();

	double getLcooldown();
	double getFcooldown();
	double getBcooldown();

	bool is_longkang_charging_active;
	bool is_longkang_active;
	double longkang_elasped;
	double longkang_chargeup;
	bool use_longkang_spell();
	float get_longkang_charge();
	void update_charging_longkang(double dt);
	double longkang_active_elapsed;
	double longkang_active_duration;
	void update_active_longkang(double dt);
	Character* character;
private:
	DamageArea* lightning;
	DamageArea* freeze;
	DamageArea* blast;
	DamageArea* fire;

	GameObject* longkang_charging_mesh;
	DamageArea* longkang;
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