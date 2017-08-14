
#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "Scene.h"
#include "Camera.h"
#include "FontType.h"

class GameObj;
class Mesh;
class UIObj;
class Instructions : public Scene
{
public:
	Instructions();
	~Instructions();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;

	Mesh* background;
	Mesh* Inst;
	UIObj* backbutton = nullptr;

	void renderThing(GameObj* a);
	//template<class ButtonType, class FontType>
	//static GenerateButton<ButtonType, FontType> start;
	//
	//ButtonTypeStyle* bts;
	//FontType* ft;
};

#endif