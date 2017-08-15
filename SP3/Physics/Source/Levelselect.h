#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"

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

	Mesh* axis;
	//Mesh* background;
	float worldHeight;
	float worldWidth;
};

#endif