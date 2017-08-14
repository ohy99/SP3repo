#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <map>
#include "Scene.h"

class SceneManager
{
	bool shouldExit = false;
	std::map < std::string, Scene*> scenes;
	Scene* curr;
	SceneManager() {
	}
	static SceneManager* instance;
public:
	static SceneManager* getInstance() {
		if (!instance)
			instance = new SceneManager();
		return instance;
	}
	~SceneManager() {
		for each(auto p in scenes) {
			if (p.second)
			{
				p.second->Exit();
				delete p.second;
				p.second = nullptr;
			}
		}
	}
	void addScene(std::string key, Scene* a) {
		scenes[key] = a;
	}
	void update(double dt) {
		curr->Update(dt);
		curr->Render();
	}

	void setNextScene(std::string n) {
		curr->Exit();
		curr = scenes[n];
		curr->Init();
		curr->Update(0.0);
	}
	void setCurrScene(std::string a) {
		curr = scenes[a];
		curr->Init();
	}
	void setExitGame(bool a) {
		shouldExit = true;
	}
	bool checkShouldExit() {
		return shouldExit;
	}
};

#endif
