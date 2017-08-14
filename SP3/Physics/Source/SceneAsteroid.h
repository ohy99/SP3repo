#ifndef SCENE_ASTEROID_H
#define SCENE_ASTEROID_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

class SceneAsteroid : public SceneBase
{
	static const int MAX_SPEED = 10;
	static const int BULLET_SPEED = 50;
	static const int MISSILE_SPEED = 20;
	static const int MISSILE_POWER = 1;

public:
	SceneAsteroid();
	~SceneAsteroid();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);

	GameObject* FetchGO();
protected:

	//Physics
	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ship;
	Vector3 m_force;
	Vector3 m_torque;

	int m_objectCount;
	int m_lives;
	int m_score;


	int NumOfBullets;
	int NumOfMissiles;
	float rotateAngle;
	Vector3 rotateAbout;

	void spawnBullet();
	void spawnMissle();
	void spawnAsteroid();
	void mouseControl();

	void initShip();
	void updateShip(double dt);

	void updateAsteroid(GameObject* go, double dt);
	void updateShipBullet(GameObject* go, double dt);
	void updateShipMissile(GameObject* go, double dt);
	void updateEnemyShip(GameObject* go, double dt);
	bool allShoot;
	void updateEnemyBullet(GameObject* go, double dt);
	GameObject* EnemyLockedOn;

	void renderTexts();


};

#endif