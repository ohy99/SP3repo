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



Mainmenu::Mainmenu()
{
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
	//background = EntityBase::getInstance()->getEntity("BACKGROUND");
	//play = MeshBuilder::GenerateQuad("", Color(1, 1, 1), 30);
	//play->textureID = LoadTGA("Image\\play.tga");
	//quit = MeshBuilder::GenerateQuad("", Color(1, 1, 1), 30);
	//quit->textureID = LoadTGA("Image\\quit.tga");

	//option = MeshBuilder::GenerateQuad("", Color(1, 1, 1), 30);
	//option->textureID = LoadTGA("Image\\options.tga");

	playbutt.pos.Set(0, 12.5, 0);
	playbutt.resize_button(20, 10);
	playbutt.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");
	optionbutt.pos.Set(0, 0, 0);
	optionbutt.resize_button(35, 10);
	optionbutt.mesh = MeshList::GetInstance()->getMesh("OPTIONSBUTTON");
	quitbutt.pos.Set(0, -12.5, 0);
	quitbutt.resize_button(20, 10);
	quitbutt.mesh = MeshList::GetInstance()->getMesh("QUITBUTTON");
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
	//if (x>Application::GetWindowWidth/2 )
	//if(float(x / w * worldWidth)&& float((h - y) / h * worldHeight))
	//{
	//	if (Application::IsKeyPressed('1'))
	//	{
	//		SceneManager::GetInstance()->setNextScene("QUIT");
	//	}
	//}

	Vector3 cursor_point_in_world_space(x / w * worldWidth - worldWidth * 0.5f, (Application::GetWindowHeight() - y) / h * worldHeight - worldHeight * 0.5f);
	Collision cursor_collider;
	cursor_collider.collisionType = Collision::POINT;
	cursor_collider.mid = &cursor_point_in_world_space;

	if (playbutt.collision.isCollide(cursor_collider))
	{
		std::cout << cursor_point_in_world_space << std::endl;
		//SceneManager::GetInstance()->setNextScene("QUIT");
	}
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
	RenderHelper::RenderMesh(axis, false);
	
	//ms.PushMatrix();
	//ms.Scale(Vector3(3, 1, 1));

	//ms.PushMatrix();
	//ms.Translate(0, 10, 0);
	////RenderHelper::RenderMesh(play, false);
	//ms.PopMatrix();

	////ms.PushMatrix();
	////ms.Translate(0, -30, 0);
	////RenderHelper::RenderMesh(quit, false);
	////ms.PopMatrix();

	////ms.PushMatrix();
	////ms.Translate(0, -10, 0);
	////RenderHelper::RenderMesh(option, false);
	////ms.PopMatrix();


	//ms.PopMatrix();


	playbutt.render_button();
	optionbutt.render_button();
	quitbutt.render_button();


}

void Mainmenu::Exit()
{

	if (axis)
	{
		delete axis;
		axis = nullptr;
	}


}
