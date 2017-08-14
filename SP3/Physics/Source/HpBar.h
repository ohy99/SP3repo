#ifndef _HPBAR_H
#define _HPBAR_H

#include "UIObj.h"
#include "Graphics.h"
#include "RenderHelper.h"
#include "SingletonTemplate.h"

class HpBar : public UIObj, public Singleton<HpBar>
{
	friend Singleton;
	Mesh* greenBar;
	//float hpPercent;
	HpBar() {
		mesh = EntityBase::getInstance()->getEntity("REDHPBAR");
		greenBar = EntityBase::getInstance()->getEntity("GREENHPBAR");
	}
public:

	virtual ~HpBar() {
		//delete greenBar;
		//greenBar = nullptr;
	}

	void update(float hpPercent) {

	}

	void render(float hpPercent = 1.f) {

		Graphics::getInstance()->modelStack.PushMatrix();
		//Graphics::getInstance()->modelStack.LoadMatrix(transformation);
		Graphics::getInstance()->modelStack.Translate(this->pos.x, this->pos.y, this->pos.z);
		//Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)) - 90.f, 0, 0, 1);
		Graphics::getInstance()->modelStack.PushMatrix();
		Graphics::getInstance()->modelStack.Scale(this->scale.x, this->scale.y, this->scale.z);
		RenderHelper::RenderMesh(this->getMesh(), false);
		Graphics::getInstance()->modelStack.PopMatrix();

		Graphics::getInstance()->modelStack.PushMatrix();
		Graphics::getInstance()->modelStack.Translate(-(1.f - hpPercent) * this->scale.x * 0.5f, 0, 0);
		Graphics::getInstance()->modelStack.Scale(hpPercent * this->scale.x, this->scale.y, this->scale.z);
		RenderHelper::RenderMesh(greenBar, false);
		Graphics::getInstance()->modelStack.PopMatrix();

		Graphics::getInstance()->modelStack.PopMatrix();
	}
};

#endif