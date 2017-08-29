//gamescene.cpp
#include "GameScene.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshList.h"
#include "RenderHelper.h"
#include "Graphics.h"

#include "GlobalVariableManager.h"
#include "MeshBuilder.h"
#include "SceneManager.h"

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "TextManager.h"
#include "GameObjectManager.h"
#include "GameLogic.h"
#include "EnvironmentManager.h"
#include "RenderManager.h"
#include "MinionManager.h"
#include "ShowHpManager.h"
#include "EnemyAiLogic.h"
#include "TowerManager.h"
#include "GenericDecoration.h"

#include "CharacterInfo.h"
#include "SpriteAnimation.h"

#include "SeasonManager.h"

#include "WeaponInfo.h"
#include "SpellManager.h"
#include "ObjectPoolManager.h"
#include "HUDManager.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	PhysicsManager::Destroy();
	CollisionManager::Destroy();
	GameObjectManager::Destroy();
	GameLogic::Destroy();
	MeshList::Destroy();
	EnvironmentManager::Destroy();
	RenderManager::Destroy();
	MinionManager::Destroy();
	SeasonManager::Destroy();
	ObjectPoolManager::Destroy();
	HUDManager::Destroy();
	EnemyAiLogic::Destroy();
	ShowHpManager::Destroy();
	SpellManager::Destroy();
	TowerManager::Destroy();
}

void GameScene::Init()
{


	glClearColor(0.0f, 0.0f, 0.f, 0.0f);
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	Graphics::GetInstance()->init();

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));



	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);

	Math::InitRNG();

	axis = MeshBuilder::GenerateAxes("", 100, 100, 100);
	//background = EntityBase::getInstance()->getEntity("BACKGROUND");
	pausescreen = MeshList::GetInstance()->getMesh("PAUSE");
	GameObjectManager::GetInstance()->load_objects("Image\\lvl0objects.txt");
	winlvl = MeshList::GetInstance()->getMesh("TRANS");

	isPause = false;
	isShop = false;
	istrans = false;
	

	CharacterInfo.Init();
	//CharacterInfo.Load();
	shop.init();
	

	SeasonManager::GetInstance()->set_season((SeasonManager::SEASON_TYPE)Math::RandIntMinMax(0,3));
	switch (SeasonManager::GetInstance()->get_season())
	{
	case SeasonManager::WINTER:
		MinionManager::GetInstance()->adjust_minions_move_speed(80);
		MinionManager::GetInstance()->adjust_minions_dmg(90);
		MinionManager::GetInstance()->adjust_minions_hp(110);
		MinionManager::GetInstance()->adjust_minions_att_spd(80);
		break;
	case SeasonManager::SUMMER:
		MinionManager::GetInstance()->adjust_minions_move_speed(110);
		MinionManager::GetInstance()->adjust_minions_dmg(120);
		MinionManager::GetInstance()->adjust_minions_att_spd(110);
		MinionManager::GetInstance()->adjust_minions_hp(90);
		break;
	case SeasonManager::SPRING:
		MinionManager::GetInstance()->reset_minions_att_spd();
		MinionManager::GetInstance()->reset_minions_dmg();
		MinionManager::GetInstance()->reset_minions_hp();
		MinionManager::GetInstance()->reset_minions_move_speed();
		break;
	case SeasonManager::AUTUMN:
		MinionManager::GetInstance()->adjust_minions_hp(80);
		MinionManager::GetInstance()->adjust_minions_dmg(80);
		MinionManager::GetInstance()->adjust_minions_move_speed(120);
		MinionManager::GetInstance()->adjust_minions_att_spd(80);
		break;
	}


	/*weap.Init();
	weap.set_faction_side(Faction::FACTION_SIDE::PLAYER);
	weap.mesh = MeshList::GetInstance()->getMesh("CANNON");
	weap.scale.Set(5, 5, 5);
	weap.active = true;
	weap.pos.Set(7.5, 25);
	weap.set_damage(50);
	RenderManager::GetInstance()->attach_renderable(&weap, 1);
	*/

	//cout << SeasonManager::GetInstance()->get_season() << endl;
	shop.attachWalletInfo(&this->CharacterInfo.getWallet());
	MinionManager::GetInstance()->attach_character(&this->CharacterInfo);
	EnemyAiLogic::GetInstance()->attachCharacter(&this->CharacterInfo);
	SpellManager::GetInstance()->character = &this->CharacterInfo;
	HUDManager::GetInstance()->character = &this->CharacterInfo;

	FontType & wad = ShowHpManager::GetInstance()->get_font();
	std::cout << &wad << std::endl;
}


void GameScene::Update(double dt)
{
	//Test out for variable in characterinfo save	cout << CharacterInfo.getcurrentcoins() << endl;


	static bool PButtonState = false;
	if (Application::IsKeyPressed('P') && !PButtonState && !isShop && !istrans)
	{
		if (!isPause)
			isPause = true;
		else
			isPause = false;

		PButtonState = true;
	}
	else if (!Application::IsKeyPressed('P') && PButtonState)
	{
		PButtonState = false;
	}

	static bool SButtonState = false;
	if (Application::IsKeyPressed('S') && !SButtonState && !isPause && !istrans)
	{
		if (!isShop)
			isShop = true;
		else
			isShop = false;
		CharacterInfo.Save();
		SButtonState = true;
	}
	else if (!Application::IsKeyPressed('S') && SButtonState)
	{
		SButtonState = false;
	}


	//	weap.WeaponInfo::Update(dt);

	if (!isPause && !isShop&&!istrans)
	{
		CharacterInfo.Update(dt);

		GameLogic::GetInstance()->update(dt);
		GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);

		SpellManager::GetInstance()->update(dt);
		//Update enemies
		EnemyAiLogic::GetInstance()->update(dt);
		MinionManager::GetInstance()->update(dt);
		//Update Physics
		PhysicsManager::GetInstance()->update(dt);
		//Update collisions
		CollisionManager::GetInstance()->update(dt);
		//update the show hp thing
		ShowHpManager::GetInstance()->update(dt);
		ObjectPoolManager::GetInstance()->Update(dt);
		SeasonManager::GetInstance()->update(dt);
		HUDManager::GetInstance()->update(dt);
		fps = 1.0 / dt;
	}
	if (isShop)
	{
		shop.Update(dt);
	}

	//TextManager::GetInstance()->add_text(0, "fps: " + std::to_string(fps));

	//if (TowerManager::GetInstance()->player->get_health() <= 0)
	//	SceneManager::GetInstance()->setNextScene("LOSE");

	if (TowerManager::GetInstance()->enemy->get_health() <= 0)
	{
		if (EnemyAiLogic::GetInstance()->get_level() < 4 )
		{
			istrans = true;
			int level = EnemyAiLogic::GetInstance()->get_level();
			SceneManager::GetInstance()->setNextScene("TRANS");

			EnemyAiLogic::GetInstance()->set_level(level += 1);
			audioPlayer.pause();
		}
		else
		{
			
			SceneManager::GetInstance()->setNextScene("WIN");
		}
	}
	else if (TowerManager::GetInstance()->player->get_health() <= 0)
	{
		SceneManager::GetInstance()->setNextScene("LOSE");
		audioPlayer.pause();
	}
}



void GameScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;

	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	projection.SetToOrtho(0, worldWidth, 0, worldHeight, -10, 10);
	Graphics::GetInstance()->projectionStack.LoadMatrix(projection);

	// Camera matrix
	Graphics::GetInstance()->viewStack.LoadIdentity();
	Graphics::GetInstance()->viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	// Model matrix : an identity matrix (model will be at the origin)
	Graphics::GetInstance()->modelStack.LoadIdentity();

	MS& ms = Graphics::GetInstance()->modelStack;
	RenderHelper::RenderMesh(axis, false);

	ms.PushMatrix();
	//ms.Scale(600.f / Application::GetWindowHeight(), 600.f/ Application::GetWindowHeight(), 1);
	ms.Translate(0, 5.f * ((800.f / 600.f) - ((float)Application::GetWindowWidth() / (float)Application::GetWindowHeight())), 0);
	RenderManager::GetInstance()->render_all_active_objects();
	SeasonManager::GetInstance()->render_season();
	HUDManager::GetInstance()->render();
	ShowHpManager::GetInstance()->render_all_hp_text();
	RenderManager::GetInstance()->post_render();
	ms.PopMatrix();


	//SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Poster"));
	//ms.PushMatrix();
	//ms.Translate(50, 50, 0);
	//ms.Scale(10, 10, 10);
	//RenderHelper::RenderMesh(sa, false);
	////sa->Render();
	//ms.PopMatrix();

	if (isPause)
	{
		ms.PushMatrix();
		ms.Translate(worldWidth / 2, worldHeight / 2, 0);
		ms.Scale(Vector3(100, 80, 1));
		RenderHelper::RenderMesh(pausescreen, false);
		ms.PopMatrix();
	}
	if (isShop)
		shop.Render();
}

void GameScene::Exit()
{

	//if (axis)
	//{
	//	delete axis;
	//	axis = nullptr;
	//}

	//Do this later when the variables are loaded.
	//CharacterInfo.Save();

	PhysicsManager::Destroy();
	CollisionManager::Destroy();
	GameObjectManager::Destroy();
	GameLogic::Destroy();
	//MeshList::Destroy();
	EnvironmentManager::Destroy();
	RenderManager::Destroy();
	MinionManager::Destroy();
	SeasonManager::Destroy();
	ObjectPoolManager::Destroy();
	HUDManager::Destroy();
	EnemyAiLogic::Destroy();
	ShowHpManager::Destroy();
	SpellManager::Destroy();
	TowerManager::Destroy();
}

