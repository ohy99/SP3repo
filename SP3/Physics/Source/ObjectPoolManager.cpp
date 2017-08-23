#include "ObjectPoolManager.h"

#include "MeshList.h"
#include "Projectile.h"
#include "ParticleManager.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "ParticleManager.h"

ObjectPoolManager::ObjectPoolManager()
{
	for (unsigned int i = 0; i < (unsigned)100; ++i)
	{
		Projectile* temp_proj = new Projectile();
		temp_proj->set_collision_type(Collision::CollisionType::SPHERE);
		temp_proj->scale.Set(3, 3);
		temp_proj->update_collider();

		projectile_pool.push_back(temp_proj);
		PhysicsManager::GetInstance()->add_object(temp_proj);
		RenderManager::GetInstance()->attach_renderable(temp_proj, 2);
	}
	projectile_mesh[PROJECTILE_TYPE::BULLET] = MeshList::GetInstance()->getMesh("BULLET");
	projectile_mesh[PROJECTILE_TYPE::CANNONBALL] = MeshList::GetInstance()->getMesh("CANNONBALL");

	for (unsigned int i = 0; i < (unsigned)100; ++i)
	{
		Particle* temp_proj = new Particle();
		temp_proj->init();
		temp_proj->scale.Set(3, 3);
		temp_proj->set_duration(2.0);
		particle_pool.push_back(temp_proj);
		//PhysicsManager::GetInstance()->add_object(temp_proj);
		RenderManager::GetInstance()->attach_renderable(temp_proj, 2);
	}
	particle_mesh[PARTICLE_CASE::GROUND] = MeshList::GetInstance()->getMesh("Poster");
	particle_mesh[PARTICLE_CASE::ETOWER] = MeshList::GetInstance()->getMesh("Poster");
}

ObjectPoolManager::~ObjectPoolManager()
{
	for each (auto &proj in projectile_pool)
		delete proj;
}

Projectile* ObjectPoolManager::get_projectile(PROJECTILE_TYPE id)
{
	Projectile* temp_proj = get_inactive_projectile();
	temp_proj->active = true;
	temp_proj->mesh = projectile_mesh[id];
	return temp_proj;
}

Projectile* ObjectPoolManager::get_inactive_projectile()
{
	for each (auto &p in projectile_pool)
	{
		if (p->active)
			continue;
		return p;
	}
	return nullptr;
}


Particle * ObjectPoolManager::get_particle(PARTICLE_CASE id)
{
	switch(id)
	{
	case PARTICLE_CASE::GROUND:
		{ 
			Particle* p = get_inaactive_particle();
			p->mesh = particle_mesh[id];
			p->active = true;
			p->init();
			return p;
		}
			break;
	}
	return nullptr;
}

void ObjectPoolManager::Update(double dt)
{
	for each (auto &p in particle_pool)
	{
		if (p->active)
			p->update(dt);
	}
}

Particle* ObjectPoolManager::get_inaactive_particle()
{
	for each (auto &p in particle_pool)
	{
		if (p->active)
			continue;
		return p;
	}
	return nullptr;
}