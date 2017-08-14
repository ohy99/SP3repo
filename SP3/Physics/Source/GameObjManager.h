#ifndef GAMEOBJMANAGER_H
#define GAMEOBJMANAGER_H

class GameObj;
#include "SingletonTemplate.h"
#include <vector>

class GameObjManager : public Singleton<GameObjManager>
{
	friend Singleton;
	std::vector<GameObj*> all_game_objs;
public:
	enum OBJ_TYPE
	{
		BALL,
		WALL,
		BRICK,
		PILLAR,
		BRICK_WITH_TURRET,
		HPAREA
	};
	void update_all_game_objs(double dt);
	void render_all_game_objs();
	void add_game_obj(GameObj* g);

	GameObj* request_new(OBJ_TYPE type);
protected:
	GameObjManager();
	virtual ~GameObjManager();
};


#endif // !GAMEOBJMANAGER_H
