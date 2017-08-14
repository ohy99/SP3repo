#ifndef _GAMEOBJ_H
#define _GAMEOBJ_H

#include "Mesh.h"
#include "Vector3.h"
#include "EntityBase.h"
#include "Collision.h"
#include "RenderHelper.h"
#include "Graphics.h"


class GameObj abstract
{

public:
	Vector3 pos;
	Vector3 dir;
	Vector3 up;
	Vector3 right;
	Vector3 scale;

	Vector3 vel;
	float mass;

	bool active;

	GameObj() {
		pos.Set(0, 0, 0);
		dir.Set(0, 0, 1);
		up.Set(0, 1, 0);
		right.Set(1, 0, 0);
		scale.Set(1, 1, 1);

		vel.SetZero();
		mass = 1.f;

		active = false;
	}
	virtual ~GameObj() {}

	Mesh* getMesh() {
		return mesh;
	}

	Collision collision;

	virtual void update(double dt) {}
	virtual void render() {
		MS& ms = Graphics::getInstance()->modelStack;

		ms.PushMatrix();
		ms.Translate(this->pos);
		if (up.y != 1.f)
		ms.Rotate(Math::RadianToDegree(atan2(this->up.y, this->up.x)) - 90.f, 0, 0, 1);//rotate along the z axis.
		ms.Scale(this->scale);
		RenderHelper::RenderMesh(this->mesh, false);
		ms.PopMatrix();
	}
	Mesh* mesh;

	virtual void deactivate() {
		this->active = false;
	}
protected:
};

#endif