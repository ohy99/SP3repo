#include "ObjectPoolManager.h"

#include "MeshList.h"
#include "Projectile.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"

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