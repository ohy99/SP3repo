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

#include "CharacterInfo.h"
#include "SpriteAnimation.h"

#include "SeasonManager.h"

#include "WeaponInfo.h"
#include "SpellManager.h"
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

	isPause = false;
		//Example of Audio playing //
	audioPlayer.playlist.push_back(new Sound("Audio//YARUTA.mp3"));
	audioPlayer.playlist.push_back(new Sound("Audio//explosion.wav"));
	
	audioPlayer.playSoundThreaded(audioPlayer.playlist[0]->fileName_);

	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Poster"));
	if (sa)
	{

		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 5, 1, 10.0f, true);
	}
	CharacterInfo.Init();
	/*weap.Init();
	weap.set_faction_side(Faction::FACTION_SIDE::PLAYER);
	weap.mesh = MeshList::GetInstance()->getMesh("CANNON");
	weap.scale.Set(5, 5, 5);
	weap.active = true;
	weap.pos.Set(7.5, 25);
	weap.set_damage(50);
	RenderManager::GetInstance()->attach_renderable(&weap, 1);
*/
	SeasonManager::GetInstance()->set_season((SeasonManager::SEASON_TYPE)Math::RandIntMinMax(0, 3));
	//cout << SeasonManager::GetInstance()->get_season() << endl;
	CharacterInfo.Load();
}


void GameScene::Update(double dt)
{

	
//Test out for variable in characterinfo save	cout << CharacterInfo.getcurrentcoins() << endl;
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Poster"));
	if (sa)
	{

		sa->Update(dt);
		sa->m_anim->animActive = true;
	}
	CharacterInfo.Update(dt);

	/*GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);


	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);
	cout << isPause << endl;
	static bool PButtonState = false;
	if (Application::IsKeyPressed('P') && !PButtonState)
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

*/
//	weap.WeaponInfo::Update(dt);

	if (!isPause)
	{
		SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Poster"));
		if (sa)
		{

			sa->Update(dt);
			sa->m_anim->animActive = true;
		}


		GameLogic::GetInstance()->update(dt);
		GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);


		//static bool keypressed = false;
		//if (Application::GetInstance().IsMousePressed(1) && !keypressed)
		//{
		//	weap.dir = -weap.pos + cursor_point_in_world_space;
		//	weap.dir.Normalize();
		//	weap.Discharge(weap.pos, weap.dir);
		//	keypressed = true;
		//}
		//else if (!Application::GetInstance().IsMousePressed(1) && keypressed)
		//{
		//	keypressed = false;
		//}
		//weap.WeaponInfo::Update(dt);

		{
			static bool dakeypressed = false;
			if (Application::GetInstance().IsKeyPressed('6') && !dakeypressed)
			{
				SpellManager::GetInstance()->useLightningSpell();
				dakeypressed = true;
			}
			else if (!Application::GetInstance().IsKeyPressed('6') && dakeypressed)
			{
				dakeypressed = false;
			}
		}
		SpellManager::GetInstance()->update(dt);
		MinionManager::GetInstance()->update(dt);
		PhysicsManager::GetInstance()->update(dt);
		//Update collisions
		CollisionManager::GetInstance()->update(dt);

		//update the show hp thing
		ShowHpManager::GetInstance()->update(dt);

		fps = 1.0 / dt;

		//TextManager::GetInstance()->add_text(0, "fps: " + std::to_string(fps));

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
	ms.Translate(0, 5.f * ((800.f / 600.f) - ((float)Application::GetWindowWidth() / (float)Application::GetWindowHeight())), 0);
	RenderManager::GetInstance()->render_all_active_objects();
	ShowHpManager::GetInstance()->render_all_hp_text();
	ms.PopMatrix();

	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Poster"));
	ms.PushMatrix();
	ms.Translate(50, 50, 0);
	ms.Scale(10, 10, 10);
	RenderHelper::RenderMesh(sa, false);
	//sa->Render();
	ms.PopMatrix();

	if (isPause)
	{
		ms.PushMatrix();
		ms.Translate(worldWidth/2,worldHeight/2, 0);
		ms.Scale(Vector3(100, 80, 1));
		RenderHelper::RenderMesh(pausescreen, false);
		ms.PopMatrix();
	}
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

}
