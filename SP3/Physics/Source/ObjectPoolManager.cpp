#include "ObjectPoolManager.h"

#include "MeshList.h"
#include "Projectile.h"

ObjectPoolManager::ObjectPoolManager()
{
	for (unsigned int i = 0; i < (unsigned)100;++i)
		projectile_pool.push_back(new Projectile());
	projectile_mesh[PROJECTILE_TYPE::BULLET] = MeshList::GetInstance()->getMesh("PLAYERTOWER");
	projectile_mesh[PROJECTILE_TYPE::CANNONBALL] = MeshList::GetInstance()->getMesh("PLAYERTOWER");
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