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
#include "AudioPlayer.h"
#include "GameLogic.h"
#include "EnvironmentManager.h"
#include "RenderManager.h"

#include "CharacterInfo.h"
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

	GameObjectManager::GetInstance()->load_objects("Image\\lvl0objects.txt");

	
		//Example of Audio playing //
	/*audioPlayer.playlist.push_back(new Sound("Audio//MAINMENU.mp3"));
	audioPlayer.playlist.push_back(new Sound("Audio//explosion.wav"));
	
	audioPlayer.playSoundThreaded(audioPlayer.playlist[0]->fileName_);*/
	

}


void GameScene::Update(double dt)
{
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);

	PhysicsManager::GetInstance()->update(dt);
	//Update collisions
	CollisionManager::GetInstance()->update(dt);


	fps = 1.0 / dt;
	//TextManager::GetInstance()->add_text(0, "fps: " + std::to_string(fps));
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

	RenderManager::GetInstance()->render_all_active_objects();
}

void GameScene::Exit()
{

	if (axis)
	{
		delete axis;
		axis = nullptr;
	}

	//Do this later when the variables are loaded.
	//CharacterInfo.Save();

}
