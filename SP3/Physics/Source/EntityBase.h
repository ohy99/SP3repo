#ifndef _ENTITYBASE_
#define _ENTITYBASE_

#define AXIS 0

#include <vector>
#include <map>
#include <string>

#include "EntityNotFound.h"
#include "Vertex.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

class EntityBase
{
	std::map<std::string, Mesh*>Entities;

	EntityBase(){

		Mesh* temp;
		temp = MeshBuilder::GenerateAxes("Axis", 1000, 1000, 1000);
		assignEntity(temp);
		temp = MeshBuilder::GenerateSphere("Sphere", Color(1, 1, 1), 10, 10, 1);
		assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("Quad", Color(1, 1, 1), 1);
		assignEntity(temp);

		temp = MeshBuilder::GenerateCone("Cone", Color(1, 1, 1), 10, 1, 1);
		assignEntity(temp);
		temp = MeshBuilder::GenerateCube("Cube", Color(1, 1, 1), 1);
		assignEntity(temp);
		temp = MeshBuilder::GenerateRing("Ring", Color(1, 1, 1), 10, 1.0f, 0.5f);
		assignEntity(temp);

		temp = MeshBuilder::GenerateCone("SHIP", Color(1, 1, 0), 10, 1, 1);
		assignEntity(temp);
		temp = MeshBuilder::GenerateCone("ENEMY", Color(1, 0, 0), 10, 1, 1);
		assignEntity(temp);
		temp = MeshBuilder::GenerateSphere("BULLET", Color(1, 0, 0), 10, 10, 1.f);
		assignEntity(temp);
		//temp = MeshBuilder::GenerateQuad("ASTEROID", Color(1.f, 1.f, 1.1f), 1);
		//temp->textureID = LoadTGA("Image//asteroid.tga");
		//assignEntity(temp);
		temp = MeshBuilder::GenerateCone("MISSILE", Color(1.f, 0.f, 0.7f), 10, 1, 1);
		assignEntity(temp);
		//temp = MeshBuilder::GenerateQuad("PLANET", Color(1.f, 1.f, 1.f), 1);
		//temp->textureID = LoadTGA("Image//planet.tga");
		//assignEntity(temp);

		temp = MeshBuilder::GenerateQuad("REDHPBAR", Color(1, 1, 1), 1.f);
		temp->textureID = LoadTGA("Image//redhpbar.tga");
		assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("GREENHPBAR", Color(1, 1, 1), 1.f);
		temp->textureID = LoadTGA("Image//greenhpbar.tga");
		assignEntity(temp);
		//temp = MeshBuilder::GenerateQuad("BOOSTBORDER", Color(1, 1, 1), 1.f);
		//temp->textureID = LoadTGA("Image//boostborder.tga");
		//assignEntity(temp);
		//temp = MeshBuilder::GenerateQuad("BOOSTFUEL", Color(1, 1, 1), 1.f);
		//temp->textureID = LoadTGA("Image//boostfuel.tga");
		//assignEntity(temp);

		//temp = MeshBuilder::GenerateQuad("HPUP", Color(1, 1, 1), 1.f);
		//temp->textureID = LoadTGA("Image//hpup.tga");
		//assignEntity(temp);
		//temp = MeshBuilder::GenerateQuad("BOOSTUP", Color(1, 1, 1), 1.f);
		//temp->textureID = LoadTGA("Image//boostup.tga");
		//assignEntity(temp);
		//temp = MeshBuilder::GenerateQuad("INCDMG", Color(1, 1, 1), 1.f);
		//temp->textureID = LoadTGA("Image//incdmg.tga");
		//assignEntity(temp);
		//temp = MeshBuilder::GenerateQuad("DMGIMM", Color(1, 1, 1), 1.f);
		//temp->textureID = LoadTGA("Image//shield.tga");
		//assignEntity(temp);

		temp = MeshBuilder::GenerateQuad("BUTTON", Color(1, 1, 1), 1.f);
		//temp->textureID = LoadTGA("Image//shield.tga");
		assignEntity(temp);

		//temp = MeshBuilder::GenerateMovingTextureQuad("BACKGROUND", Color(1, 1, 1), 1, 1);
		//temp->textureID = LoadTGA("Image//background.tga");
		//assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("BACKGROUND", Color(0, 0, 0), 1);
		assignEntity(temp);

		temp = MeshBuilder::GenerateText("CALIBRI", 16, 16);
		temp->textureID = LoadTGA("Image//calibri.tga");
		assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("STARTBUTTON", Color(1,1,1), 1);
		temp->textureID = LoadTGA("Image//startbutton.tga");
		assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("INSTRUCTIONBUTTON", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//Instructionsbutton.tga");
		assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("EXITBUTTON", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//exitbutton.tga");
		assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("BACKBUTTON", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//backbutton.tga");
		assignEntity(temp);
		//temp = MeshBuilder::GenerateQuad("INSTRUCTIONS", Color(1, 1, 1), 1);
		//temp->textureID = LoadTGA("Image//instructions.tga");
		//assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("INSTRUCTIONS", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//A2Instructions.tga");
		assignEntity(temp);

		temp = MeshBuilder::GenerateQuad("BRICK", Color(1, 1, 1), 1);
		//temp->textureID = LoadTGA("Image//instructions.tga");
		assignEntity(temp);
		temp = MeshBuilder::GenerateSphere("BALL", Color(1, 1, 1), 10, 10, 1.f);
		//temp->textureID = LoadTGA("Image//instructions.tga");
		assignEntity(temp);
		
		temp = MeshBuilder::GenerateQuad("RED", Color(1, 0, 0), 1);
		//temp->textureID = LoadTGA("Image//instructions.tga");
		assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("GREEN", Color(0, 1, 0), 1);
		//temp->textureID = LoadTGA("Image//instructions.tga");
		assignEntity(temp);
		temp = MeshBuilder::GenerateQuad("BLUE", Color(0, 0, 1), 1);
		//temp->textureID = LoadTGA("Image//instructions.tga");
		assignEntity(temp);

		temp = MeshBuilder::GenerateSphere("ENEMYBALL", Color(1, 0, 0), 10, 10, 1.f);
		//temp->textureID = LoadTGA("Image//instructions.tga");
		assignEntity(temp);
		temp = MeshBuilder::GenerateSphere("PLAYERBALL", Color(0, 1, 0), 10, 10, 1.f);
		//temp->textureID = LoadTGA("Image//instructions.tga");
		assignEntity(temp);

		temp = MeshBuilder::GenerateLine("REDLINE", Color(1,0,0), 1);
		assignEntity(temp);
		temp = MeshBuilder::GenerateLine("GREENLINE", Color(0, 1, 0), 1);
		assignEntity(temp);
		temp = MeshBuilder::GenerateLine("BLUELINE", Color(0, 0, 1), 1);
		assignEntity(temp);
	}

	void assignEntity(Mesh* a) {
		Entities[a->name] = a;
	}
	static EntityBase* instance;
public:
	static EntityBase* getInstance() {
		if (!instance)
			instance = new EntityBase;
		return instance;
	}

	Mesh* getEntity(std::string a)
	{
		Mesh* ret = Entities[a];
		if (ret == NULL)
			throw EntityNotFound(a);
		return ret;
	}


	~EntityBase() {
		for (auto it : Entities)
		{
			if (it.second != NULL)
			{
				delete it.second;
				it.second = nullptr;
			}
		}
	}
};



#endif

