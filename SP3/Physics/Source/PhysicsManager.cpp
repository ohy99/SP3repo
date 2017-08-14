#include "PhysicsManager.h"

#include "GameObj.h"
#include "GameLogic.h"

PhysicsManager::PhysicsManager() {

}
PhysicsManager::~PhysicsManager() {

}

void PhysicsManager::update(double dt) {
	//const static Vector3 gravity(0, -9.8f, 0);
	if (GameLogic::GetInstance()->slow_down)
		dt /= 3.0;

	for each (auto const &go in gameobjs)
	{
		if (go->active == false)
			continue;
		//go->vel = go->vel + gravity * (float)dt;
		if (go->vel.LengthSquared() > ball_max_speed * ball_max_speed)
			go->vel = go->vel.Normalize() * ball_max_speed;
		
		go->pos += go->vel * (float)dt;
	}
}
void PhysicsManager::add_obj(GameObj* go) {
	this->gameobjs.push_back(go);
}

void PhysicsManager::set_ball_max_speed(float& ball_max_speed)
{
	this->ball_max_speed = ball_max_speed;
}

void PhysicsManager::exert_external_force_on_all_obj(Vector3 pos_of_thing)
{
	for each (auto const &go in gameobjs)
	{
		if (go->active == false)
			continue;

		Vector3 dist = pos_of_thing - go->pos;
		float length_sq = dist.LengthSquared();
		if (length_sq < 3.f * 3.f)
		{
			dist = go->vel;
			//too near, go straight and ignore gravity
		}
		double G = 1.0;
		double MofThing = 100.0;
		double F = G * (MofThing * 1.0) / Math::Min((double)length_sq, 125.0);
		try {
			go->vel += dist.Normalize() * F;
		}
		catch (DivideByZero&) {
			go->vel;
		}
	}
}