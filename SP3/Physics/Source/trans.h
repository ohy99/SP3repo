#ifndef TRANS_H
#define TRANS_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"
#include "AudioPlayer.h"
#include "CharacterInfo.h"
#include "Shop.h"
#include "TowerManager.h"
class Mesh;

class Trans : public Scene
{
public:
	Trans();
	~Trans();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;

	Mesh* axis;
	double rj;
	AudioPlayer audioPlayer;
	//Mesh* background;
	float worldHeight;
	float worldWidth;
};

#endif