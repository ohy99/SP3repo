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


		//Level 1 
		
		temp = MeshBuilder::GenerateQuad("PLAYERTOWER", Color(0, 0, 0), 10);
		temp->textureID = LoadTGA("Image//tower(player).tga");
		assignMesh(temp);

		/*temp = MeshBuilder::GenerateQuad("BACKGROUND1", Color(0, 0, 0), 10);
		temp->textureID = LoadTGA("Image//level1background.tga");
		assignMesh(temp);*/

		temp = MeshBuilder::GenerateQuad("Tile1", Color(0, 0, 0), 10);
		temp->textureID = LoadTGA("Image//level1tile.tga");
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

