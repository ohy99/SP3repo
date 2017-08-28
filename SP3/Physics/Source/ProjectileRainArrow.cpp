#include "ProjectileRainArrow.h"

#include "ObjectPoolManager.h"
#include "Mtx44.h"

ProjectileRainArrow::ProjectileRainArrow() : num_of_splits(0), elapsed_time(0.0),
	spliting_time(0.0), percentage_force_transfered(1.f), degree_apart(0.f), percent_split_dmg(0.f)
{
}

ProjectileRainArrow::~ProjectileRainArrow()
{
}

void ProjectileRainArrow::update(double dt)
{
	elapsed_time += dt;

	if (elapsed_time >= spliting_time)
	{
		//SPLIT
		this->active = false;
		float total_degree_between = (num_of_splits - 1) * degree_apart;
		int spliteddmg = (this->get_dmg() * percent_split_dmg) / num_of_splits;

		for (int i = 0; i < num_of_splits; ++i)
		{
			Projectile* proj = ObjectPoolManager::GetInstance()->get_projectile(ObjectPoolManager::PROJECTILE_TYPE::ARROWS3);
			proj->active = true;
			Mtx44 rotate;
			rotate.SetToRotation(-total_degree_between * 0.5f + (float)i * degree_apart, 0, 0, 1);
			proj->pos = this->pos;
			proj->dir = rotate * this->dir;
			proj->dir.Normalize();
			proj->velocity = proj->dir * percentage_force_transfered * this->velocity.Length();
			proj->set_collision_type(Collision::CollisionType::SPHERE);
			proj->set_dmg(spliteddmg);
			proj->set_mass(percentage_force_transfered * this->get_mass());

			//proj->scale.Set(3, 3);
			//proj->update_collider();
			proj->set_faction_side(this->get_faction_side());
		}

		elapsed_time = 0.0;
	}
}

void ProjectileRainArrow::set_spliting_time(double time)
{
	this->spliting_time = time;
	elapsed_time = 0.0;
}

void ProjectileRainArrow::set_num_of_splits(unsigned num)
{
	this->num_of_splits = num;
}

unsigned ProjectileRainArrow::get_num_of_splits()
{
	return num_of_splits;
}

void ProjectileRainArrow::set_percentage_force_transfered(float percentage)
{
	this->percentage_force_transfered = percentage;
}

void ProjectileRainArrow::set_degree_apart(float degree)
{
	this->degree_apart = degree;
}

void ProjectileRainArrow::set_total_percentage_split_damage(float splitdmg)
{
	this->percent_split_dmg = splitdmg;
}
