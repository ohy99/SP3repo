
#ifndef _EndGame_H
#define _EndGame_H

#include "Scene.h"
#include "Camera.h"
#include "FontType.h"

class GameObj;
class Mesh;
class UIObj;
class EndGame : public Scene
{
public:
	EndGame();
	~EndGame();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;

	Mesh* background;
	UIObj* backbutton = nullptr;
	std::string endGameText;
	void renderThing(GameObj* a);
	//template<class ButtonType, class FontType>
	//static GenerateButton<ButtonType, FontType> start;
	//
	//ButtonTypeStyle* bts;
	//FontType* ft;
};

#endif