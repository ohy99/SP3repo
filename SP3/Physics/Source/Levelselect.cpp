#include "Levelselect.h"
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
#include "EnemyAiLogic.h"

Levelselect::Levelselect()
{
}

Levelselect::~Levelselect()
{
	PhysicsManager::Destroy();
	CollisionManager::Destroy();
	PhysicsManager::Destroy();
	CollisionManager::Destroy();
	GameObjectManager::Destroy();
	GameLogic::Destroy();
	MeshList::Destroy();
	EnvironmentManager::Destroy();
	RenderManager::Destroy();
}

void Levelselect::Init()
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

	worldHeight = 100;
	worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	Math::InitRNG();

	axis = MeshList::GetInstance()->getMesh("MENUBACKGROUND");
	//background = EntityBase::getInstance()->getEntity("BACKGROUND");

	LevelSelect.pos.Set(0, 25, 0);
	LevelSelect.resize_button(50, 10);
	LevelSelect.mesh = MeshList::GetInstance()->getMesh("LEVELSELECTBUTTON");

	Level1.pos.Set(-30, 0, 0);
	Level1.resize_button(40, 10);
	Level1.mesh = MeshList::GetInstance()->getMesh("LEVEL1");

	Level2.pos.Set(30, 0, 0);
	Level2.resize_button(40, 10);
	Level2.mesh = MeshList::GetInstance()->getMesh("LEVEL2");

	Level3.pos.Set(-30, -20, 0);
	Level3.resize_button(40, 10);
	Level3.mesh = MeshList::GetInstance()->getMesh("LEVEL3");

	Level4.pos.Set(30, -20, 0);
	Level4.resize_button(40, 10);
	Level4.mesh = MeshList::GetInstance()->getMesh("LEVEL4");

	Back.pos.Set(45, -40, 0);
	Back.resize_button(30, 15);
	Back.mesh = MeshList::GetInstance()->getMesh("BACK");

	audioPlayer.playlist.push_back(new Sound("Audio//YARUTA.mp3"));
	audioPlayer.playlist.push_back(new Sound("Audio//explosion.wav"));

	audioPlayer.playSoundThreaded(audioPlayer.playlist[0]->fileName_);
}


void Levelselect::Update(double dt)
{
	worldHeight = 100;
	worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	double x, y;
	Application::GetCursorPos(&x, &y);

	PhysicsManager::GetInstance()->update(dt);
	//Update collisions
	CollisionManager::GetInstance()->update(dt);

	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();

	fps = 1.0 / dt;
	//TextManager::GetInstance()->add_text(0, "fps: " + std::to_string(fps));
	Vector3 cursor_point_in_world_space(x / w * worldWidth - worldWidth * 0.5f, (Application::GetWindowHeight() - y) / h * worldHeight - worldHeight * 0.5f);
	Collision cursor_collider;
	cursor_collider.collisionType = Collision::POINT;
	cursor_collider.mid = &cursor_point_in_world_space;
	static bool pressle = false;
	//	std::cout << "options:" << audioPlayer.getCurrentVolume() << std::endl;
	if (Application::IsMousePressed(0) && !pressle)
	{
		if (Level1.collision.isCollide(cursor_collider))
		{
			EnemyAiLogic::GetInstance()->set_level(1);
			SceneManager::GetInstance()->setNextScene("GAME");
			audioPlayer.pause();
		}
		if (Level2.collision.isCollide(cursor_collider))
		{
			EnemyAiLogic::GetInstance()->set_level(2);
			SceneManager::GetInstance()->setNextScene("GAME");
			audioPlayer.pause();
		}
		if (Level3.collision.isCollide(cursor_collider))
		{
			EnemyAiLogic::GetInstance()->set_level(3);
			SceneManager::GetInstance()->setNextScene("GAME");
			audioPlayer.pause();
		}
		if (Level4.collision.isCollide(cursor_collider))
		{
			EnemyAiLogic::GetInstance()->set_level(4);
			SceneManager::GetInstance()->setNextScene("GAME");
			audioPlayer.pause();
		}

		if (Back.collision.isCollide(cursor_collider))
		{
			SceneManager::GetInstance()->setNextScene("MAIN");
			audioPlayer.pause();
		}
		pressle = true;
	}
	else if (!Application::IsMousePressed(0) && pressle)
		pressle = false;
}



void Levelselect::Render()
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

	LevelSelect.render_button();
	Level1.render_button();
	Level2.render_button();
	Level3.render_button();
	Level4.render_button();
	Back.render_button();
}

void Levelselect::Exit()
{

	//if (axis)
	//{
	//	delete axis;
	//	axis = nullptr;
	//}


}
