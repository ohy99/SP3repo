#ifndef SEASONMANAGER_H
#define SEASONMANAGER_H

#include "SingletonTemplate.h"
#include <vector>

class Mesh;
class SeasonManager : public Singleton<SeasonManager>
{
public:
	enum SEASON_TYPE
	{
		WINTER,
		SUMMER,
		SPRING,
		AUTUMN,	
		COUNT
	}season;
	
	//Projectile* get_projectile(SEASON_TYPE id);

private:
	friend Singleton;

	Mesh* season_mesh[SEASON_TYPE::COUNT];
	
protected:
	SeasonManager();
	~SeasonManager();
};

#endif // !SEASONMANAGER_H
