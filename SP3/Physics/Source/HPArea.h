#ifndef HPAREA_H
#define HPAREA_H

#include "CollidableObj.h"
#include "HpBar.h"
#include "GlobalVariableManager.h"
class HPArea : public CollidableObj
{
	int max_hp;
	int max_overheal;
public:
	int hp;
	HPArea() {
		GameObj::collision.collisionType = Collision::AABB;
		GameObj::collision.mid = &this->pos;
		GameObj::collision.min.Set(-this->scale.x * 0.5f, -this->scale.y * 0.5f);
		GameObj::collision.max.Set(this->scale.x * 0.5f, this->scale.y * 0.5f);
		this->hp = 0;

		this->collision_type = COLLISION_TYPE::HPAREA;
	}
	~HPArea() {

	}

	void set_max_hp(int a) {
		max_hp = a;
		max_overheal = max_hp * 2;
	}

	void collision_response(double dt, CollidableObj* other) {
		if (other->collision_type != CollidableObj::COLLISION_TYPE::BALL)
			return;

		//if collided is ball or brick
		switch (other->collision_type) {
		case CollidableObj::COLLISION_TYPE::BALL:
		{
			if (other->faction == this->faction) {
				//HEAL!
				other->active = false;
				this->hp = Math::Min(this->hp + 1, max_overheal);
			}
			else
			{
				//OUCH!
				other->active = false;
				this->hp = Math::Max(this->hp - 2, 0);
			}

		}
			break;
		}

		//std::cout <<  this->faction << " : " << this->hp << std::endl;
	}

	void update(double dt) {
		GameObj::collision.min.Set(-this->scale.x * 0.5f, -this->scale.y * 0.5f);
		GameObj::collision.max.Set(this->scale.x * 0.5f, this->scale.y * 0.5f);
	}

	void render() {
		//GameObj::render();
		HpBar* temp = HpBar::GetInstance();
		GlobalVariables* gv = GlobalVariables::get();
		if (this->pos.y < 0)
			temp->pos.Set(0, -*gv->worldHeight * 0.45f);
		else
			temp->pos.Set(0, *gv->worldHeight * 0.45f);

		temp->scale.Set(20, 3);
		temp->render((float)hp / (float)max_hp);
		//temp->render(3.f);
	}
};

#endif // !HPAREA_H
