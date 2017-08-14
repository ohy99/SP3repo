
#ifndef ASCENE_H
#define ASCENE_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"

class Mesh;

class AScene : public Scene
{
public:
	AScene();
	~AScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;

	//Mesh* background;

};

#endif