#include "SceneKinematics.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

#include <algorithm>

SceneKinematics::SceneKinematics()
{
}

SceneKinematics::~SceneKinematics()
{
}

void SceneKinematics::Init()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	
	glEnable(GL_CULL_FACE);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders( "Shader//comg.vertexshader", "Shader//comg.fragmentshader" );
	
	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	
	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);
	
	glUniform1i(m_parameters[U_NUMLIGHTS], 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1), 2.f);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	bLightEnabled = false;

	//Physics code here
	m_speed = 1.f;
	
	m_gravity.Set(0, -9.8f, 0); //init gravity as 9.8ms-2 downwards
	Math::InitRNG();

	m_ghost = new GameObject(GameObject::GO_BALL);

	//Exercise 1: construct 10 GameObject with type GO_BALL and add into m_goList
	for (size_t i = 0; i < 20; ++i)
		m_goList.push_back(new GameObject(GameObject::GO_BALL));

	m_timeGO = NULL;
	
}

void SceneKinematics::Update(double dt)
{
	//Keyboard Section
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	static bool bButtonSpdUP = false;
	static bool bButtomSpdDwn = false;

	if (Application::IsKeyPressed(VK_OEM_PLUS) && !bButtonSpdUP)
	{
		//Exercise 6: adjust simulation speed
		bButtonSpdUP = true;
		m_speed *= 2.0f;
	}
	else if (bButtonSpdUP && !Application::IsKeyPressed(VK_OEM_PLUS))
	{
		bButtonSpdUP = false;
	}
	if(Application::IsKeyPressed(VK_OEM_MINUS) && !bButtomSpdDwn)
	{
		//Exercise 6: adjust simulation speed
		bButtomSpdDwn = true;
		m_speed = Math::Max(m_speed -= 0.1f, 0.1f);
	}
	else if (bButtomSpdDwn && !Application::IsKeyPressed(VK_OEM_MINUS))
	{
		bButtomSpdDwn = false;
	}
	if(Application::IsKeyPressed('C'))
	{
		//Exercise 9: clear screen
		for (auto it : m_goList)
			it->active = false;
	}
	static bool bisSpacePressed = false;
	if (Application::IsKeyPressed(' ') && !bisSpacePressed)
	{
		bisSpacePressed = true;
		//Exercise 9: spawn balls
		GameObject* it = getInactiveGObj();
		if (it)
		{
			it->active = true;
			it->type = GameObject::GAMEOBJECT_TYPE::GO_BALL;
			it->pos.Set(Math::RandFloatMinMax(0.2f * m_worldWidth, 0.8f * m_worldWidth), Math::RandFloatMinMax(0.2f * m_worldHeight, 0.8f * m_worldHeight), 0);
			it->scale.Set(1, 1, 1);
			it->vel.Set(Math::RandFloatMinMax(-30.f, 30.f), Math::RandFloatMinMax(0.f, 30.f), 0);
			//it->mass = Math::RandFloatMinMax();

			m_timeGO = it;
		}
	}
	else if (!Application::IsKeyPressed(' ') && bisSpacePressed)
		bisSpacePressed = false;

	static bool isVPressed = false;
	if (Application::IsKeyPressed('V') && !isVPressed)
	{
		//Exercise 9: spawn obstacles
		isVPressed = true;
		//Exercise 9: spawn balls
		GameObject* it = getInactiveGObj();
		if (it)
		{
			it->active = true;
			it->type = GameObject::GAMEOBJECT_TYPE::GO_CUBE;
			it->pos.Set(Math::RandFloatMinMax(0.05f * m_worldWidth, 0.95f * m_worldWidth), Math::RandFloatMinMax(0.05f * m_worldHeight, 0.95f * m_worldHeight), 0);
			it->scale.Set(2, 2, 2);
			it->vel.Set(0, 0, 0);
			//it->mass = Math::RandFloatMinMax();
		}
	}
	else if (!Application::IsKeyPressed('V') && isVPressed)
		isVPressed = false;

	//Mouse Section
	static bool bLButtonState = false;
	//Exercise 10: ghost code here
	if(!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();

		//Exercise 10: spawn ghost ball
		if(!m_ghost->active)
		{
			//if ghostball is previously not active(out of window/not flying), set it to active and usable
			m_ghost->active = true;
			m_ghost->type = GameObject::GAMEOBJECT_TYPE::GO_BALL;
			m_ghost->pos.Set((float)x / (Application::GetWindowWidth() / m_worldWidth), (Application::GetWindowHeight() - (float)y) / (Application::GetWindowHeight() / m_worldHeight), 0);
			m_ghost->scale.Set(1, 1, 1);
			m_ghost->vel.Set(0, 0, 0);
		}
	}
	else if(bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
		
		//Exercise 4: spawn ball

		//if gameobj is not active, set active
		GameObject* it = getInactiveGObj();

		//Get mouse pos
		double xpos, ypos;
		Application::GetCursorPos(&xpos, &ypos);

		if (it)
		{
			it->active = true;
			it->type = GameObject::GAMEOBJECT_TYPE::GO_BALL;

			//set pos
			it->pos.Set(xpos / (Application::GetWindowWidth() / m_worldWidth), (Application::GetWindowHeight() - ypos) / (Application::GetWindowHeight() / m_worldHeight), 0);
			it->vel.Set(20, 20, 0);
			it->scale.Set(1, 1, 1);

			m_timeGO = it;
		}
				
		//Exercise 10: replace Exercise 4 code and use ghost to determine ball velocity
		if (m_ghost->active)
		{
			int vx, vy;
			vx = m_ghost->pos.x - (xpos / (Application::GetWindowWidth() / m_worldWidth));
			vy = m_ghost->pos.y - ((Application::GetWindowHeight() - ypos) / (Application::GetWindowHeight() / m_worldHeight));
			m_ghost->vel.Set(vx, vy, 0);

			m_timeGO = m_ghost;
		}
		
		if (m_timeGO)
		{
			if (m_timeGO->active)
			{
				//reset 
				m_timeTaken1 = 0.f;
				m_timeTaken2 = 0.f;
				m_heightMax = 0.f;

				//Exercise 11: kinematics equation
				//v = u + a * t
				//t = (v - u ) / a

				//v * v = u * u + 2 * a * s
				//s = - (u * u) / (2 * a)

				//s = u * t + 0.5 * a * t * t
				//(0.5 * a) * t * t + (u) * t + (-s) = 0


				//i. Estimated time for ball to reach maximum height. Store in m_timeEstimated1
				//0 = m_timeGO->vel + m_gravity * t;	
				m_timeEstimated1 = -m_timeGO->vel.y / m_gravity.y;

				//ii. Estimated time for ball to reach window’s bottom, i.e. go­>pos.y <= 0. Store in m_timeEstimated2
				//just calculate for y
				float ydisplacement = -m_timeGO->pos.y;
				//-m_timeGO->pos.y = m_timeGO->vel.y * t + 0.5 * m_gravity.y * t * t;
				//Solve Quad Eqn
				float x1, x2;
				SolveQuadratic(m_gravity.y * 0.5, m_timeGO->vel.y, m_timeGO->pos.y, x1, x2);
				x1 = Math::Max(0.f, x1);
				x2 = Math::Max(0.f, x2);
				m_timeEstimated2 = ((x1 >= x2) ? (x1) : (x2));//Either one SHOULD be negative

				//iii. Estimated maximum height that the ball will reach. Store in m_heightEstimated
				//v = 0;
				//0 = m_timeGO->vel * m_timeGO->vel + 2 * m_gravity * s
				//(0 - (m_timeGO->vel * m_timeGO->vel)) / 2 * m_gravity = s;
				m_heightEstimated = (0.f - (m_timeGO->vel.y * m_timeGO->vel.y)) / (2.f * m_gravity.y);
				m_heightEstimated += m_timeGO->pos.y;

				//iv. Estimated horizontal distance that the ball will travel
				//vel.x is constant.
				//1st Assumption: Ball hits the bottom first and not the sides. So, a == 0, s == ut
				float m_horizontalDistEst = m_timeGO->vel.x * m_timeEstimated2;
				//2nd Assumption: Ball hits the sides first
				float checkingSide = ((m_timeGO->vel.x < 0) ? (0) : (m_worldWidth)); //Check if ball is going left or right. if left, check left wall, else check right wall.
				float m_horizontalDistEst2 = abs(-m_timeGO->pos.x + checkingSide);//x distance from ball to the side
				//3rd Assumption:: Ball hits the celling first
				//dist = m_timeGO->vel.y * t + 0.5*m_gravity.y*t*t;
				float distBalltoCelling = m_worldHeight - m_timeGO->pos.y;
				float t1 = 0;
				float t2 = 0;
				float tempTimeEst = 0;
				SolveQuadratic(m_gravity.y * 0.5, m_timeGO->vel.y, distBalltoCelling, t1, t2);
				t1 = Math::Max(0.f, t1);
				t2 = Math::Max(0.f, t2);
				if (t1 <= 0 && t2 != 0 || t1 != 0 && t2 <= 0)//if touch the celling once only
				{
					tempTimeEst = Math::Max(t1, t2);
				}
				else if (t1 == 0 && t2 == 0 || t1 < 0 && t2 < 0)//ball nvr touch celling or both roots are negative
				{
					tempTimeEst = FLT_MAX;//FLT_MAX
				}
				else // ball wouldve touched celling TWICE
				{
					tempTimeEst = Math::Min(t1, t2);
				}
				float m_horizontalDistEst3;
				if (tempTimeEst != FLT_MAX)
					m_horizontalDistEst3 = m_timeGO->vel.x * tempTimeEst;
				else
					m_horizontalDistEst3 = FLT_MAX;

				float FINAL_EST_HORIZONTAL_DIST = Math::Min(m_horizontalDistEst, Math::Min(m_horizontalDistEst2, m_horizontalDistEst3));

			}
		}
	}
	
	static bool bRButtonState = false;
	if(!bRButtonState && Application::IsMousePressed(1)) //RIGHT CLICK =====
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;

		//Exercise 7: spawn obstacles using GO_CUBE
		
		GameObject *it = getInactiveGObj();

		double xpos, ypos;
		Application::GetCursorPos(&xpos, &ypos);

		if (it)
		{
			it->active = true;
			it->type = GameObject::GAMEOBJECT_TYPE::GO_CUBE;

			it->pos.Set(xpos / (Application::GetWindowWidth() / m_worldWidth), (Application::GetWindowHeight() - ypos) / (Application::GetWindowHeight() / m_worldHeight), 0);
			it->scale.Set(2, 2, 2);
		}

	}
	else if(bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}

	//Physics Simulation Section
	fps = (float)(1.f / dt);

	bool updatedGhost = false;
	//Exercise 11: update kinematics information
	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end();)
	{
		GameObject *go;
		if (!updatedGhost) //update Ghost ball first
			go = m_ghost;
		else
			go = (GameObject *)*it;
		if(go->active)
		{
			if(go->type == GameObject::GO_BALL)
			{
				//Exercise 2: implement equation 1 & 2
				//v = u + at
				//s = 0.5 * (u + v) * t
				
				Vector3 u = go->vel;
				go->vel += (m_gravity * (float)dt * m_speed);
				go->pos += 0.5f * (u + go->vel) * (float)dt * m_speed;
				
				//go->vel += m_gravity * dt * m_speed;
				//go->pos += go->vel * dt * m_speed;

				//Exercise 12: replace Exercise 2 code and use average speed instead



				//DOING COLLISION CHECK HERE
				//Exercise 8: check collision with GO_CUBE
				for (auto itCUBE : m_goList)
				{
					if (itCUBE->type != GameObject::GAMEOBJECT_TYPE::GO_CUBE)
						continue;
					if (go == itCUBE)
						continue;
					if (itCUBE->active == false)
						continue;


					//if itCube type is CUBE
					Vector3 ballToCube(-go->pos.x + itCUBE->pos.x, -go->pos.y + itCUBE->pos.y, -go->pos.z + itCUBE->pos.z);

					Vector3 cubeMin(itCUBE->pos.x - itCUBE->scale.x, itCUBE->pos.y - itCUBE->scale.y, 0);//ignore Z
					Vector3 cubeMax(itCUBE->pos.x + itCUBE->scale.x, itCUBE->pos.y + itCUBE->scale.y, 0);

					Vector3 nearestPtOfBallToCube(go->pos.x + ballToCube.Normalized().x * (float)go->scale.x, go->pos.y + ballToCube.Normalized().y * (float)go->scale.y, 0);//ignore Z

					if (isPointInBox(nearestPtOfBallToCube, cubeMin, cubeMax))
					{
						go->active = false;
						itCUBE->active = false;
					}
				}
			}

			//Exercise 5: unspawn ball when outside window
			if (go->pos.x > m_worldWidth + go->scale.x || go->pos.x < 0 - go->scale.x
				|| go->pos.y < 0 - go->scale.y || go->pos.y > m_worldHeight + go->scale.x)
			{
				go->active = false;
			}
		}
		
		if (!updatedGhost)
		{
			updatedGhost = true;
		}
		else
		{
			++it;
		}
	}

	if (m_timeGO)
	{
		if (m_timeGO->active)
		{
			if (m_heightMax < m_timeGO->pos.y)
			{
				m_heightMax = m_timeGO->pos.y;
				m_timeTaken1 += (float)dt;
			}


			if (m_timeGO->pos.y > 0)
			{
				m_timeTaken2 += (float)dt;
			}
		}
		//else
		//{
		//	m_timeTaken1 = 0.f;
		//	m_timeTaken2 = 0.f;
		//	m_heightMax = 0.f;
		//}
	}
}

void SceneKinematics::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneKinematics::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneKinematics::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneKinematics::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_BALL:
		//Exercise 3: render a sphere with radius 1
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL], true);
		modelStack.PopMatrix();
		break;
	case GameObject::GO_CUBE:
		//Exercise 7: render a cube with length 2
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_CUBE], true);
		modelStack.PopMatrix();
		break;
	}
}

void SceneKinematics::Render()
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
	{
		RenderGO(m_ghost);
	}

	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);
	
	//Exercise 6: print simulation speed
	std::ostringstream ss1;
	ss1.precision(3);
	ss1 << "SPEED: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss1.str(), Color(0, 1, 0), 3, 0, 6);

	//Exercise 10: print m_ghost position and velocity information
	std::ostringstream ss2;
	ss2.precision(5);
	ss2 << "m_ghost pos: " << m_ghost->pos;
	RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 3, 0, 9);

	std::ostringstream ss3;
	ss3.precision(5);
	ss3 << "m_ghost vel: " << m_ghost->vel;
	RenderTextOnScreen(meshList[GEO_TEXT], ss3.str(), Color(0, 1, 0), 3, 0, 12);
	
	//Exercise 11: print kinematics information
	std::ostringstream ss4;
	ss4.precision(3);
	ss4 << "mTimeEst1: " << m_timeEstimated1;
	RenderTextOnScreen(meshList[GEO_TEXT], ss4.str(), Color(0, 1, 0), 3, 0, 15);

	std::ostringstream ss5;
	ss5.precision(3);
	ss5 << "mTimeEst2: " << m_timeEstimated2;
	RenderTextOnScreen(meshList[GEO_TEXT], ss5.str(), Color(0, 1, 0), 3, 0, 18);

	std::ostringstream ss6;
	ss6.precision(3);
	ss6 << "mHeightEst: " << m_heightEstimated;
	RenderTextOnScreen(meshList[GEO_TEXT], ss6.str(), Color(0, 1, 0), 3, 0, 21);

	std::ostringstream ss7;
	ss7.precision(3);
	ss7 << "mTimeTaken1: " << m_timeTaken1;
	RenderTextOnScreen(meshList[GEO_TEXT], ss7.str(), Color(0, 1, 0), 3, 0, 24);

	std::ostringstream ss8;
	ss8.precision(3);
	ss8 << "mTimeTaken2: " << m_timeTaken2;
	RenderTextOnScreen(meshList[GEO_TEXT], ss8.str(), Color(0, 1, 0), 3, 0, 27);

	std::ostringstream ss9;
	ss9.precision(3);
	ss9 << "mHeightMax: " << m_heightMax;
	RenderTextOnScreen(meshList[GEO_TEXT], ss9.str(), Color(0, 1, 0), 3, 0, 30);

	//Print the velocity and position of the last ball on screen
	if (m_timeGO)
	{
		std::ostringstream ss10;
		ss10.precision(3);
		ss10 << "timeGo vel: " << m_timeGO->vel;
		RenderTextOnScreen(meshList[GEO_TEXT], ss10.str(), Color(0, 1, 0), 3, 0, 33);

		std::ostringstream ss11;
		ss11.precision(3);
		ss11 << "timeGo pos: " << m_timeGO->pos;
		RenderTextOnScreen(meshList[GEO_TEXT], ss11.str(), Color(0, 1, 0), 3, 0, 36);
	}
	RenderTextOnScreen(meshList[GEO_TEXT], "Kinematics", Color(0, 1, 0), 3, 0, 0);
}

void SceneKinematics::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	
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

bool SceneKinematics::isPointInBox(Vector3 pt, Vector3 min, Vector3 max)
{
	return (pt.x >= min.x &&
		pt.x <= max.x &&
		pt.y >= min.y &&
		pt.y <= max.y &&
		pt.z >= min.z &&
		pt.z <= max.z );
}
GameObject* SceneKinematics::getInactiveGObj()
{
	for (auto it : m_goList)
	{
		if (!it->active)
		{
			return it;
		}
	}
	return NULL;
}

void SceneKinematics::SolveQuadratic(float a, float b, float c, float& x1, float& x2)
{
	float determinant = b*b - 4*a*c;
	if (determinant > 0) 
	{
		x1 = (-b + sqrt(determinant)) / (2*a);
		x2 = (-b - sqrt(determinant)) / (2*a);
	}
	else if (determinant == 0) 
	{
		x1 = (-b + sqrt(determinant)) / (2*a);
		x2 = 0;
	}
	else
	{
		x1 = x2 = 0;
	}
}

