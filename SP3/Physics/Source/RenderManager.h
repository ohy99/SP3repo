#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <map>

class GameObject;

class RenderManager :public Singleton<RenderManager>
{
	friend Singleton;
	std::map<int, std::vector<GameObject*> >objects;
public:
	void attach_renderable(GameObject* , int layer = 0);
	void render_all_active_objects();
protected:
	RenderManager();
	~RenderManager();
};

#endif // !RENDERMANAGER_H
