#include "AScene.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "EntityBase.h"
#include "RenderHelper.h"
#include "Graphics.h"

#include "GlobalVariableManager.h"

#include "MeshBuilder.h"


#include "SceneManager.h"

#include "CollisionManager.h"

//EntityBase* EntityBase::instance = NULL;
//Graphics* Graphics::instance = NULL;
//GlobalVariables* GlobalVariables::instance = nullptr;

//
//Player* Player::instance = NULL;
//HpBar* HpBar::instance = nullptr;//this acts as stamp;

#include "Bricks.h"
#include "Ball.h"
#include "PlayerControls.h"
#include "GameObjManager.h"
#include "PhysicsManager.h"
#include "GameLogic.h"
#include "TextManager.h"
#include "HpBar.h"

Mesh* test;

AScene::AScene()
{
}

AScene::~AScene()
{
	//delete Player::getInstance();
	//delete EnemyManager::getinstance();
	//delete AsteroidManager::getinstance();
	//delete PowerUpManager::getInstance();
	//delete HpBar::getInstance();

	//delete EntityBase::getInstance();
	//delete Graphics::getInstance();
	//delete GlobalVariables::get();

	GameObjManager::Destroy();
	GameLogic::Destroy();
	PhysicsManager::Destroy();
	TextManager::Destroy();
	CollisionManager::Destroy();
	PlayerControls::Destroy();
	HpBar::Destroy();
}

void AScene::Init()
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

	Graphics::getInstance()->init();

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//GlobalVariables::get()->worldHeight = 100;

	//GlobalVariables::get()->worldWidth = GlobalVariables::get()->worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	Math::InitRNG();

	test = MeshBuilder::GenerateAxes("", 100, 100, 100);
	//background = EntityBase::getInstance()->getEntity("BACKGROUND");


	GameLogic::GetInstance()->init();
	GameObjManager::GetInstance();
	PlayerControls::GetInstance()->init();
}


void AScene::Update(double dt)
{
	//GlobalVariables::get()-> worldHeight = 100.f;
	//GlobalVariables::get()-> worldWidth = GlobalVariables::get()->worldHeight *
	//	(float)Application::GetWindowWidth() / (float)Application::GetWindowHeight();

	GameObjManager::GetInstance()->update_all_game_objs(dt);
	GameLogic::GetInstance()->update(dt);
	PlayerControls::GetInstance()->update(dt);

	PhysicsManager::GetInstance()->update(dt);
	//Update collisions
	CollisionManager::GetInstance()->update(dt);


	fps = 1.0 / dt;
	TextManager::GetInstance()->add_text(0, "fps: " + std::to_string(fps));
}



void AScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(-*GlobalVariables::get()->worldWidth * 0.5f, *GlobalVariables::get()->worldWidth * 0.5f, -*GlobalVariables::get()->worldHeight * 0.5f, *GlobalVariables::get()->worldHeight * 0.5f, -10, 10);
	Graphics::getInstance()->projectionStack.LoadMatrix(projection);

	// Camera matrix
	Graphics::getInstance()->viewStack.LoadIdentity();
	Graphics::getInstance()->viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	// Model matrix : an identity matrix (model will be at the origin)
	Graphics::getInstance()->modelStack.LoadIdentity();

	MS& ms = Graphics::getInstance()->modelStack;
	//RenderHelper::RenderMesh(test, false);

	//glEnable(GL_DEPTH_TEST);
	GameObjManager::GetInstance()->render_all_game_objs();
	//glDisable(GL_DEPTH_TEST);
	TextManager::GetInstance()->render_all_text();
	GameLogic::GetInstance()->render_info();

	CollisionManager::GetInstance()->render_partition_lines();
}

void AScene::Exit()
{

	if (test)
	{
		delete test;
		test = nullptr;
	}


}
