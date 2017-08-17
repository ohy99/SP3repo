#ifndef WIN_H
#define WIN_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"
#include "AudioPlayer.h"
#include "CharacterInfo.h"

class Mesh;

class Win : public Scene
{
public:
	Win();
	~Win();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;

	Mesh* axis;
	//Mesh* background;
	float worldHeight;
	float worldWidth;
};

#endif
