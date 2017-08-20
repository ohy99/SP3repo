#ifndef _MeshList_
#define _MeshList_

#define AXIS 0

#include <vector>
#include <map>
#include <string>

#include "MeshNotFound.h"
#include "Vertex.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "SingletonTemplate.h"

class MeshList : public Singleton <MeshList>
{
	friend Singleton;
	std::map<std::string, Mesh*>Entities;

	MeshList(){

		Mesh* temp;

		//Base Meshes
		temp = MeshBuilder::GenerateAxes("Axis", 1000, 1000, 1000);
		assignMesh(temp);
		temp = MeshBuilder::GenerateSphere("Sphere", Color(1, 1, 1), 10, 10, 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("Quad", Color(1, 1, 1), 1);
		assignMesh(temp);

		temp = MeshBuilder::GenerateCone("Cone", Color(1, 1, 1), 10, 1, 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateCube("Cube", Color(1, 1, 1), 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateRing("Ring", Color(1, 1, 1), 10, 1.0f, 0.5f);
		assignMesh(temp);
	
		temp = MeshBuilder::GenerateQuad("BACKGROUND", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//level1background.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateText("CALIBRI", 16, 16);
		temp->textureID = LoadTGA("Image//calibri.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateLine("REDLINE", Color(1,0,0), 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateLine("GREENLINE", Color(0, 1, 0), 1);
		assignMesh(temp);
		temp = MeshBuilder::GenerateLine("BLUELINE", Color(0, 0, 1), 1);
		assignMesh(temp);

		//COMMON MESHS
		temp = MeshBuilder::GenerateQuad("CANNON", Color(0, 0, 0), 1);
		temp->textureID = LoadTGA("Image//cannon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("CANNONBALL", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//projectiles.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("BULLET", Color(1, 1, 1), 1);
		//temp->textureID = LoadTGA("Image//cannon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("REDHPBAR", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//redhpbar.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("GREENHPBAR", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//greenhpbar.tga");
		assignMesh(temp);

	
		
		//Level 1; 
		
		temp = MeshBuilder::GenerateQuad("PLAYERTOWER", Color(0, 0, 0), 1);
		temp->textureID = LoadTGA("Image//tower(player).tga");
		assignMesh(temp);

		/*temp = MeshBuild cbcer::GenerateQuad("BACKGROUND1", Color(0, 0, 0), 10);
		temp->textureID = LoadTGA("Image//level1background.tga");
		assignMesh(temp);*/

		temp = MeshBuilder::GenerateQuad("Tile1", Color(0, 0, 0), 1);
		temp->textureID = LoadTGA("Image//level1tile.tga");
		assignMesh(temp);



		//Level 2

		temp = MeshBuilder::GenerateQuad("BACKGROUND2", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//level2background.tga");
		assignMesh(temp);
		//Tiles same as level 1



		//Level 3

		temp = MeshBuilder::GenerateQuad("BACKGROUND3", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//level3background.tga");
		assignMesh(temp);


		//Level 4


		temp = MeshBuilder::GenerateQuad("BACKGROUND4", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//level4background.tga");
		assignMesh(temp);

		//BUTTONS
		temp = MeshBuilder::GenerateQuad("PLAYBUTTON", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\playbutton.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("OPTIONSBUTTON", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\optionsbutton.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("QUITBUTTON", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\quitbutton.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("LOSE", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\lose.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("WIN", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\win.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("PLUSBUTTON", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\plus.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("MINUSBUTTON", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\minus.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("LEVELSELECTBUTTON", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\levelselect.tga");
		assignMesh(temp);
		//temp = MeshBuilder::GenerateQuad("TITLE", Color(1, 1, 1), 1);
		//temp->textureID = LoadTGA("Image\\title.tga");
		//assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("Poster", 1, 6, 1.0f);
		temp->textureID = LoadTGA("Image//animatedposter.tga");
		assignMesh(temp);


		
	}

	void assignMesh(Mesh* a) {
		Entities[a->name] = a;
	}

public:

	Mesh* getMesh(std::string a)
	{
		Mesh* ret = Entities[a];
		if (ret == NULL)
			throw MeshNotFound(a);
		return ret;
	}


	~MeshList() {
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

