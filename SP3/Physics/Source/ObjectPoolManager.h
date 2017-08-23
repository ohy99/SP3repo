#ifndef OBJECTPOOLMANAGER_H
#define OBJECTPOOLMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
class Projectile;
class Particle;
class Mesh;
class ObjectPoolManager : public Singleton<ObjectPoolManager>
{
public:
	enum PROJECTILE_TYPE
	{
		BULLET,
		CANNONBALL,
		ARROWS,
		COUNT
	};
	enum PARTICLE_CASE
	{
		GROUND,
		ETOWER,
		TOWER,
		COUNT2
	};
	//RETURNS ACTIVATED PROJECTILE
	Projectile* get_projectile(PROJECTILE_TYPE id, int type = 0);
	Particle* get_particle(PARTICLE_CASE id);
	void Update(double dt);
private:
	friend Singleton;

	std::vector<Projectile*> projectile_pool;
	std::vector<Particle*>particle_pool;
	Mesh* projectile_mesh[PROJECTILE_TYPE::COUNT];
	Mesh* particle_mesh[PARTICLE_CASE::COUNT2];
	Projectile* get_inactive_projectile(int type = 0);//0 normal, 1 rain
	Particle* get_inaactive_particle();
protected:
	ObjectPoolManager();
	~ObjectPoolManager();
};

#endif // !OBJECTPOOLMANAGER_H
