#include "ObjectPoolManager.h"

#include "MeshList.h"
#include "Projectile.h"
#include "ParticleManager.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "ParticleManager.h"
#include "ProjectileRainArrow.h"

ObjectPoolManager::ObjectPoolManager()
{
	for (unsigned int i = 0; i < (unsigned)200; ++i)
	{
		Projectile* temp_proj = new Projectile();
		temp_proj->set_collision_type(Collision::CollisionType::SPHERE);
		temp_proj->scale.Set(3, 3);
		temp_proj->update_collider();

		projectile_pool.push_back(temp_proj);
		PhysicsManager::GetInstance()->add_object(temp_proj);
		RenderManager::GetInstance()->attach_renderable(temp_proj, 2);
	}
	for (unsigned int i = 0; i < (unsigned)10; ++i)
	{
		Projectile* temp_proj = new ProjectileRainArrow();
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
	//particle_mesh[PARTICLE_CASE::GROUND] = MeshList::GetInstance()->getMesh("Poster");
	//particle_mesh[PARTICLE_CASE::ETOWER] = MeshList::GetInstance()->getMesh("Poster");

	particle_mesh[PARTICLE_CASE::SPRING] = MeshList::GetInstance()->getMesh("SPRING");
	particle_mesh[PARTICLE_CASE::SUMMER] = MeshList::GetInstance()->getMesh("SUMMER");
	particle_mesh[PARTICLE_CASE::AUTUMN] = MeshList::GetInstance()->getMesh("AUTUMN");
	particle_mesh[PARTICLE_CASE::WINTER] = MeshList::GetInstance()->getMesh("WINTER");
}

ObjectPoolManager::~ObjectPoolManager()
{
	for each (auto &proj in projectile_pool)
		delete proj;
}

Projectile* ObjectPoolManager::get_projectile(PROJECTILE_TYPE id, int type)
{
	Projectile* temp_proj = get_inactive_projectile(type);
	temp_proj->active = true;
	temp_proj->mesh = projectile_mesh[id];
	return temp_proj;
}

Projectile* ObjectPoolManager::get_inactive_projectile(int type)
{
	switch (type)
	{
	case 1:
		for each (auto &p in projectile_pool)
		{
			if (p->active)
				continue;
			if (dynamic_cast<ProjectileRainArrow*>(p))
				return p;
		}
		break;
	default:
		for each (auto &p in projectile_pool)
		{
			if (p->active)
				continue;
			if (dynamic_cast<ProjectileRainArrow*>(p) == nullptr)
				return p;
		}
		break;
	}

	return nullptr;
}


Particle * ObjectPoolManager::get_particle(PARTICLE_CASE id)
{
	Particle* p = get_inaactive_particle();
	p->mesh = particle_mesh[id];
	p->active = true;
	p->init();
	return p;
	return nullptr;
}

void ObjectPoolManager::Update(double dt)
{
	for each (auto &p in projectile_pool)
	{
		if (p->active)
			p->update(dt);
	}
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