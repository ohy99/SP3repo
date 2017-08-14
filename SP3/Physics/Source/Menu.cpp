#include "Menu.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "EntityBase.h"
#include "ObjHelper.h"
#include "RenderHelper.h"
#include "Graphics.h"

#include "GlobalVariableManager.h"
#include "HpBar.h"
#include "Button.h"

#include "MeshBuilder.h"
#include "FontType.h"
#include "CalibriStyle.h"

#include "SceneManager.h"
SceneManager* SceneManager::instance = nullptr;

EntityBase* EntityBase::instance = NULL;
ObjHelper* ObjHelper::instance = NULL;
Graphics* Graphics::instance = NULL;
GlobalVariables* GlobalVariables::instance = nullptr;

#include "GameLogic.h"


Menu::Menu()
{
}

Menu::~Menu()
{
	delete GlobalVariables::get();
	delete EntityBase::getInstance();
	delete Graphics::getInstance();
	delete ObjHelper::getInstance();
}

void Menu::Init()
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);


	//GlobalVariables::get()->worldHeight = 100;
	//m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//GlobalVariables::get()->worldWidth = GlobalVariables::get()->worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	static bool firstTime = true;
	if (firstTime)
	{
		Math::InitRNG();

		EntityBase::getInstance();
		ObjHelper::getInstance();
		Graphics::getInstance()->init();
		//GlobalVariables::get()->text = new CalibriStyle();

		firstTime = false;
	}


	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//if (GlobalVariables::get()->text == nullptr)
		

	background = EntityBase::getInstance()->getEntity("BACKGROUND");

	GlobalVariables* GV = GlobalVariables::get();
	GameLogic::GetInstance()->get_world_size_reference(GV->worldWidth, GV->worldHeight);

	startbutton = nullptr;
	startbutton = new Button("START");
	startbutton->pos.Set(*GV->worldWidth * 0.5f, *GV->worldHeight * 0.5f);
	//startbutton->pos.Set(0, 0);
	startbutton->scale.Set(*GV->worldWidth * 0.3f, *GV->worldHeight * 0.1f);
	startbutton->collision.setCollisionType(Collision::CollisionType::AABB);
	startbutton->collision.mid = &startbutton->pos;
	startbutton->collision.min.Set(-startbutton->scale.x * 0.5f, -startbutton->scale.y * 0.5f);
	startbutton->collision.max.Set(startbutton->scale.x * 0.5f, startbutton->scale.y * 0.5f);


	insbutton = new Button("INSTRUCTION");
	insbutton->pos.Set(*GV->worldWidth * 0.5f, *GV->worldHeight * 0.5f - startbutton->scale.y * 1.2f);
	insbutton->scale.Set(*GV->worldWidth * 0.3f, *GV->worldHeight * 0.1f);
	insbutton->collision.setCollisionType(Collision::CollisionType::AABB);
	insbutton->collision.mid = &insbutton->pos;
	insbutton->collision.min.Set(-insbutton->scale.x * 0.5f, -insbutton->scale.y * 0.5f);
	insbutton->collision.max.Set(insbutton->scale.x * 0.5f, insbutton->scale.y * 0.5f);

	exitbutton = new Button("EXIT");
	exitbutton->pos.Set(*GV->worldWidth * 0.5f, *GV->worldHeight * 0.5f
		- (startbutton->scale.y * 1.2f) - (insbutton->scale.y * 1.2f));
	exitbutton->scale.Set(*GV->worldWidth * 0.3f, *GV->worldHeight * 0.1f);
	exitbutton->collision.setCollisionType(Collision::CollisionType::AABB);
	exitbutton->collision.mid = &exitbutton->pos;
	exitbutton->collision.min.Set(-exitbutton->scale.x * 0.5f, -exitbutton->scale.y * 0.5f);
	exitbutton->collision.max.Set(exitbutton->scale.x * 0.5f, exitbutton->scale.y * 0.5f);
}


void Menu::Update(double dt)
{
	GlobalVariables* GV = GlobalVariables::get();
	*GV->worldHeight = 100.f;
	*GV-> worldWidth = *GV-> worldHeight * (float)Application::GetWindowWidth() / (float)Application::GetWindowHeight();

	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursorpt((x / (double)w) * *GV->worldWidth,( 1.0 - (y / (double)h)) * *GV->worldHeight);
	Collision cpt;
	cpt.setCollisionType(Collision::CollisionType::POINT);
	cpt.mid = &cursorpt;


	startbutton->collision.mid = &startbutton->pos;
	startbutton->collision.min.Set(-startbutton->scale.x * 0.5f, -startbutton->scale.y * 0.5f);
	startbutton->collision.max.Set(startbutton->scale.x * 0.5f, startbutton->scale.y * 0.5f);
	if (startbutton->collision.isCollide(cpt))
	{
		startbutton->scale.Set(*GV->worldWidth * 0.4f, *GV->worldHeight * 0.15f);

		if (Application::IsMousePressed(0))
		{
			SceneManager::getInstance()->setNextScene("GAME");
			return;
		}
	}
	else
	{
		startbutton->scale.Set(*GV->worldWidth * 0.3f, *GV->worldHeight * 0.1f);
		startbutton->pos.Set(*GV->worldWidth * 0.5f, *GV->worldHeight * 0.5f);
	}

	insbutton->collision.mid = &insbutton->pos;
	insbutton->collision.min.Set(-insbutton->scale.x * 0.5f, -insbutton->scale.y * 0.5f);
	insbutton->collision.max.Set(insbutton->scale.x * 0.5f, insbutton->scale.y * 0.5f);
	if (insbutton->collision.isCollide(cpt))
	{
		insbutton->scale.Set(*GV->worldWidth * 0.4f, *GV->worldHeight * 0.15f);

		if (Application::IsMousePressed(0))
		{
			SceneManager::getInstance()->setNextScene("INSTRUCTIONS");
			return;
		}
	}
	else
	{
		insbutton->scale.Set(*GV->worldWidth * 0.3f, *GV->worldHeight * 0.1f);
		insbutton->pos.Set(*GV->worldWidth * 0.5f, *GV->worldHeight * 0.5f - startbutton->scale.y * 1.2f);
		//insbutton->pos.Set(*GV->worldWidth * 0.5f, *GV->worldHeight * 0.5f);
	}

	exitbutton->collision.mid = &exitbutton->pos;
	exitbutton->collision.min.Set(-exitbutton->scale.x * 0.5f, -exitbutton->scale.y * 0.5f);
	exitbutton->collision.max.Set(exitbutton->scale.x * 0.5f, exitbutton->scale.y * 0.5f);
	if (exitbutton->collision.isCollide(cpt))
	{
		exitbutton->scale.Set(*GV->worldWidth * 0.4f, *GV->worldHeight * 0.15f);

		if (Application::IsMousePressed(0))
		{
			SceneManager::getInstance()->setExitGame(true);
			return;
		}
	}
	else
	{
		exitbutton->scale.Set(*GV->worldWidth * 0.3f, *GV->worldHeight * 0.1f);
		exitbutton->pos.Set(*GV->worldWidth * 0.5f, *GV->worldHeight * 0.5f
			- (startbutton->scale.y * 1.2f) - (insbutton->scale.y * 1.2f));
		//exitbutton->pos.Set(*GV->worldWidth * 0.5f, *GV->worldHeight * 0.5f);
	}





	fps = 1.0 / dt;
}



void Menu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, *GlobalVariables::get()->worldWidth,
		0, *GlobalVariables::get()->worldHeight, -10, 10);
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

	ObjHelper::getInstance()->renderObj();

	Graphics::getInstance()->modelStack.PushMatrix();
	Graphics::getInstance()->modelStack.Translate(*GlobalVariables::get()->worldWidth * 0.5f, *GlobalVariables::get()->worldHeight * 0.5f, 0);
	Graphics::getInstance()->modelStack.Scale(*GlobalVariables::get()->worldWidth,* GlobalVariables::get()->worldHeight, 1);
	RenderHelper::RenderMesh(background, false);
	Graphics::getInstance()->modelStack.PopMatrix();


	renderThing(startbutton);
	renderThing(insbutton);
	renderThing(exitbutton);


	glDisable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	//RenderHelper::RenderTextOnScreen(, std::to_string(fps), Color(1, 1, 1), 2, 0, 0);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
}

void Menu::Exit()
{
	//SceneBase::Exit();
	//Cleanup GameObjects

	if (startbutton)
	{
		 delete startbutton;
		 startbutton = nullptr;
	}
	if (insbutton)
	{
		delete insbutton;
		insbutton = nullptr;
	}
	if (exitbutton)
	{
		delete exitbutton;
		exitbutton = nullptr;
	}
}

void Menu::renderThing(GameObj* a)
{
	Graphics::getInstance()->modelStack.PushMatrix();
	Graphics::getInstance()->modelStack.Translate(a->pos.x, a->pos.y, a->pos.z);
	Graphics::getInstance()->modelStack.Scale(a->scale.x, a->scale.y, 1);
	RenderHelper::RenderMesh(a->getMesh(), false);
	Graphics::getInstance()->modelStack.PopMatrix();
}