#include "Projectile.h"

#include "Minion.h"
#include "Tower.h"
#include "ObjectPoolManager.h"
#include "ParticleManager.h"

Projectile::Projectile() : velocity(0,0,0), dmg(0), mass(1.f),
	start_timer(false), active_remaining_elapsed_timer(0.0), active_remaining_duration(1.f)
{
}
Projectile::~Projectile()
{
}

void Projectile::update(double dt)
{
	if (!start_timer)
		return;

	active_remaining_elapsed_timer = Math::Min(active_remaining_elapsed_timer + dt, active_remaining_duration);

	if (active_remaining_elapsed_timer >= active_remaining_duration)
	{
		this->active = false;
		active_remaining_elapsed_timer = 0.0;
		start_timer = false;
		this->set_isCollidable(true);
	}
}

void Projectile::set_dmg(int dmg)
{
	this->dmg = dmg;
}
int Projectile::get_dmg()
{
	return dmg;
}

void Projectile::set_mass(float mass)
{
	this->mass = mass;
}

float Projectile::get_mass()
{
	return mass;
}

void Projectile::collision_response(Collidable* obj)
{
	//add projectile animation sprite
	if (obj->get_faction_side() == this->get_faction_side())
		return;
	Minion* temp_minion = dynamic_cast<Minion*>(obj);
	Tower* temp_tower = dynamic_cast<Tower*>(obj);
	if (obj == CollisionManager::GetInstance()->get_ground())
	{
		//priority. test to see if it is neccesary
		this->set_isCollidable(false);
		this->start_countdown(true);
		return;
	}
	if (temp_minion)
	{
		temp_minion->get_hit(this->get_dmg());
		this->active = false;
	}
	else if (temp_tower)
	{
		temp_tower->get_hit(this->get_dmg());
		Particle* p = ObjectPoolManager::GetInstance()->get_particle(ObjectPoolManager::PARTICLE_CASE::GROUND);
		p->pos = this->pos;
		p->scale = this->scale;
		p->dir = -this->dir;

		this->active = false;
	}
	//else if (temp_tower)

	//if proj - proj, ignore

}

void Projectile::start_countdown(bool sure_start)
{
	if (!sure_start)
		return;

	this->start_timer = true;
	this->active_remaining_elapsed_timer = 0.0;
}