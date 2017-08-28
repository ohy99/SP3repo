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

		temp = MeshBuilder::GenerateText("CHILLER", 16, 16);
		temp->textureID = LoadTGA("Image//chiller.tga");
		assignMesh(temp);
		
		//Level 1; 
		
		temp = MeshBuilder::GenerateQuad("PLAYERTOWER", Color(0, 0, 0), 1);
		temp->textureID = LoadTGA("Image//tower(player).tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("PLAYERTOWER75", Color(0, 0, 0), 1);
		temp->textureID = LoadTGA("Image//tower75.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("PLAYERTOWER50", Color(0, 0, 0), 1);
		temp->textureID = LoadTGA("Image//tower50.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("PLAYERTOWER25", Color(0, 0, 0), 1);
		temp->textureID = LoadTGA("Image//tower25.tga");
		assignMesh(temp);

		/*temp = MeshBuild cbcer::GenerateQuad("BACKGROUND1", Color(0, 0, 0), 10);
		temp->textureID = LoadTGA("Image//level1background.tga");
		assignMesh(temp);*/

		temp = MeshBuilder::GenerateQuad("Tile1", Color(0, 0, 0), 1);
		temp->textureID = LoadTGA("Image//level1tile.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("GREENDRAGON", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//greendragon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("GREENATTACK", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//greenattack.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("BLUEDRAGON", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//bluedragon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("BLUEATTACK", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//blueattack.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("BROWNDRAGON", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//browndragon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("BROWNATTACK", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//brownattack.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("BLACKDRAGON", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//blackdragon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("BLACKATTACK", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//blackattack.tga");
		assignMesh(temp);


		temp = MeshBuilder::GenerateOppositeSpriteAnimation("#OGREENDRAGON", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//greendragon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateOppositeSpriteAnimation("#OGREENATTACK", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//greenattack.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateOppositeSpriteAnimation("#OBLUEDRAGON", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//bluedragon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateOppositeSpriteAnimation("#OBLUEATTACK", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//blueattack.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateOppositeSpriteAnimation("#OBROWNDRAGON", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//browndragon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateOppositeSpriteAnimation("#OBROWNATTACK", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//brownattack.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateOppositeSpriteAnimation("#OBLACKDRAGON", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//blackdragon.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateOppositeSpriteAnimation("#OBLACKATTACK", 1, 6, 1.f);
		temp->textureID = LoadTGA("Image//blackattack.tga");
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
		temp = MeshBuilder::GenerateQuad("LEVEL1", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\level1.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("LEVEL2", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\level2.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("LEVEL3", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\level3.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("LEVEL4", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\level4.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("TITLE", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\title.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("Poster", 1, 6, 1.0f);
		temp->textureID = LoadTGA("Image//animatedposter.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateSpriteAnimation("Fire", 1, 6, 1.0f);
		temp->textureID = LoadTGA("Image//animatedfire.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("PAUSE", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//pause.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("VOLUME", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//volume.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("INSTRUCTIONS", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//instructions.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("SUMMER", 1,9, 1.f);
		temp->textureID = LoadTGA("Image//summer.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("SPRING", 1, 9, 1.f);
		temp->textureID = LoadTGA("Image//spring.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("WINTER", 1, 9, 1.f);
		temp->textureID = LoadTGA("Image//winter.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateSpriteAnimation("AUTUMN", 1, 9, 1.f);
		temp->textureID = LoadTGA("Image//autumn.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("BACK", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//back.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("MENUBACKGROUND", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image//background.tga");
		assignMesh(temp);


		//Shop Button
		temp = MeshBuilder::GenerateQuad("Buy", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\buy.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("Sell", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\sell.tga");
		assignMesh(temp);
		//Shop 
		temp = MeshBuilder::GenerateQuad("Shop", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\Shop.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("currentcoins", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\currentcoins.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("header", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\header.tga");
		assignMesh(temp);
		//Spells
		temp = MeshBuilder::GenerateQuad("lightning", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\lightning.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("freeze", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\blizzard.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("blast", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\blast.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("fire", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\fire.tga");
		assignMesh(temp);


		temp = MeshBuilder::GenerateQuad("drainparticle", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\drainparticle.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("drain", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\drainwater.tga");
		assignMesh(temp);

		temp = MeshBuilder::GenerateQuad("SPELLHUD", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\spellhud.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("ULTIREADY", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\ultiready.tga");
		assignMesh(temp);

		//weap
		temp = MeshBuilder::GenerateQuad("NOOBBOW", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\weapon1.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("OKAYBOW", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\weapon2.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("GOODBOW", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\weapon3.tga");
		assignMesh(temp);
		temp = MeshBuilder::GenerateQuad("TRANS", Color(1, 1, 1), 1);
		temp->textureID = LoadTGA("Image\\winlvl.tga");
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

