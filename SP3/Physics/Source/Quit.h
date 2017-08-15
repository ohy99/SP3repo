#ifndef QUIT_H
#define QUIT_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"

class Mesh;

class Quit : public Scene
{
public:
	Quit();
	~Quit();

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