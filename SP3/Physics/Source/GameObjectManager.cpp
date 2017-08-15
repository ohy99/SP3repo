#include "GameObjectManager.h"

#include "GameObject.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObject * GameObjectManager::request_new(GameObjectType)
{
	return nullptr;
}
