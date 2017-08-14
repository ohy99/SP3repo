#ifndef _COLLECTIBLES_H
#define _COLLECTIBLES_H

#include "GameObj.h"
#include "RenderHelper.h"
#include "Graphics.h"

class Collectibles : public GameObj
{
public:
	virtual ~Collectibles(){}

	virtual void render() {
		Graphics::getInstance()->modelStack.PushMatrix();
		Graphics::getInstance()->modelStack.Translate(this->pos.x, this->pos.y, this->pos.z);
		Graphics::getInstance()->modelStack.Scale(this->scale.x, this->scale.y, this->scale.z);
		RenderHelper::RenderMesh(this->mesh, false);
		Graphics::getInstance()->modelStack.PopMatrix();
	}

	float activeElapsedTime = 0.f;
	float activeDuration;


	void reset() {
		activeElapsedTime = 0.f;
		isActivated = false;
		hasCalled = false;
	}
	bool checkStatus() {
		return isActivated && !this->active;
	}

	void incElapsed(float dt) {
		activeElapsedTime += dt;
	}
	bool checkValidation() {
		//return true if still running
		if (activeElapsedTime >= activeDuration)
		{
			reset();
			return false;
		}
		return true;
	}
	//Only method that enables use of collectible
	void setTaken() {
		this->active = false;
		setActivated();
	}

	float getActiveDuration() {
		return activeDuration;
	}
	void setEffectDone() {
		if (!hasCalled)
			hasCalled = true;
	}
	bool hasCalledBo() {
		return hasCalled;
	}
protected:
	bool isActivated;
	bool hasCalled;
	Collectibles(float ad) : activeDuration(ad){
		isActivated = false;
		hasCalled = false;
	}
	void setActivated() {
		isActivated = true;
	}
	void setActiveDuration(float ad) {
		this->activeDuration = ad;
	}
};



#endif
