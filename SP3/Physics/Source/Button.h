#ifndef BUTTON_H
#define BUTTON_H

#include "UIObj.h"
//#include "GlobalVariableManager.h"

class Button : public UIObj
{
public:
	std::string text;
	Button(std::string a) {
		if (a == "START")
			mesh = EntityBase::getInstance()->getEntity("STARTBUTTON");
		else if (a == "BACK")
			mesh = EntityBase::getInstance()->getEntity("BACKBUTTON");
		else if (a == "INSTRUCTION")
			mesh = EntityBase::getInstance()->getEntity("INSTRUCTIONBUTTON");
		else if (a == "EXIT")
			mesh = EntityBase::getInstance()->getEntity("EXITBUTTON");
		//mesh->textureID = LoadTGA(a.c_str());
		text = a;
	}
	virtual ~Button(){}

	void update(double dt) {

	}
	void render() {
		Graphics::getInstance()->modelStack.PushMatrix();
		Graphics::getInstance()->modelStack.Translate(this->pos.x, this->pos.y, this->pos.z);
		Graphics::getInstance()->modelStack.Scale(this->scale.x, this->scale.y, 1);
		RenderHelper::RenderMesh(this->getMesh(), false);
		Graphics::getInstance()->modelStack.PopMatrix();

		//Graphics::getInstance()->modelStack.PushMatrix();
		//Graphics::getInstance()->modelStack.Translate(this->pos.x, this->pos.y, this->pos.z);
		//Graphics::getInstance()->modelStack.Scale(this->scale.x * 0.75f, this->scale.y * 0.75f, 1);
		//RenderHelper::RenderText(GlobalVariables::get()->text, text, Color(1, 1, 1));
		//Graphics::getInstance()->modelStack.PopMatrix();
	}
};

#endif
