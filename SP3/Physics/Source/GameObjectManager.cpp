#include "GameObjectManager.h"

#include "GameObject.h"
#include <fstream>

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for each (auto &g in game_object_list)
	{
		delete g;
	}
	game_object_list.clear();
}

GameObject * GameObjectManager::request_new(GameObjectType)
{
	GameObject* temp;
	game_object_list.push_back(temp);
	return nullptr;
}

void GameObjectManager::load_objects(const char* file_path)
{
	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return;
	}

	while (!fileStream.eof()) {
		char buf[256];
		fileStream.getline(buf, 256);
	

	}

	fileStream.close();

}