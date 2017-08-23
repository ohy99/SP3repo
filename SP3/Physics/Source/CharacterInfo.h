//Char info.h
#pragma once
#include "Vector3.h"
#include <string>
#include "Consumables.h"
#include "Tower.h"
#include "Wallet.h"
#include "GameLogic.h"
#include "Weapon.h"
#include "RenderManager.h"
#include "MeshList.h"
#include "MinionManager.h"
#include "SpellManager.h"
using namespace std;
class Wallet;
class Character {

private:
	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 pos, target, up;

	//Health system//
	int maxhealth;
	int health;
	//Combat system//
	int damage;

	//Levels//
	int levels;

	//Ecnomoy & highscore//
	int coins;
	int highscore;
	//Irrklang stuff
	int soundtrack;

	bool mute;
	Wallet wallet;
	Weapon weap;
	float worldWidth;
	float worldHeight;
public:
	Character();
	~Character();

	//--------------------------Getters----------------------//
	int getlevel();
	int getmaxhealth();
	int getcurrenthealth();
	int getcurrentcoins();
	int getcurrenthighscore();
	int getcurrentst();
	Vector3 GetPos(void) const;
	// Get target
	Vector3 GetTarget(void) const;
	// Get Up
	Vector3 GetUp(void) const;

	Wallet & getWallet();


	//-----------------------Setters---------------------//
	void SetPos(const Vector3& pos);
	// Set target
	void SetTarget(const Vector3& target);
	// Set Up
	void SetUp(const Vector3& up);

	void setlevel(int);
	void setmaxhealth(int);
	void setcurrenthealth(int);
	void setcurrentcoins(int);
	void setcurrenthighscore(int);

	void setcurrentst(int);


	//Bool//
	bool Load(const string saveFileName = ".//Image//Stats.sav"); // .sav files
																  // Save this class
	bool Save(const string saveFileName = ".//Image//Stats.sav"); // .sav files


																  //---------------------Token Convers-----------------//
	Vector3 Token2Vector(const string token);
	double Token2Double(const string token);
	bool Token2Bool(const string token);



	//-----------Functions--------------------//
	void Update(double dt);
	void Init();
protected:


};