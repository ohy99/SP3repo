#ifndef BALL_H
#define BALL_H

#include "CollidableObj.h"
#include "GlobalVariableManager.h"
#include "Bricks.h"

class Ball : public CollidableObj
{
public:
	Ball() {
		this->collision_type = COLLISION_TYPE::BALL;

		this->mesh = EntityBase::getInstance()->getEntity("BALL");
		default_ball = this->mesh;
		enemy_ball = EntityBase::getInstance()->getEntity("ENEMYBALL");
		player_ball = EntityBase::getInstance()->getEntity("PLAYERBALL");

		faction = PLAYER;

		GameObj::collision.collisionType = Collision::SPHERE;
		GameObj::collision.mid = &(this->pos);
		GameObj::collision.radius = this->scale.x * 0.5f;
	}
	virtual ~Ball() {

	}
	
	virtual void collision_response(double dt, CollidableObj* other) {

		if (collided_at_this_frame == true)
			return;

		//if ball and other are both enemy, dont collide
		if (this->faction == CollidableObj::FACTION_SIDE::ENEMY &&
			this->faction == other->faction)
			return;
		
		//player-player still collide
		if (other->collision_type == CollidableObj::COLLISION_TYPE::BRICK) {
			Bricks* temp_brick = dynamic_cast<Bricks*>(other);
			for (int i = 0; i < Bricks::COLLIDERS::COLLIDERCOUNT; ++i) {
				CollidableObj* temp_inside = temp_brick->collision[i];
				this->collision_response(dt, temp_inside);
				if (this->collided_at_this_frame)
					break;
			}
			//this->collided_at_this_frame = true;
			return;
		}
		Vector3 prev_vel = this->vel;
		switch (other->collision_type)
		{
		case CollidableObj::COLLISION_TYPE::BALL:
		{
			//BALL - BALL
			float m1 = this->mass;
			float m2 = other->mass;
			Vector3 u1 = this->vel;
			Vector3 u2 = other->vel;
			Vector3 normalAxis = (other->pos - this->pos).Normalize();

			this->vel = u1 + (2.0 * m2 / (m1 + m2)) * (u2.Dot(normalAxis) * normalAxis - u1.Dot(normalAxis) * normalAxis);
			other->vel = u2 + (2.0 * m1 / (m2 + m1)) * (u1.Dot(normalAxis) * normalAxis - u2.Dot(normalAxis) * normalAxis);
		}
		break;
		case CollidableObj::COLLISION_TYPE::WALL:
		{
			//Vector3 ball_to_wall = -this->pos + other->pos;
			//Wall* wall = dynamic_cast<Wall*>(other);
			//Vector3 N = other->normal;
			Vector3 relative_position = this->pos - other->pos;
			//if (relative_position.Dot(N) > 0)
			//	N = -N;
			
			//check position from the wall normal
			Vector3 normal_perpendicular = other->normal.Cross(Vector3(0, 0, 1)).Normalize();
			Vector3 position_projection = ( relative_position.Dot(normal_perpendicular) ) * normal_perpendicular;
			if (position_projection.LengthSquared() > other->scale.x * 0.5f * other->scale.x * 0.5f)
				break;
			//if (this->pos)

			this->vel = this->vel - (2.f * this->vel.Dot(other->normal)) * other->normal;
			//this->vel = this->vel - (2.f * this->vel.Dot(N)) * N;
			
		}
		break;
		case CollidableObj::COLLISION_TYPE::PILLAR:
		{
			Vector3 normal = -other->pos + this->pos;
			normal.Normalize();

			this->vel = this->vel - (2.f * this->vel.Dot(normal)) * normal;
		}
		break;
		};

		if (prev_vel != this->vel)
		CollidableObj::collided_at_this_frame = true;


	};

	virtual void render() {
		//check whose ball
		switch (this->faction)
		{
		case CollidableObj::FACTION_SIDE::FS_NONE:
			this->mesh = this->default_ball;
			break;
		case CollidableObj::FACTION_SIDE::PLAYER:
			this->mesh = this->player_ball;
			break;
		case CollidableObj::FACTION_SIDE::ENEMY:
			this->mesh = this->enemy_ball;
			break;
		}

		GameObj::render();
	}
	
	virtual void update(double dt) {
		float exitx = *GlobalVariables::get()->worldWidth * 0.5f;
		float exity = *GlobalVariables::get()->worldHeight * 0.5f;

		if (this->pos.x < -exitx || this->pos.x > exitx || 
			this->pos.y < -exity * 1.5f|| this->pos.y > exity * 1.5f)
				this->active = false;
		
		//0ffset 0.6f
		GameObj::collision.radius = this->scale.x * 1.f;
	}


	Mesh* default_ball;
	Mesh* enemy_ball;
	Mesh* player_ball;
};

#endif // !BALL_H
