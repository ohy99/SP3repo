#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"
#include "Button.h"
#include "AudioPlayer.h"
#include "CharacterInfo.h"

class Mesh;

class Levelselect : public Scene
{
public:
	Levelselect();
	~Levelselect();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;

	Button LevelSelect;
	Button Level1;
	Button Level2;
	Button Level3;
	Button Level4;
	Button Back;

	Mesh* axis;
	AudioPlayer audioPlayer;
	//Mesh* background;
	float worldHeight;
	float worldWidth;
};

#endif