#include "SceneCollision.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshBuilder.h"

SceneCollision::SceneCollision()
{
}

SceneCollision::~SceneCollision()
{
}

void SceneCollision::Init()
{
	SceneBase::Init();

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);//red
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1), 2.f);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1);

	//Physics code here
	m_speed = 1.f;
	
	Math::InitRNG();

	m_objectCount = 0;

	m_ghost = new GameObject(GameObject::GO_BALL);

	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();


	GameObject* temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_WALL;
	temp->scale.Set(20, 3);
	temp->normal.Set(0, 1, 0);
	temp->pos.SetZero();
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(-10, 0, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(10, 0, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	//2

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_WALL;
	temp->scale.Set(20, 3);
	temp->normal.Set(0, 1, 0);
	temp->pos.Set(0, 28.5, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(-10, 28.5, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(10, 28.5, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	//3
	float radian = Math::DegreeToRadian(45.f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_WALL;
	temp->scale.Set(20, 3);
	temp->normal.Set(1, 1, 0);
	temp->normal.Normalize();
	temp->pos.Set(20, 20, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(-10.f * cos(radian) + 20, 10.f * sin(radian) + 20, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(10.f * cos(radian) + 20.f, -10.f * sin(radian) + 20.f, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	//4

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_WALL;
	temp->scale.Set(20, 3);
	temp->normal.Set(1, 0, 0);
	temp->pos.Set(28.5, 0, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(28.5, 10, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(28.5, -10, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	//5

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_WALL;
	temp->scale.Set(20, 3);
	temp->normal.Set(1, -1, 0);
	temp->normal.Normalize();
	temp->pos.Set(20, -20, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(-10.f * cos(radian) + 20, -10.f * sin(radian) - 20, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(10.f * cos(radian) + 20.f, 10.f * sin(radian) - 20.f, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	//6

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_WALL;
	temp->scale.Set(20, 3);
	temp->normal.Set(0, -1, 0);
	temp->pos.Set(0, -28.5, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(-10, -28.5, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(10, -28.5, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	//7

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_WALL;
	temp->scale.Set(20, 3);
	temp->normal.Set(-1, -1, 0);
	temp->normal.Normalize();
	temp->pos.Set(-20, -20, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(-10.f * cos(radian) - 20, 10.f * sin(radian) - 20, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(10.f * cos(radian) - 20.f, -10.f * sin(radian) - 20.f, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	//8

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_WALL;
	temp->scale.Set(20, 3);
	temp->normal.Set(-1, 0, 0);
	temp->pos.Set(-28.5, 0, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(-28.5, -10, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(-28.5, 10, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	//9

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_WALL;
	temp->scale.Set(20, 3);
	temp->normal.Set(-1, 1, 0);
	temp->normal.Normalize();
	temp->pos.Set(-20, 20, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(-10.f * cos(radian) - 20, -10.f * sin(radian) + 20, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

	temp = FetchGO();
	temp->active = true;
	temp->type = GameObject::GO_PILLAR;
	temp->scale.Set(1.5, 1.5);
	temp->pos.Set(10.f * cos(radian) - 20.f, 10.f * sin(radian) + 20.f, 0);
	temp->pos += Vector3(m_worldWidth*0.5f, m_worldHeight*0.5f);

}

GameObject* SceneCollision::FetchGO()
{
	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(!go->active)
		{
			go->active = true;
			++m_objectCount;
			return go;
		}
	}
	for(unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_BALL);
		m_goList.push_back(go);
	}
	GameObject *go = m_goList.back();
	go->active = true;
	++m_objectCount;
	return go;
}

bool SceneCollision::CheckCollision(GameObject *go, GameObject *go2, float dt)
{
	if (go->type == GameObject::GO_BALL && go2->type == GameObject::GO_BALL)
	{
		float distSquared = (go->pos - go2->pos).LengthSquared();
		float combinedRadius = go->scale.x + go2->scale.x;

		//Practical 4, Exercise 13: improve collision detection algorithm
		if (distSquared <= combinedRadius * combinedRadius)
		{
			Vector3 relative_position = go->pos - go2->pos;
			Vector3 relative_velocity = go->vel - go2->vel;
			if (relative_velocity.Dot(relative_position) < 0)
				return true;
			else
				return false;
			//Exercise 3: audit kinetic energy
		}
	}
	if (go->type == GameObject::GO_BALL && go2->type == GameObject::GO_WALL)
	{
		Vector3 ball_to_wall = go2->pos - go->pos;
		Vector3 normal_perpendicular = go2->normal.Cross(Vector3(0, 0, 1)).Normalize();
		Vector3 relative_position = go->pos - go2->pos;
		Vector3 N = go2->normal;
		if (relative_position.Dot(N) > 0)
			N = -N;
		return (abs(ball_to_wall.Dot(N)) < go->scale.x + go2->scale.y * 0.5f && abs(ball_to_wall.Dot(normal_perpendicular)) < go->scale.x + go2->scale.x * 0.5f);
	}
	if (go->type == GameObject::GO_BALL && go2->type == GameObject::GO_PILLAR)
	{
		return (go2->pos - go->pos).LengthSquared() < (go->scale.x + go2->scale.x) * (go->scale.x + go2->scale.x);
	}
	return false;
}

void SceneCollision::Update(double dt)
{
	SceneBase::Update(dt);
	
	if(Application::IsKeyPressed('9'))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if(Application::IsKeyPressed('0'))
	{
		m_speed += 0.1f;
	}

	//Mouse Section
	static bool bLButtonState = false;
	if(!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

		m_ghost->pos.Set(posX, posY, 0); //IMPT
		m_ghost->active = true;
		float sc = 2;
		m_ghost->scale.Set(sc, sc, sc);
	}
	else if(bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;

		//spawn small GO_BALL
		GameObject *go = FetchGO();
		go->active = true;
		go->type = GameObject::GO_BALL;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

		go->pos = m_ghost->pos;
		go->vel.Set(m_ghost->pos.x - posX, m_ghost->pos.y - posY, 0);
		m_ghost->active = false;
		float sc = 2;
		Vector3 s((posX - m_ghost->pos.x) * 10.f / m_worldWidth, 
			(posY - m_ghost->pos.y) * 10.f / m_worldHeight);
		sc = Math::Clamp(s.Length() , 2.f, 10.f);
		go->scale.Set(sc, sc, sc);
		go->mass = sc * sc * sc;
	}
	static bool bRButtonState = false;
	if(!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;

		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

		m_ghost->pos.Set(posX, posY, 0); //IMPT
		m_ghost->active = true;
		float sc = 3;
		m_ghost->scale.Set(sc, sc, sc);
	}
	else if(bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;

		//spawn large GO_BALL
		GameObject *go = FetchGO();
		go->active = true;
		go->type = GameObject::GO_BALL;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

		go->pos = m_ghost->pos;
		go->vel.Set(m_ghost->pos.x - posX, m_ghost->pos.y - posY, 0);
		m_ghost->active = false;
		float sc = 3;
		go->scale.Set(sc, sc, sc);
		go->mass = sc * sc * sc;
	}

	//Physics Simulation Section
	dt *= m_speed;

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			go->pos += go->vel * static_cast<float>(dt);

			//Exercise 2a: Rebound game object at screen edges
			if (go->pos.x > m_worldWidth - go->scale.x && go->vel.x > 0) {
				go->vel.x = -go->vel.x;
			}
			if (go->pos.x < 0 + go->scale.x && go->vel.x < 0) {
				go->vel.x = -go->vel.x;
			}
			if (go->pos.y > m_worldHeight - go->scale.y && go->vel.y > 0)
			{
				go->vel.y = -go->vel.y;
			}
			if (go->pos.y < 0 + go->scale.y && go->vel.y < 0)
			{
				go->vel.y = -go->vel.y;
			}

			//Exercise 2b: Unspawn if it really leave the screen
			if (go->pos.x > m_worldWidth + go->scale.x || go->pos.x < 0 - go->scale.x || go->pos.y > m_worldHeight + go->scale.y || go->pos.y < 0 - go->scale.y)
			{
				go->active = false;
				--m_objectCount;
			}

			for(std::vector<GameObject *>::iterator it2 = it + 1; it2 != m_goList.end(); ++it2)
			{
				GameObject *go2 = static_cast<GameObject *>(*it2);
				if(go2->active)
				{
					//Exercise 1: move collision code to CheckCollision()
					//if (!CheckCollision(go, go2, dt))
					//	continue;
					if (go->type == GameObject::GO_WALL && go2->type == GameObject::GO_WALL)
						continue;


						//CollisionResponse(go, go2, dt);
					GameObject *ball = go, *other = go2;
					if (ball->type != GameObject::GO_BALL)
					{
						if (other->type != GameObject::GO_BALL)
							continue;
						ball = go2;
						other = go;
					}
					if (CheckCollision(ball,other,(float)dt))
						CollisionResponse(ball, other, dt);
					

				}
			}
		}
	}
}


void SceneCollision::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_BALL:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GAMEOBJECT_TYPE::GO_WALL:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(Math::RadianToDegree(atan2(go->normal.y, go->normal.x)) - 90.f, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_QUAD], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GAMEOBJECT_TYPE::GO_PILLAR:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	}
}

void SceneCollision::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
	
	RenderMesh(meshList[GEO_AXES], false);

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}
	if(m_ghost->active)
		RenderGO(m_ghost);

	//On screen text
	std::ostringstream ss;
	ss << "Object count: " << m_objectCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 9);

	ss.str(std::string());
	ss.precision(5);
	ss << "Initial KE: " << initialKE;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 21);

	ss.str(std::string());
	ss.precision(5);
	ss << "Final   KE: " << finalKE;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 18);

	ss.str(std::string());
	ss.precision(5);
	ss << "Initial momentum: " << initialMomentum;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 15);
	
	ss.str(std::string());
	ss.precision(5);
	ss << "Final   momentum: " << finalMomentum;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 12);

	//Exercise 3: render initial and final kinetic energy
	
	ss.str(std::string());
	ss.precision(3);
	ss << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6);
	
	ss.str(std::string());
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);
	
	RenderTextOnScreen(meshList[GEO_TEXT], "Collision", Color(0, 1, 0), 3, 0, 0);
}

void SceneCollision::CollisionResponse(GameObject* go, GameObject* go2, float dt)
{
	if (go->type == GameObject::GO_BALL && go2->type == GameObject::GO_BALL)
	{
		m1 = go->mass;
		m2 = go2->mass;
		u1 = go->vel;
		u2 = go2->vel;

		initialMomentum = m1 * u1 + m2 * u2;

		Vector3 momentum1 = go->mass * go->vel;
		Vector3 momentum2 = go2->mass * go2->vel;

		float ke1, ke2;
		ke1 = 0.5f * go->mass * go->vel.LengthSquared();
		ke2 = 0.5f * go2->mass * go2->vel.LengthSquared();

		initialKE = ke1 + ke2;

		Vector3 normalAxis = go2->pos - go->pos;
		normalAxis.Normalize();

		go->vel = u1 + (2.0 * m2 / (m1 + m2)) * (u2.Dot(normalAxis) * normalAxis - u1.Dot(normalAxis) * normalAxis);
		go2->vel = u2 + (2.0 * m1 / (m2 + m1)) * (u1.Dot(normalAxis) * normalAxis - u2.Dot(normalAxis) * normalAxis);

		v1 = go->vel;
		v2 = go2->vel;

		finalMomentum = m1 * v1 + m2 * v2;
		finalKE = 0.5f * go->mass * go->vel.LengthSquared() + 0.5f * go2->mass * go2->vel.LengthSquared();

	}
	else if ((go->type == GameObject::GO_BALL && go2->type == GameObject::GO_WALL) || (go2->type == GameObject::GO_BALL && go->type == GameObject::GO_WALL))
	{
		GameObject* ball;
		GameObject* wall;
		if (go->type == GameObject::GO_BALL) {
			ball = go;
			wall = go2;
		}
		else
		{
			ball = go2;
			wall = go;
		}

		Vector3 ball_to_wall = -ball->pos + wall->pos;

		Vector3 normal_perpendicular = wall->normal.Cross(Vector3(0, 0, 1)).Normalize();


		{
			ball->vel = ball->vel - (2.f * ball->vel.Dot(wall->normal)) * wall->normal;
		}


	}
	else if (go2->type == GameObject::GO_PILLAR)
	{
		GameObject* ball = go;
		GameObject* pillar = go2;
		Vector3 normal = pillar->pos - ball->pos;
		normal.Normalize();

		ball->vel = ball->vel - (2.f * ball->vel.Dot(normal)) * normal;
	}
}

float SceneCollision::CheckCollision2(GameObject *go1, GameObject *go2, float dt)
{
	return 1;
}


void SceneCollision::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if(m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}
