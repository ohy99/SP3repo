#include "SceneAsteroid.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneAsteroid::SceneAsteroid()
{
}

SceneAsteroid::~SceneAsteroid()
{
}

void SceneAsteroid::Init()
{
	SceneBase::Init();

	//Physics code here
	m_speed = 1.f;
	
	Math::InitRNG();

	//Exercise 2a: Construct 100 GameObject with type GO_ASTEROID and add into m_goList
	for (size_t i = 0; i < 100; ++i)
		m_goList.push_back(new GameObject(GameObject::GAMEOBJECT_TYPE::GO_ASTEROID));
	

	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Exercise 2c: Construct m_ship, set active, type, scale and pos
	//Exercise 2b: Initialize m_lives and m_score
	initShip();
	EnemyLockedOn = NULL;
}

GameObject* SceneAsteroid::FetchGO()
{
	//Exercise 3a: Fetch a game object from m_goList and return it
	for (auto it : m_goList)
	{
		if (!it->active)
			return it;
	}
	for (size_t i = 0; i < 10; ++i)//Create extra 10
	{
		m_goList.push_back(new GameObject(GameObject::GAMEOBJECT_TYPE::GO_ASTEROID));
	}
	return FetchGO();
}

void SceneAsteroid::Update(double dt)
{
	SceneBase::Update(dt); 

	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	
	if(Application::IsKeyPressed('9'))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if(Application::IsKeyPressed('0'))
	{
		m_speed += 0.1f;
	}
	m_force.SetZero();
	//Exercise 6: set m_force values based on WASD
	float FORCE = 100;
	if(Application::IsKeyPressed('W'))
	{
		m_force += m_ship->dir * FORCE;
	}
	if(Application::IsKeyPressed('A'))
	{
		m_force += m_ship->dir * 5.f;

		//m_torque = (m_ship->dir.Cross(Vector3(0, 0, 1)).Normalized() - m_ship->dir).Cross(m_ship->dir * 5);//right engine
		m_torque = (m_ship->dir.Cross(Vector3(0, 0, 1)).Normalized() - m_ship->dir).Cross(m_ship->dir * 5);//right engine
	}
	if(Application::IsKeyPressed('S'))
	{
		m_force += -m_ship->dir * FORCE;
	}
	if(Application::IsKeyPressed('D'))
	{
		m_force += m_ship->dir * 5.f;
		m_torque = (m_ship->dir.Cross(Vector3(0, 0, -1)).Normalized() - m_ship->dir).Cross(m_ship->dir * 5);//left engine
	}
	//Exercise 8: use 2 keys to increase and decrease mass of ship
	if (Application::IsKeyPressed(VK_OEM_PLUS))
		m_ship->mass = Math::Min(m_ship->mass + 0.1f, 100.f);
	if (Application::IsKeyPressed(VK_OEM_MINUS))
		m_ship->mass = Math::Max(m_ship->mass - 0.1f, 0.1f);

	//Spawn enemy Ships
	static bool isCpressed = false;
	if (Application::IsKeyPressed('C') && !isCpressed)
	{
		GameObject* go = FetchGO();
		go->active = true;
		go->pos.Set(Math::RandFloatMinMax(0, m_worldWidth), Math::RandFloatMinMax(0, m_worldHeight));
		go->vel = (-go->pos + m_ship->pos).Normalized() * 10;
		go->dir = go->vel.Normalized();
		go->scale.Set(1, 1, 1);
		go->type = GameObject::GAMEOBJECT_TYPE::GO_ENEMY;

		isCpressed = true;
	}
	else if (!Application::IsKeyPressed('C') && isCpressed)
		isCpressed = false;

	static GameObject* prevLock = NULL;
	prevLock;
	EnemyLockedOn;


	spawnBullet();
	spawnMissle();
	spawnAsteroid();
	mouseControl();

	//Physics Simulation Section
	updateShip(dt);


	static float allShootTime = 0.f;
	allShoot = false;
	if (allShootTime < 1)
		allShootTime += (float)dt;
	else
	{
		allShoot = true;
		allShootTime = 0.f;
	}


	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			//Exercise 12: handle collision between GO_SHIP and GO_ASTEROID using simple distance-based check
			if (go->type == GameObject::GAMEOBJECT_TYPE::GO_ASTEROID)
			{
				updateAsteroid(go, dt);
			}


			//Exercise 16: unspawn bullets when they leave screen
			else if (go->type == GameObject::GAMEOBJECT_TYPE::GO_BULLET)
			{
				updateShipBullet(go, dt);
			}

			else if (go->type == GameObject::GAMEOBJECT_TYPE::GO_MISSLE)
			{
				updateShipMissile(go, dt);
			}

			else if (go->type == GameObject::GAMEOBJECT_TYPE::GO_ENEMY)
			{
				updateEnemyShip(go, dt);
			}

			else if (go->type == GameObject::GAMEOBJECT_TYPE::GO_ENEMY_BULLET)
			{
				updateEnemyBullet(go, dt);
			}
			
		}
	}



}


void SceneAsteroid::RenderGO(GameObject *go)
{
	modelStack.PushMatrix();
	modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
	modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
	switch(go->type)
	{
	case GameObject::GO_SHIP:
		//Exercise 4a: render a sphere with radius 1
		//modelStack.PushMatrix();
		//modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		//modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		modelStack.Rotate(Math::RadianToDegree(atan2(go->dir.y, go->dir.x)) - 90.f, 0, 0, 1);
		RenderMesh(SceneBase::meshList[SceneBase::GEOMETRY_TYPE::GEO_TRIANGLE], false);
		modelStack.PopMatrix();
		//Exercise 17a: render a ship texture or 3D ship model
		//Exercise 17b:	re-orientate the ship with velocity
		break;
	case GameObject::GO_ASTEROID:
		//Exercise 4b: render a cube with length 2
		//modelStack.PushMatrix();
		//modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		//modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(SceneBase::meshList[SceneBase::GEOMETRY_TYPE::GEO_CUBE], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_BULLET:
		//modelStack.PushMatrix();
		//modelStack.Translate(go->p)
		RenderMesh(SceneBase::meshList[SceneBase::GEOMETRY_TYPE::GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_MISSLE:
		modelStack.Rotate(Math::RadianToDegree(atan2(go->dir.y, go->dir.x)) - 90.f, 0, 0, 1);
		RenderMesh(SceneBase::meshList[SceneBase::GEOMETRY_TYPE::GEO_MISSILE], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_ENEMY:
		modelStack.Rotate(Math::RadianToDegree(atan2(go->dir.y, go->dir.x)) - 90.f, 0, 0, 1);
		RenderMesh(SceneBase::meshList[SceneBase::GEOMETRY_TYPE::GEO_ENEMY], false);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_ENEMY_BULLET:
		RenderMesh(SceneBase::meshList[SceneBase::GEOMETRY_TYPE::GEO_ENEMYBULLET], false);
		modelStack.PopMatrix();
		break;
	}
}

void SceneAsteroid::Render()
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
	if (m_ship->active)
		RenderGO(m_ship);

	//On screen text
	renderTexts();
}

void SceneAsteroid::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if(m_ship)
	{
		delete m_ship;
		m_ship = NULL;
	}
}


void SceneAsteroid::spawnAsteroid()
{
	//Exercise 11: use a key to spawn some asteroids
	static bool isVpressed = false;
	if (Application::IsKeyPressed('V') && !isVpressed)
	{
		for (size_t i = 0; i < 25; ++i)
		{
			GameObject* go = FetchGO();
			go->active = true;
			go->type = GameObject::GAMEOBJECT_TYPE::GO_ASTEROID;
			go->scale.Set(1, 1, 1);
			go->pos.Set(Math::RandFloatMinMax(0.f + go->scale.x, m_worldWidth - go->scale.x),
				Math::RandFloatMinMax(0.f + go->scale.y, m_worldHeight - go->scale.y), 0);
			//float xmag = Math::RandFloatMinMax(0.f, 5.f);
			go->vel.Set(Math::RandFloatMinMax(-5.f, 5.f), Math::RandFloatMinMax(-5.f, 5.f), 0);

			while ((go->pos - m_ship->pos).LengthSquared() < 25)//re-random if asterioid is too near
				go->pos.Set(Math::RandFloatMinMax(0.f + go->scale.x, m_worldWidth - go->scale.x),
					Math::RandFloatMinMax(0.f + go->scale.y, m_worldHeight - go->scale.y), 0);
		}
		isVpressed = true;
	}
	else if (!Application::IsKeyPressed('V') && isVpressed)
		isVpressed = false;

}

void SceneAsteroid::spawnBullet()
{

	//Exercise 14: use a key to spawn a bullet
	static bool bisSpacePressed = false;
	if (Application::IsKeyPressed(VK_SPACE) && !bisSpacePressed)
	{
		if (NumOfBullets < 20)
		{
			GameObject* go = FetchGO();
			go->active = true;
			go->type = GameObject::GAMEOBJECT_TYPE::GO_BULLET;
			try {
				go->vel = m_ship->dir.Normalized() * BULLET_SPEED;
			}
			catch (DivideByZero) {
				go->vel = Vector3(0, 1, 0) * BULLET_SPEED;
			}
			go->pos = m_ship->pos;
			go->scale.Set(0.2f, 0.2f, 0.2f);

			//Exercise 15: limit the spawn rate of bullets
			++NumOfBullets;
		}
		bisSpacePressed = true;
	}
	else if (!Application::IsKeyPressed(VK_SPACE) && bisSpacePressed)
		bisSpacePressed = false;

}

void SceneAsteroid::spawnMissle()
{
	static bool isLMBpressed = false;
	if (Application::IsMousePressed(0) && !isLMBpressed)
	{
		if (NumOfMissiles < 10)//LIMIT MISSILE
		{
			GameObject* go = FetchGO();
			go->active = true;
			go->type = GameObject::GAMEOBJECT_TYPE::GO_MISSLE;

			go->scale.Set(1, 1, 1);
			go->pos = m_ship->pos;

			if (EnemyLockedOn == NULL)
			{
				for (auto it : m_goList)
				{
					if ((it->type == GameObject::GAMEOBJECT_TYPE::GO_ENEMY || it->type == GameObject::GAMEOBJECT_TYPE::GO_ASTEROID) 
						&& it->active)
					{
						EnemyLockedOn = it;
						go->dir = (-go->pos + EnemyLockedOn->pos).Normalized();
						go->vel = go->dir * BULLET_SPEED * 0.5f;
						break;
					}
				}

				if (EnemyLockedOn == NULL)//if after checking still no lock
				{
					go->dir = m_ship->dir;
					go->vel = go->dir * (float)BULLET_SPEED * 0.5f;
				}
			}
			else//If alr got locked enemy
			{
				go->dir = (-go->pos + EnemyLockedOn->pos).Normalized();
				go->vel = go->dir * BULLET_SPEED * 0.5f;
			}
			++NumOfMissiles;

			isLMBpressed = true;
		}
	}
	else if (!Application::IsMousePressed(0) && isLMBpressed)
		isLMBpressed = false;
}

void SceneAsteroid::mouseControl()
{

	//Mouse Section
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}
}

void SceneAsteroid::initShip()
{
	//Exercise 2c: Construct m_ship, set active, type, scale and pos
	m_ship = NULL;
	m_ship = new GameObject(GameObject::GAMEOBJECT_TYPE::GO_SHIP);
	m_ship->scale.Set(1, 1, 1);
	m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f);
	m_ship->active = true;
	NumOfBullets = 0;
	NumOfMissiles = 0;

	m_torque.Set(0, 0, 1);
	m_ship->momentOfInertia = 1.f;
	m_ship->angularVelocity = 0.f;
	m_ship->dir.Set(0, 1, 0);


	m_lives = 100;
	m_score = 0;
}

void SceneAsteroid::updateShip(double dt)
{
	//Exercise 7: Update ship's velocity based on m_force
	//if ((m_ship->vel + (m_force * (1.f / m_ship->mass)) * (float)dt * m_speed).LengthSquared() < MAX_SPEED * MAX_SPEED)
	m_ship->vel = m_ship->vel + (m_force * (1.f / m_ship->mass)) * (float)dt * m_speed;

	if (m_ship->vel.Length() > MAX_SPEED)
	{
		m_ship->vel.Normalize();
		m_ship->vel *= MAX_SPEED;
	}


	m_ship->pos += m_ship->vel * m_speed * (float)dt;
	//m_torque * (1.f / m_ship->momentOfInertia);
	m_ship->angularVelocity += m_torque.z * (1.f / m_ship->momentOfInertia) * (float)dt;
	//m_ship->dir = m_ship->angularVelocity * (float)dt;
	//rotateAngle += m_ship->angularVelocity * (float)dt;

	//rotateAbout = m_torque;

	//Mtx44 rotation;
	//rotation.SetToRotation(Math::RadianToDegree(m_ship->angularVelocity * (float)(dt)), 0, 0, 1);
	//m_ship->dir = rotation * m_ship->dir;

	//faster
	float theta = m_ship->angularVelocity * dt * m_speed;
	m_ship->dir.Set(m_ship->dir.x * cos(theta) - m_ship->dir.y * sin(theta),
	m_ship->dir.x * sin(theta) + m_ship->dir.y * cos(theta));

	m_force.SetZero();
	m_torque.SetZero();


	//try {
	//	rotateAngle = Math::RadianToDegree(acos(Vector3(0, 1, 0).Dot(m_ship->vel.Normalized())));
	//}
	//catch (DivideByZero) {
	//	rotateAngle = Math::RadianToDegree(acos(Vector3(0, 1, 0).Dot(Vector3(0,1,0))));
	//}
	//
	//try {
	//	rotateAbout = Vector3(0, 1, 0).Cross(m_ship->vel.Normalized()).Normalized();
	//}
	//catch (DivideByZero) {
	//	rotateAbout = Vector3(0, 0, 1);
	//}


	//Exercise 9: wrap ship position if it leaves screen
	m_ship->pos.x = Math::Wrap(m_ship->pos.x, 0.0f - m_ship->scale.x, m_worldWidth + m_ship->scale.x);
	m_ship->pos.y = Math::Wrap(m_ship->pos.y, 0.0f - m_ship->scale.y, m_worldHeight + m_ship->scale.y);

}

void SceneAsteroid::updateAsteroid(GameObject* go, double dt)
{
	if ((go->pos - m_ship->pos).LengthSquared() < (m_ship->scale.x + go->scale.x) * (m_ship->scale.x + go->scale.x))
	{
		//COLLIDED
		m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f);
		m_ship->vel.SetZero();
		--m_lives;
		go->active = false;

		if (m_lives == 0)
		{
			m_lives = 100;
		}
	}

	//Exercise 13: asteroids should wrap around the screen like the ship
	go->pos += go->vel * (float)dt * m_speed;
	go->pos.x = Math::Wrap(go->pos.x, 0.0f - go->scale.x, m_worldWidth + go->scale.x);
	go->pos.y = Math::Wrap(go->pos.y, 0.0f - go->scale.y, m_worldHeight + go->scale.y);
}
void SceneAsteroid::updateShipBullet(GameObject* go, double dt)
{
	go->pos += go->vel * (float)dt * m_speed;
	if (go->pos.x < 0 - go->scale.x || go->pos.x > m_worldWidth + go->scale.x || go->pos.y < 0 - go->scale.y || go->pos.y > m_worldHeight + go->scale.y)
	{
		--NumOfBullets;
		go->active = false;
	}

	//Exercise 18: collision check between GO_BULLET and GO_ASTEROID
	for (auto it : m_goList)
	{
		if (it->type != GameObject::GAMEOBJECT_TYPE::GO_ASTEROID && it->type != GameObject::GAMEOBJECT_TYPE::GO_ENEMY)
			continue;
		if ((go->pos - it->pos).LengthSquared() < (go->scale.x + it->scale.x) * (go->scale.x + it->scale.x) && it->active)
		{
			//collided
			go->active = false;
			it->active = false;
			m_score += 2;
			--NumOfBullets;
			break;
		}
	}
}
void SceneAsteroid::updateShipMissile(GameObject* go, double dt) {

	if (EnemyLockedOn != NULL)
	{
		if (EnemyLockedOn->active == false)
			EnemyLockedOn = NULL;
		else
			go->dir = (-go->pos + EnemyLockedOn->pos).Normalized();
	}
	else
	{
		//Attempt to lock on
		for (auto it : m_goList)
		{
			if ((it->type == GameObject::GAMEOBJECT_TYPE::GO_ENEMY || it->type == GameObject::GAMEOBJECT_TYPE::GO_ASTEROID)
				&& it->active == true)
			{
				EnemyLockedOn = it;
				go->dir = (-go->pos + EnemyLockedOn->pos).Normalized();
				break;
			}
		}
	}
	go->vel = go->dir * BULLET_SPEED * 0.5f;
	go->pos += go->vel * (float)dt * m_speed;
	if (go->pos.x < 0 - go->scale.x || go->pos.x > m_worldWidth + go->scale.x || go->pos.y < 0 - go->scale.y || go->pos.y > m_worldHeight + go->scale.y)
	{
		--NumOfMissiles;
		go->active = false;
	}

	//Exercise 18: collision check between MISSILE and ASTEROID
	for (auto it : m_goList)
	{
		if ((it->type != GameObject::GAMEOBJECT_TYPE::GO_ASTEROID && it->type != GameObject::GAMEOBJECT_TYPE::GO_ENEMY) || it->active == false)
			continue;
		if ((go->pos - it->pos).LengthSquared() < (go->scale.x + it->scale.x) * (go->scale.x + it->scale.x) && it->active)
		{
			//collided
			go->active = false;
			it->active = false;
			m_score += 1;
			--NumOfMissiles;
			EnemyLockedOn = NULL;
			break;
		}
	}
}

void SceneAsteroid::updateEnemyShip(GameObject* go, double dt)
{
	go->pos += go->vel * (float)dt * m_speed;
	if ((go->pos - m_ship->pos).LengthSquared() < (go->scale.x + m_ship->scale.x) * (go->scale.x + m_ship->scale.x))
	{
		//if ship collide with enemy
		--m_lives;
		go->active = false;
	}
	else
	{


		go->dir = (-go->pos + m_ship->pos).Normalized();
		go->vel = go->dir * 5;
		if (allShoot)
		{
			GameObject* bullet = FetchGO();
			bullet->active = true;
			bullet->dir = go->dir;
			bullet->pos = go->pos;
			bullet->type = GameObject::GAMEOBJECT_TYPE::GO_ENEMY_BULLET;
			bullet->scale.Set(0.2f, 0.2f, 0.2f);
			bullet->vel = bullet->dir * BULLET_SPEED;
		}
	}
}
void SceneAsteroid::updateEnemyBullet(GameObject* go, double dt)
{
	go->pos += go->vel * (float)dt * m_speed;
	if (go->pos.x < 0 - go->scale.x || go->pos.x > m_worldWidth + go->scale.x || go->pos.y < 0 - go->scale.y || go->pos.y > m_worldHeight + go->scale.y)
	{
		go->active = false;
	}

	if ((go->pos - m_ship->pos).LengthSquared() < (go->scale.x + m_ship->scale.x) * (go->scale.x + m_ship->scale.x))
	{
		go->active = false;
		--m_lives;
	}
}

void SceneAsteroid::renderTexts()
{
	//On screen text
	//Exercise 5a: Render m_lives, m_score
	//Exercise 5b: Render position, velocity & mass of ship
	std::ostringstream ss7;
	ss7.precision(3);
	ss7 << "mass: " << m_ship->mass;
	RenderTextOnScreen(meshList[GEO_TEXT], ss7.str(), Color(0, 1, 0), 3, 0, 21);

	std::ostringstream ss6;
	ss6.precision(3);
	ss6 << "vel: " << m_ship->vel;
	RenderTextOnScreen(meshList[GEO_TEXT], ss6.str(), Color(0, 1, 0), 3, 0, 18);

	std::ostringstream ss5;
	ss5.precision(3);
	ss5 << "pos: " << m_ship->pos;
	RenderTextOnScreen(meshList[GEO_TEXT], ss5.str(), Color(0, 1, 0), 3, 0, 15);

	std::ostringstream ss4;
	ss4.precision(3);
	ss4 << "Score: " << m_score;
	RenderTextOnScreen(meshList[GEO_TEXT], ss4.str(), Color(0, 1, 0), 3, 0, 12);

	std::ostringstream ss3;
	ss3.precision(3);
	ss3 << "Lives: " << m_lives;
	RenderTextOnScreen(meshList[GEO_TEXT], ss3.str(), Color(0, 1, 0), 3, 0, 9);

	std::ostringstream ss2;
	ss2.precision(3);
	ss2 << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 3, 0, 6);

	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);

	RenderTextOnScreen(meshList[GEO_TEXT], "Asteroid", Color(0, 1, 0), 3, 0, 0);
}