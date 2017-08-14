#ifndef _GLOBALMANAGER_H
#define _GLOBALMANAGER_H

class Player;
class Enemy;
#include <vector>
#include "Collision.h"

class GlobalVariables
{
	static GlobalVariables* instance;
	GlobalVariables() {

		//player = nullptr;
	}
public:
	static GlobalVariables* get(){
		if (instance == nullptr)
			instance = new GlobalVariables();
		return instance;
	}
	~GlobalVariables() {

	}

	//ALL GLOBAL VARIABLES HERE
	float* worldWidth;
	float* worldHeight;

	//Player* player;


};



#endif