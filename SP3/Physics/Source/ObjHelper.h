#ifndef OBJHELPER_H
#define OBJHELPER_H

#include "GameObj.h"
#include "Graphics.h"
#include "RenderHelper.h"

#define DEFAULTDIR Vector3(0,1,0)

#include <vector>

class ObjHelper
{
	static ObjHelper* instance;
	std::vector<GameObj*> objs_;
	ObjHelper() {}
public:
	static ObjHelper* getInstance() {
		if (!instance)
			instance = new ObjHelper();
		return instance;
	}
	~ObjHelper() {
		for (std::vector< GameObj* >::iterator it = objs_.begin(); it != objs_.end(); ++it)
		{
			delete (*it);
		}
		objs_.clear();

		//if (instance)
		//{
		//	delete instance;
		//	instance = NULL;
		//}
	}

	void addObj(GameObj* a) {
		objs_.push_back(a);
	}

	void renderObj() {
		for (auto it : objs_)
		{
			Mtx44 transformation(it->right.x * it->scale.x, it->right.y * it->scale.y, it->right.z * it->scale.z, 0,
				it->up.x * it->scale.x, it->up.y * it->scale.y, it->up.z * it->scale.z, 0,
				it->dir.x * it->scale.x, it->dir.y * it->scale.y, it->dir.z * it->scale.z, 0,
				it->pos.x, it->pos.y, it->pos.z, 1);

			Graphics::getInstance()->modelStack.PushMatrix();
			Graphics::getInstance()->modelStack.LoadMatrix(transformation);
			RenderHelper::RenderMesh(it->getMesh(), false);
			Graphics::getInstance()->modelStack.PopMatrix();
		}
	}
};


#endif