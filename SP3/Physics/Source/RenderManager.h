#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "SingletonTemplate.h"
#include <vector>

class GameObject;

class RenderManager :public Singleton<RenderManager>
{
	friend Singleton;
	std::vector<GameObject*> objects;
public:
	void attach_renderable(GameObject*);
	void render_all_active_objects();
protected:
	RenderManager();
	~RenderManager();
};

#endif // !RENDERMANAGER_H
