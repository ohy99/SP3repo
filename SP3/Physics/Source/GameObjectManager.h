#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
class GameObject;

//Manages the life time of GameObjects
class GameObjectManager : public Singleton<GameObjectManager>
{
	friend Singleton;

	std::vector<GameObject*> game_object_list;

public:
	enum GameObjectType {
		//Define the types of game objects here.
	};
	GameObject* request_new(GameObjectType);

	void load_objects(const char* file_name);

protected:
	GameObjectManager();
	~GameObjectManager();
};

#endif // !GAMEOBJECTMANAGER_H
