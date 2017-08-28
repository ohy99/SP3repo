#include "Trans.h"
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

#include "CharacterInfo.h"
#include "SpriteAnimation.h"

#include "SeasonManager.h"

#include "WeaponInfo.h"
#include "SpellManager.h"
#include "ObjectPoolManager.h"
#include "HUDManager.h"

Trans::Trans()
{
	axis = nullptr;
}

Trans::~Trans()
{
	PhysicsManager::Destroy();
	CollisionManager::Destroy();
}

void Trans::Init()
{
	glClearColor(0.0f, 0.0f, 0.f, 0.0f);
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it cTransr to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	Graphics::GetInstance()->init();

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	worldHeight = 100;
	worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	Math::InitRNG();

	axis = MeshList::GetInstance()->getMesh("TRANS");
	rj = 0.0;

	audioPlayer.playlist.push_back(new Sound("Audio//MAINMENU.mp3"));
	audioPlayer.playlist.push_back(new Sound("Audio//explosion.wav"));
	audioPlayer.playlist.push_back(new Sound("Audio//Level2.mp3"));
	audioPlayer.playlist.push_back(new Sound("Audio//Level3.mp3"));
	audioPlayer.playlist.push_back(new Sound("Audio//Level4.mp3"));

	if (EnemyAiLogic::GetInstance()->get_level() == 1)
		audioPlayer.playLoop(audioPlayer.playlist[0]->fileName_);

	if (EnemyAiLogic::GetInstance()->get_level() == 2)
		audioPlayer.playLoop(audioPlayer.playlist[1]->fileName_);

	if (EnemyAiLogic::GetInstance()->get_level() == 3)
		audioPlayer.playLoop(audioPlayer.playlist[2]->fileName_);

	if (EnemyAiLogic::GetInstance()->get_level() == 4)
		audioPlayer.playLoop(audioPlayer.playlist[3]->fileName_);
}


void Trans::Update(double dt)
{
	worldHeight = 100;
	worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	double x, y;
	Application::GetCursorPos(&x, &y);
	rj += dt;
	if (rj >= 5.0)
	{
		int level = EnemyAiLogic::GetInstance()->get_level() + 1;
		SceneManager::GetInstance()->setNextScene("GAME");
		EnemyAiLogic::GetInstance()->set_level(level);
		rj = 0.0;
	}
	
}



void Trans::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(-worldWidth * 0.5f, worldWidth * 0.5f, -worldHeight * 0.5f, worldHeight * 0.5f, -10, 10);
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
	ms.PushMatrix();
	ms.Scale(135, 100, 1);
	RenderHelper::RenderMesh(axis, false);
	ms.PopMatrix();

	//ms.PushMatrix();
	//ms.Scale(Vector3(3, 1, 1));

}

void Trans::Exit()
{
	audioPlayer.pause();



}
