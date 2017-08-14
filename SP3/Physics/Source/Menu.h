
#ifndef MENU_H
#define MENU_H

#include "Scene.h"
#include "Camera.h"
#include "FontType.h"

class GameObj;
class Mesh;
class UIObj;
class Menu : public Scene
{
public:
	Menu();
	~Menu();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;

	Mesh* background;
	UIObj* startbutton = nullptr;
	UIObj* insbutton = nullptr;
	UIObj* exitbutton = nullptr;

	void renderThing(GameObj* a);
	//template<class ButtonType, class FontType>
	//static GenerateButton<ButtonType, FontType> start;
	//
	//ButtonTypeStyle* bts;
	//FontType* ft;
};

#endif