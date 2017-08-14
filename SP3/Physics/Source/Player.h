#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObj.h"
#include "ShipBase.h"
#include "Engine.h"

class Weapon;
class Camera;

class Player : public ShipBase
{
	static Player* instance;
	Player();
	
	float hp;
	const float MAXHP = 100;
	float moveSpd;
	float MAXSPD;
	const float defaultMAXSPD = 10;
	const float forcedMAXSPD = 500;

	//Vector3 torque;
	//Vector3 force;
	float momentOfInertia;
	float angularVelocity;

	const float DEFAULTWeapDmg = 5.f;
	Camera* cam;
	Weapon* weap;
	Weapon* weapHoming;

	Engine engines[4];

	bool engineBoost;
	const float boostCap = 2.f;
	float boostFuel;
	float rechargeRateMultiplierPerSec;
	const float DEFAULTRRMPS = 0.25f;

	bool dmgimmune;
	float dmgreduction;

	bool incdmg;

	Mesh* powerBulletPowerUp;
public:
	static Player* getInstance();
	~Player();

	void reset();

	void update(double dt);
	void render();

	void inputMovement(double dt);
	void updateKinematics(double dt);
	void updateCollisionBox();
	void updateWeapon(double dt);
	void updateBooster(double dt);
	void updateCheckPowerUp(double dt);

	void getHit(float dmg);

	void attachCamera(Camera* cam);
	inline void updateCamPos();

	float getHp(){
		return hp;
	}
};

#endif