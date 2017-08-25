//GameScene_H


#ifndef GameScene_H
#define GameScene_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"
#include "AudioPlayer.h"
#include "CharacterInfo.h"
#include "Shop.h"
#include "TowerManager.h"
class Mesh;

#include "Weapon.h"
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;
	AudioPlayer audioPlayer;
	Mesh* axis;
	Mesh* pausescreen;
	Character CharacterInfo;
	//Mesh* background;
	float worldHeight;
	float worldWidth;
	bool isPause;
	bool isShop;
	bool isFreeze;
	Weapon weap;
	Shop shop;
};

#endif