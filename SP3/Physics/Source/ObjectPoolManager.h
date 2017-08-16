#ifndef OBJECTPOOLMANAGER_H
#define OBJECTPOOLMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
class Projectile;
class Mesh;
class ObjectPoolManager : public Singleton<ObjectPoolManager>
{
public:
	enum PROJECTILE_TYPE
	{
		BULLET,
		CANNONBALL,
		COUNT
	};
	//RETURNS ACTIVATED PROJECTILE
	Projectile* get_projectile(PROJECTILE_TYPE id);

private:
	friend Singleton;

	std::vector<Projectile*> projectile_pool;
	Mesh* projectile_mesh[PROJECTILE_TYPE::COUNT];
	Projectile* get_inactive_projectile();
protected:
	ObjectPoolManager();
	~ObjectPoolManager();
};

#endif // !OBJECTPOOLMANAGER_H
