
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	momentOfInertia(0.0f),
	angularVelocity(0.0f), //in radians
	normal(0, 1, 0)
{
}

GameObject::~GameObject()
{
}