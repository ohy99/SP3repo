#ifndef _BOOSTBAR_H
#define _BOOSTBAR_H

#include "UIObj.h"
#include "Graphics.h"
#include "RenderHelper.h"

class BoostBar : public UIObj
{
	Mesh* boostFuel;
	//float hpPercent;
	BoostBar() {
		mesh = EntityBase::getInstance()->getEntity("BOOSTBORDER");
		boostFuel = EntityBase::getInstance()->getEntity("BOOSTFUEL");
	}
	static BoostBar* instance;
public:
	static BoostBar* getInstance() {
		if (!instance)
			instance = new BoostBar();
		return instance;
	}

	virtual ~BoostBar() {}

	void update(float hpPercent) {

	}

	void render(float boostPercent = 1.f) {

		Graphics::getInstance()->modelStack.PushMatrix();
		//Graphics::getInstance()->modelStack.LoadMatrix(transformation);
		Graphics::getInstance()->modelStack.Translate(this->pos.x, this->pos.y, this->pos.z);
		//Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)) - 90.f, 0, 0, 1);
		Graphics::getInstance()->modelStack.PushMatrix();
		Graphics::getInstance()->modelStack.Scale(this->scale.x, this->scale.y, this->scale.z);
		RenderHelper::RenderMesh(this->getMesh(), false);
		Graphics::getInstance()->modelStack.PopMatrix();

		Graphics::getInstance()->modelStack.PushMatrix();
		Graphics::getInstance()->modelStack.Translate(-(1 - boostPercent) * this->scale.x * 0.5f, 0, 0);
		Graphics::getInstance()->modelStack.Scale(boostPercent * this->scale.x, this->scale.y, this->scale.z);
		RenderHelper::RenderMesh(boostFuel, false);
		Graphics::getInstance()->modelStack.PopMatrix();

		Graphics::getInstance()->modelStack.PopMatrix();
	}
};

#endif