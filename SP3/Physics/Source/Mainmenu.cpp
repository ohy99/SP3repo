#include "Mainmenu.h"
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

Mainmenu::Mainmenu()
{
	axis = nullptr;
}

Mainmenu::~Mainmenu()
{
	PhysicsManager::Destroy();
	CollisionManager::Destroy();
}

void Mainmenu::Init()
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

	axis = MeshBuilder::GenerateAxes("", 100, 100, 100);
	playbutt.pos.Set(0, 9, 0);
	playbutt.resize_button(20, 10);
	playbutt.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");
	optionbutt.pos.Set(0, -25, 0);
	optionbutt.resize_button(35, 10);
	optionbutt.mesh = MeshList::GetInstance()->getMesh("OPTIONSBUTTON");
	quitbutt.pos.Set(0, -40.5, 0);
	quitbutt.resize_button(20, 10);
	quitbutt.mesh = MeshList::GetInstance()->getMesh("QUITBUTTON");
	levelselectbutt.pos.Set(0, -7.5, 0);
	levelselectbutt.resize_button(40, 10);
	levelselectbutt.mesh = MeshList::GetInstance()->getMesh("LEVELSELECTBUTTON");
	title.pos.Set(0, 35, 0);
	title.resize_button(80, 30);
	title.mesh = MeshList::GetInstance()->getMesh("TITLE");

	audioPlayer.playlist.push_back(new Sound("Audio//MAINMENU.mp3"));
	audioPlayer.playlist.push_back(new Sound("Audio//explosion.wav"));

	audioPlayer.playSoundThreaded(audioPlayer.playlist[0]->fileName_);
}


void Mainmenu::Update(double dt)
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
	//std::cout << float(x / w * worldWidth) << std::endl;
	fps = 1.0 / dt;
	//TextManager::GetInstance()->add_text(0, "fps: " + std::to_string(fps));

	Vector3 cursor_point_in_world_space(x / w * worldWidth - worldWidth * 0.5f, (Application::GetWindowHeight() - y) / h * worldHeight - worldHeight * 0.5f);
	Collision cursor_collider;
	cursor_collider.collisionType = Collision::POINT;
	cursor_collider.mid = &cursor_point_in_world_space;
	if (Application::IsMousePressed(0))
	{
		if (playbutt.collision.isCollide(cursor_collider))
		{
			SceneManager::GetInstance()->setNextScene("GAME");
		}
		if (levelselectbutt.collision.isCollide(cursor_collider))
		{
			SceneManager::GetInstance()->setNextScene("LEVELSELECT");
		}
		if (optionbutt.collision.isCollide(cursor_collider))
		{
			SceneManager::GetInstance()->setNextScene("OPTIONS");
		}	
		if (quitbutt.collision.isCollide(cursor_collider))
		{
			SceneManager::GetInstance()->setExitGame(true);
		}
	}
	if (Application::IsKeyPressed('1'))
		SceneManager::GetInstance()->setNextScene("WIN");
	if (Application::IsKeyPressed('2'))
		SceneManager::GetInstance()->setNextScene("LOSE");
	if (Application::IsKeyPressed('3'))
		SceneManager::GetInstance()->setNextScene("LEVELSELECT");
	//std::cout<<"main:"<<audioPlayer.getCurrentVolume()<<std::endl;
}



void Mainmenu::Render()
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
	//RenderHelper::RenderMesh(axis, false);

	//ms.PushMatrix();
	//ms.Scale(Vector3(3, 1, 1));

	static int k = 0;
	{
		static bool pressle = false;
		if (Application::IsMousePressed(0) && !pressle)
		{
			k++;
			pressle = true;
		}
		else if (!Application::IsMousePressed(0) && pressle)
			pressle = false;
	}
	{
		static bool pressle = false;
		if (Application::IsMousePressed(1) && !pressle)
		{
			k--;
			pressle = true;
		}
		else if (!Application::IsMousePressed(1) && pressle)
			pressle = false;
	}

	//ms.PushMatrix();
	//ms.Translate(0, 0, 0);
	//for (int i = 0; i < 10 - k; ++i)
	//{
	//	ms.PushMatrix();
	//	ms.Translate(i * 3, i * 0.5f, 0);
	//	ms.Scale(3, 3 + i, 0);
	//	RenderHelper::RenderMesh(playbutt.mesh, false);
	//	ms.PopMatrix();
	//}
	//ms.PopMatrix();


	////ms.PushMatrix();
	////ms.Translate(0, -30, 0);
	////RenderHelper::RenderMesh(quit, false);
	////ms.PopMatrix();




	//ms.PopMatrix();


	playbutt.render_button();
	optionbutt.render_button();
	quitbutt.render_button();
	levelselectbutt.render_button();
	title.render_button();
}

void Mainmenu::Exit()
{
	audioPlayer.pause();



}
