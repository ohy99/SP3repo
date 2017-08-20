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
	void set_season(SEASON_TYPE a) { season = a; };
	SEASON_TYPE get_season() { return season; };
private:
	friend Singleton;

	Mesh* season_mesh[SEASON_TYPE::COUNT];
	
protected:
	SeasonManager() {};
	~SeasonManager() {};
};

#endif // !SEASONMANAGER_H
