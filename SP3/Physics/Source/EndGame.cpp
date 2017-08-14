#include "EndGame.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "EntityBase.h"
#include "ObjHelper.h"
#include "RenderHelper.h"
#include "Graphics.h"

#include "GlobalVariableManager.h"

#include "Button.h"

#include "SceneManager.h"

#include "CalibriStyle.h"

#include "GameLogic.h"
#include "TextManager.h"

EndGame::EndGame()
{
}

EndGame::~EndGame()
{
}

void EndGame::Init()
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


	*GlobalVariables::get()->worldHeight = 100;
	//m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	*GlobalVariables::get()->worldWidth = *GlobalVariables::get()->worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	background = EntityBase::getInstance()->getEntity("BACKGROUND");
	//background = MeshBuilder::GenerateMovingTextureQuad("BACKGROUND", Color(1, 1, 1), 1, 1);
	//background->textureID = LoadTGA("Image//background.tga");

	GlobalVariables* GV = GlobalVariables::get();
	backbutton = nullptr;
	backbutton = new Button("BACK");
	backbutton->scale.Set(*GV->worldWidth * 0.1f, *GV->worldHeight * 0.1f);
	backbutton->pos.Set(0 + backbutton->scale.x * 0.6f, 0 + backbutton->scale.y * 0.6f);
	//backbutton->pos.Set(0, 0);
	backbutton->collision.setCollisionType(Collision::CollisionType::AABB);
	backbutton->collision.mid = &backbutton->pos;
	backbutton->collision.min.Set(-backbutton->scale.x * 0.5f, -backbutton->scale.y * 0.5f);
	backbutton->collision.max.Set(backbutton->scale.x * 0.5f, backbutton->scale.y * 0.5f);

	if (GameLogic::GetInstance()->game_won == false)
	{
		//LOSE
		endGameText = "You Lose!";
	}
	else
	{
		endGameText = "You Win!";
	}
}


void EndGame::Update(double dt)
{
	GlobalVariables* GV = GlobalVariables::get();
	*GV->worldHeight = 100.f;
	*GV->worldWidth = *GV->worldHeight * (float)Application::GetWindowWidth() / (float)Application::GetWindowHeight();

	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursorpt((x / (double)w) * *GV->worldWidth, (1.0 - (y / (double)h)) * *GV->worldHeight);
	Collision cpt;
	cpt.setCollisionType(Collision::CollisionType::POINT);
	cpt.mid = &cursorpt;


	if (backbutton->collision.isCollide(cpt))
	{
		backbutton->scale.Set(*GV->worldWidth * 0.15f, *GV->worldHeight * 0.15f);

		if (Application::IsMousePressed(0))
		{
			SceneManager::getInstance()->setNextScene("MENU");
			return;
		}
	}
	else
	{
		backbutton->scale.Set(*GV->worldWidth * 0.1f, *GV->worldHeight * 0.1f);
		backbutton->pos.Set(0 + backbutton->scale.x * 0.6f, 0 + backbutton->scale.y * 0.6f);
	}
	fps = 1.0 / dt;
}



void EndGame::Render()
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

	Graphics::getInstance()->modelStack.PushMatrix();
	Graphics::getInstance()->modelStack.Translate(*GlobalVariables::get()->worldWidth * 0.5f - *GlobalVariables::get()->worldWidth * 0.15f, 
		*GlobalVariables::get()->worldHeight * 0.5f - (*GlobalVariables::get()->worldHeight* 0.1f * 0.5f), 0);
	Graphics::getInstance()->modelStack.Scale(*GlobalVariables::get()->worldWidth * 0.1f, *GlobalVariables::get()->worldHeight* 0.1f, 1);

	Color color;
	if (endGameText == "You Win!")
		color.Set(0, 1, 0);
	else
		color.Set(1, 0, 0);
	RenderHelper::RenderText(&TextManager::GetInstance()->calibri, endGameText, color);
	Graphics::getInstance()->modelStack.PopMatrix();

	renderThing(backbutton);




	glDisable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	//RenderHelper::RenderTextOnScreen(GlobalVariables::get()->text, std::to_string(fps), Color(1, 1, 1), 2, 0, 0);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
}

void EndGame::Exit()
{
	//SceneBase::Exit();
	//Cleanup GameObjects

	if (backbutton)
	{
		delete backbutton;
		backbutton = nullptr;
	}
	//if (background)
	//	delete background;
}

void EndGame::renderThing(GameObj* a)
{
	Graphics::getInstance()->modelStack.PushMatrix();
	Graphics::getInstance()->modelStack.Translate(a->pos.x, a->pos.y, a->pos.z);
	Graphics::getInstance()->modelStack.Scale(a->scale.x, a->scale.y, 1);
	RenderHelper::RenderMesh(a->getMesh(), false);
	Graphics::getInstance()->modelStack.PopMatrix();
}