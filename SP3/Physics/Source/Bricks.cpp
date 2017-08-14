#include "Bricks.h"
#include "GameObjManager.h"
#include "Turret.h"
#include "Wall.h"
#include "Pillar.h"

Bricks::Bricks(bool include_turret) {
	is_player_platform = false;

	GameObj::collision.collisionType = Collision::AABB;
	GameObj::collision.min.Set(-scale.x * 0.5f, -scale.y * 0.5f);
	GameObj::collision.max.Set(scale.x * 0.5f, scale.y * 0.5f);
	GameObj::collision.mid = &this->pos;

	this->collision_type = COLLISION_TYPE::BRICK;
	this->is_collidable = true;
	this->faction = CollidableObj::FACTION_SIDE::ENEMY;

	normal_up.Set(0, 1, 0);
	normal_right.Set(1, 0, 0);
	this->mesh = EntityBase::getInstance()->getEntity("BRICK");


	Wall* temp = new Wall(false);
	temp->pos = this->pos;
	temp->normal = normal_up;
	temp->collision_type = CollidableObj::WALL;
	temp->scale = this->scale;
	temp->parent = this;
	temp->faction = CollidableObj::FACTION_SIDE::ENEMY;
	collision[COLLIDERS::UPWALL] = temp;

	temp = new Wall(false);
	temp->pos = this->pos;
	temp->normal = normal_right;
	temp->collision_type = CollidableObj::WALL;
	temp->parent = this;
	temp->faction = CollidableObj::FACTION_SIDE::ENEMY;
	temp->scale.Set(this->scale.y, this->scale.x);
	//temp->scale = this->scale;
	collision[COLLIDERS::RIGHTWALL] = temp;

	pillars_pos[0].Set(-this->scale.x * 0.5f, this->scale.y * 0.5f);
	pillars_pos[1].Set(this->scale.x * 0.5f, this->scale.y * 0.5f);
	pillars_pos[2].Set(this->scale.x * 0.5f, -this->scale.y * 0.5f);
	pillars_pos[3].Set(-this->scale.x * 0.5f, -this->scale.y * 0.5f);

	for (int i = 0; i < 4; ++i)
	{
		Pillar* tempp = new Pillar(false);
		tempp->pos = this->pos + pillars_pos[i];
		//tempp->radius = 0.f;
		tempp->scale.Set(0, 0, 0);
		tempp->collision_type = CollidableObj::PILLAR;
		tempp->parent = this;
		tempp->faction = CollidableObj::FACTION_SIDE::ENEMY;
		collision[COLLIDERS::TLPILLAR + i] = tempp;
	}


	//Pillar* temp_pillar = new Pillar(false);
	//temp_pillar->pos = this->pos;
	//temp_pillar->pos.x = this->pos.x + -collision[COLLIDERS::UPWALL]->scale.x * 0.5f;
	//temp_pillar->collision_type = CollidableObj::PILLAR;
	//temp_pillar->scale.Set(this->scale.y * 0.5f, this->scale.y *0.5f);
	//temp_pillar->parent = this;
	//temp->faction = CollidableObj::FACTION_SIDE::ENEMY;
	//collision[COLLIDERS::LPILLAR] = temp_pillar;

	//temp_pillar = new Pillar(false);
	//temp_pillar->pos = this->pos;
	//temp_pillar->pos.x = this->pos.x + collision[COLLIDERS::UPWALL]->scale.x * 0.5f;
	//temp_pillar->collision_type = CollidableObj::PILLAR;
	//temp_pillar->scale.Set(this->scale.y * 0.5f, this->scale.y *0.5f);
	//temp_pillar->parent = this;
	//temp->faction = CollidableObj::FACTION_SIDE::ENEMY;
	//collision[COLLIDERS::RPILLAR] = temp_pillar;

	//for (int i = 0; i < COLLIDERS::COLLIDERCOUNT; ++i)
	//	CollisionManager::GetInstance()->add_collider_obj(collision[i]);

	is_static = false;

	//Controlling turret
	turret = nullptr;
	if (include_turret)
	{
		turret = new Turret();
		turret->parent = this;
	}
}
Bricks::~Bricks() {
	for (int i = 0; i < COLLIDERCOUNT; ++i)
	{
		delete collision[i];
		collision[i] = nullptr;
	}

	if (turret)
		delete turret;
}

void Bricks::update(double dt) {

	collision[COLLIDERS::UPWALL]->pos = this->pos;
	collision[COLLIDERS::UPWALL]->scale = this->scale;
	collision[COLLIDERS::RIGHTWALL]->pos = this->pos;
	collision[COLLIDERS::RIGHTWALL]->scale.Set(this->scale.y, this->scale.x);
	//collision[COLLIDERS::RIGHTWALL]->scale = this->scale;

	pillars_pos[0].Set(-this->scale.x * 0.5f, this->scale.y * 0.5f);
	pillars_pos[1].Set(this->scale.x * 0.5f, this->scale.y * 0.5f);
	pillars_pos[2].Set(this->scale.x * 0.5f, -this->scale.y * 0.5f);
	pillars_pos[3].Set(-this->scale.x * 0.5f, -this->scale.y * 0.5f);

	
	//collision[COLLIDERS::LPILLAR]->pos = this->pos;
	//collision[COLLIDERS::LPILLAR]->pos.x = this->pos.x + -collision[COLLIDERS::UPWALL]->scale.x * 0.5f;
	//collision[COLLIDERS::RPILLAR]->pos = this->pos;
	//collision[COLLIDERS::RPILLAR]->pos.x = this->pos.x + collision[COLLIDERS::UPWALL]->scale.x * 0.5f;
	for (int i = 0; i < 4; ++i)
	{
		collision[COLLIDERS::TLPILLAR + i]->pos = this->pos + pillars_pos[i];
	}

	for (int i = 0; i < COLLIDERS::COLLIDERCOUNT; ++i)
	{
		collision[i]->active = this->active;
		collision[i]->faction = this->faction;
	}

	if (this->is_collidable == false && this->active == true)
	{
		//trigger shrinking exit
		static Vector3 shrink_spd = this->scale * 0.5f;//shrink spd is default scale
		this->scale -= shrink_spd * (float)dt;
		if (this->scale.x <= 0 || this->scale.y <= 0)
			this->deactivate();
	}

	//Turret part
	if (this->turret)
		this->turret->update(dt);

	GameObj::collision.min.Set(-scale.x * 0.5f, -scale.y * 0.5f);
	GameObj::collision.max.Set(scale.x * 0.5f, scale.y * 0.5f);
}

void Bricks::deactivate() {
	this->active = false;
	for (int i = 0; i < COLLIDERS::COLLIDERCOUNT; ++i)
	{
		collision[i]->active = this->active;
	}
	if (turret)
		turret->active = this->active;
}

void Bricks::collision_response(double dt, CollidableObj* other) {

	//friendly no collide
	if (this->faction == other->faction)
		return;

	switch (other->collision_type)
	{
	case CollidableObj::COLLISION_TYPE::BALL:
	{
		if (is_player_platform == true)
		{
			//if ball hit me, i convert it to mine
			other->faction = this->faction;
			break;
		}

		if (is_static == true)
			break;

		this->is_collidable = false;
		for (int i = 0; i < COLLIDERS::COLLIDERCOUNT; ++i)
			collision[i]->is_collidable = false;
	}
	break;
	}
}

bool Bricks::check_collision(CollidableObj* ball) {

	for (int i = 0; i < COLLIDERS::COLLIDERCOUNT; ++i)
	{
		CollidableObj* other = collision[i];
		if (ball->collision_type == CollidableObj::COLLISION_TYPE::BALL &&
			other->collision_type == CollidableObj::COLLISION_TYPE::WALL)
		{
			Vector3 ball_to_wall = other->pos - ball->pos;
			Vector3 normal_perpendicular = other->normal.Cross(Vector3(0, 0, 1)).Normalize();
			Vector3 relative_position = ball->pos - other->pos;
			Vector3 N = other->normal;

			if (relative_position.Dot(N) > 0)
				N = -N;
			if (ball->vel.Dot(N) > 0 && abs(ball_to_wall.Dot(N)) < ball->scale.x + other->scale.y * 0.5f &&
				abs(ball_to_wall.Dot(normal_perpendicular)) < ball->scale.x + other->scale.x * 0.5f)
				return true;
		}
		if (ball->collision_type == CollidableObj::COLLISION_TYPE::BALL &&
			other->collision_type == CollidableObj::COLLISION_TYPE::PILLAR)
		{
			Vector3 normal = (other->pos - ball->pos).Normalize();

			if (ball->vel.Dot(normal) > 0 && (other->pos - ball->pos).LengthSquared() <
				(ball->scale.x + other->scale.x) * (ball->scale.x + other->scale.x))
				return true;
		}
	}

	return false;
}

void Bricks::render() {
	GameObj::render();
	if (turret)
		turret->render();
}




//temp = new Wall(false);
//temp->pos = this->pos;
//temp->normal = normal_right;
//temp->collision_type = CollidableObj::WALL;
//temp->parent = this;
//temp->faction = CollidableObj::FACTION_SIDE::ENEMY;
//temp->scale.Set(this->scale.y, this->scale.x);
////temp->scale = this->scale;
//collision[COLLIDERS::RIGHTWALL] = temp;

//pillars_pos[0].Set(-this->scale.x * 0.5f, this->scale.y * 0.5f);
//pillars_pos[1].Set(this->scale.x * 0.5f, this->scale.y * 0.5f);
//pillars_pos[2].Set(this->scale.x * 0.5f, -this->scale.y * 0.5f);
//pillars_pos[3].Set(-this->scale.x * 0.5f, -this->scale.y * 0.5f);

//for (int i = 0; i < 4; ++i)
//{
//	Pillar* tempp = new Pillar(false);
//	tempp->pos = this->pos + pillars_pos[i];
//	//tempp->radius = 0.f;
//	tempp->scale.Set(0, 0, 0);
//	tempp->collision_type = CollidableObj::PILLAR;
//	tempp->parent = this;
//	tempp->faction = CollidableObj::FACTION_SIDE::ENEMY;
//	collision[COLLIDERS::TLPILLAR + i] = tempp;
//}
