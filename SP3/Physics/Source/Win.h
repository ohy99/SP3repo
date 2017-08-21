#ifndef WIN_H
#define WIN_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"
#include "Button.h"
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
	Button title;
	Mesh* quit;
	Mesh* option;
	Button playbutt;
	Button optionbutt;
	Button quitbutt;
	Button levelselectbutt;
	AudioPlayer audioPlayer;
	//Mesh* background;
	float worldHeight;
	float worldWidth;
};

#endif