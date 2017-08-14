#include "Player.h"
#include "GlobalVariableManager.h"
#include "Camera.h"

#include "RenderHelper.h"
#include "Graphics.h"
#include "Mtx44.h"

#include "Weapon.h"
#include "MG.h"
#include "HomingMissile.h"

#include "Enemy.h"
#include "Planet.h"
#include "LoadTGA.h"

#include <string>

#define PLAYER_DEFAULT_DIR Vector3(0,1,0)
std::string sss;


Player::Player()
{
	this->mesh = EntityBase::getInstance()->getEntity("SHIP");
	this->pos.Set(GV_ worldWidth * 0.5f, GV_ worldHeight * 0.5f);
	this->active = true;
	this->dir.Set(0, 1, 0);
	this->scale.Set(1, 2, 1);
	this->up.Set(0, 0, 1);
	this->right.Set(1, 0, 0);
	this->mass = 5.f;
	hp = MAXHP; 
	moveSpd = 1.0;


	torque.Set(0, 0, 1);
	force.Set(0, 0, 0);

	angularVelocity = 0.f;

	// i use tetrahedron calculation for inertia (m)(s^2) / 20 //what is side length
	//i assume it is the average legth from CG to the edge for now. if scale is (1,2), then side length will be sqrt 2
	momentOfInertia = (this->mass * sqrt(this->scale.x * this->scale.x + this->scale.y + this->scale.y)) / 20.f;

	for (auto &eng : engines) {
		eng.setOwner(this);
		eng.active = false;
	}
	engines[0].pos.Set(0, -1, 0);//relative to ship pos
	engines[0].dir.Set(0, 1, 0);
	engines[1].pos.Set(0, 1, 0);//relative to ship pos
	engines[1].dir.Set(0, -1, 0);
	engines[2].pos.Set(1, 0, 0);//relative to ship pos //right, so turns left
	engines[2].dir.Set(0, 1, 0);
	engines[3].pos.Set(-1, 0, 0);//relative to ship pos //left
	engines[3].dir.Set(0, 1, 0);

	cam = nullptr;
	weap = new MachineGun(GlobalVariables::ENEMY);
	weapHoming = new HomingMissile();
	weap->fireRatePerSec = 10;
	weap->dmg = DEFAULTWeapDmg;
	weapHoming->dmg = 10;

	collision.collisionType = Collision::CollisionType::AABB;
	collision.mid = this->pos;
	collision.min.Set(-this->scale.x * 0.5f, -this->scale.y * 0.5f);
	collision.max.Set(this->scale.x * 0.5f, this->scale.y * 0.5f);

	engineBoost = false;
	boostFuel = boostCap;
	MAXSPD = defaultMAXSPD;
	rechargeRateMultiplierPerSec = DEFAULTRRMPS;


	dmgimmune = false;
	dmgreduction = 0.9f;
	incdmg = false;

	powerBulletPowerUp = MeshBuilder::GenerateQuad("", Color(1, 1, 1), 1);
	powerBulletPowerUp->textureID = LoadTGA("Image//powerbullet.tga");
}

Player::~Player()
{
	if (weap)
		delete weap;
	weap = nullptr;
	if (weapHoming)
		delete weapHoming;
	weapHoming = nullptr;
	if (powerBulletPowerUp)
		delete powerBulletPowerUp;
	powerBulletPowerUp = nullptr;

	//if (instance)
	//	delete instance;
	//instance = nullptr;
}

Player* Player::getInstance()
{
	if (instance == nullptr)
		instance = new Player();
	return instance;
}

void Player::update(double dt)
{
	updateCollisionBox();
	updateCheckPowerUp(dt);
	inputMovement(dt);//add force/torque from playerinputs
	updateBooster(dt);
	for (auto &eng : engines) {//update engine force
		eng.update(dt);
	}
	updateKinematics(dt);
	updateCamPos();
	updateWeapon(dt);


}

void Player::render() 
{
	if (this->active)
	{
		//Mtx44 transformation(this->right, this->up, this->dir, this->pos);

		Graphics::getInstance()->modelStack.PushMatrix();
		//Graphics::getInstance()->modelStack.LoadMatrix(transformation);
		Graphics::getInstance()->modelStack.Translate(this->pos.x, this->pos.y, this->pos.z);
		Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)) - 90.f, 0, 0, 1);
		Graphics::getInstance()->modelStack.Scale(this->scale.x, this->scale.y, this->scale.z);
		RenderHelper::RenderMesh(this->getMesh(), false);
		Graphics::getInstance()->modelStack.PopMatrix();
	}
	if (incdmg)
	{
		for each (auto a in weap->ammo)
		{
			if (a->active)
			{
				Graphics::getInstance()->modelStack.PushMatrix();
				//Graphics::getInstance()->modelStack.LoadMatrix(transformation);
				Graphics::getInstance()->modelStack.Translate(a->pos.x, a->pos.y, a->pos.z);
				//Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)) - 90.f, 0, 0, 1);
				Graphics::getInstance()->modelStack.Scale(a->scale.x * 5.f, a->scale.y * 5.f, 1);
				RenderHelper::RenderMesh(powerBulletPowerUp, false);
				Graphics::getInstance()->modelStack.PopMatrix();
			}

		}
	}
	weap->weaponRender();
	weapHoming->weaponRender();

	HpBar* temphp = GlobalVariables::get()->hpbar;
	float hpbarScaleY = 5;
	temphp->scale.Set(25, hpbarScaleY, 1);

	Vector3 hppos(-GlobalVariables::get()->worldWidth * 0.5f + this->pos.x + 0.75f * temphp->scale.x,
		GlobalVariables::get()->worldHeight * 0.5f + this->pos.y - 1.f * temphp->scale.y);

	temphp->pos = hppos;
	temphp->render(this->hp / this->MAXHP);

	BoostBar* tempbb = GlobalVariables::get()->boostbar;
	tempbb->scale.Set(20, 1, 1);
	tempbb->pos = hppos;
	tempbb->pos.y -= ((hpbarScaleY * 0.5f) + (1.5f));//this->scale.y * 0.5f
	tempbb->render(this->boostFuel / this->boostCap);


	RenderHelper::RenderTextOnScreen(GlobalVariables::get()->text, sss, Color(1, 1, 1), 2, 0, 2);
	sss = "";
	sss += "Vel: [ " + std::to_string(this->vel.x) + ", " +
		std::to_string(this->vel.y) + " ]";
	RenderHelper::RenderTextOnScreen(GlobalVariables::get()->text, sss, Color(1, 1, 1), 2, 0, 4);
}

void Player::inputMovement(double dt)
{
	const float FORCE = 100;
	if (Application::IsKeyPressed('W')) {
		//force += this->dir * FORCE;
		engines[0].active = true;
	}
	else
	{
		engines[0].active = false;
	}
	if (Application::IsKeyPressed('S')) {
		engines[1].active = true;
	}
	else
	{
		engines[1].active = false;
	}
	if (Application::IsKeyPressed('A')) {
		//force += this->dir * 5.f;

		////m_torque = (m_ship->dir.Cross(Vector3(0, 0, 1)).Normalized() - m_ship->dir).Cross(m_ship->dir * 5);//right engine
		//torque = (this->dir.Cross(Vector3(0, 0, 1)).Normalized() - this->dir).Cross(this->dir * 5);//right engine
		engines[2].active = true;
	}
	else
	{
		engines[2].active = false;
	}
	
	if (Application::IsKeyPressed('D')) {
		//force += this->dir * 5.f;
		//torque = (this->dir.Cross(Vector3(0, 0, -1)).Normalized() - this->dir).Cross(this->dir * 5);//left engine
		engines[3].active = true;
	}
	else
	{
		engines[3].active = false;
	}

	if (Application::IsKeyPressed(VK_SPACE)) {
		engineBoost = true;
	}
	else
		engineBoost = false;

	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 v(x - (w >> 1), (h - y) - (h >> 1));
	
	//ROTATION SPD HERE
	static float rotationSpd = 3.5f;
	Vector3 daNormal;
	try {
		v.Normalize();
		daNormal = this->dir.Cross(v).Normalized();
	}
	catch (DivideByZero) {
		//if divide by zero then i use previous dir
		v = this->dir;
		daNormal.Set(0, 0, 1);
	}
	float angleBtw = Math::RadianToDegree(acos(this->dir.Dot(v)));
	Mtx44 rotatedadir;
	rotatedadir.SetToRotation(Math::Min(angleBtw, rotationSpd),
		daNormal.x, daNormal.y, daNormal.z);
	this->dir = rotatedadir * this->dir;
	//this->dir = v;
	this->dir.Normalize();

	if (Application::IsMousePressed(0)) {
		weap->isAttack = true;
	}
	else {
		weap->isAttack = false;
	}

	if (Application::IsMousePressed(1)) {
		weapHoming->isAttack = true;
	}
	else {
		weapHoming->isAttack = false;
	}
}

void Player::updateBooster(double dt)
{
	//Clearing the floating point error
	if (abs(DEFAULTRRMPS - rechargeRateMultiplierPerSec) < Math::EPSILON)
		rechargeRateMultiplierPerSec = DEFAULTRRMPS;


	if (!engineBoost)//if bo boost
	{
		for (auto &eng : engines) {
			eng.boosted = false;
		}
		//recharge
		if (boostFuel < boostCap)
		{
			boostFuel += Math::Min((float)dt * rechargeRateMultiplierPerSec, boostCap - boostFuel);
		}

		MAXSPD = defaultMAXSPD;
		
		//and zao
		return;
	}

	if (boostFuel <= 0.0f)//if boost too low, might as well dont boost
	{
		for (auto &eng : engines) {
			eng.boosted = false;
		}
		MAXSPD = defaultMAXSPD;
		return;
	}

	boostFuel -= (float)dt;

	float boostpower = 1.f;
	for (auto &eng : engines) {
		eng.boosted = true;
		boostpower = eng.boostPowerMultiplier;
	}

	MAXSPD = defaultMAXSPD * boostpower;
}

void Player::updateKinematics(double dt)
{
	if (Application::IsKeyPressed('Z'))
		this->vel.SetZero();

	for (auto it : *(GlobalVariables::get()->planetPointer))
	{
		if (it->active)
		{
			Vector3 meTohim;
			meTohim = (-this->pos + it->pos);
			if (meTohim.LengthSquared() < it->gravitationalRadius * it->gravitationalRadius)
			{
				meTohim.Normalize();
				meTohim *= it->updateGravitationalForce(this->pos, this->mass);
				this->force += meTohim;
			}

		}
	}


	sss = "Force: " + std::to_string(force.x) + ", " + std::to_string(force.y) + ", " + std::to_string(force.z);


	this->vel = this->vel + (this->force * (1.f / this->mass)) * (float)dt;

	
	if (this->vel.LengthSquared() > MAXSPD * MAXSPD)
	{
		float currentSpd = this->vel.Length();
		const float deceleration = (1.f * currentSpd * currentSpd) / mass;
		float difference = currentSpd - MAXSPD;

		currentSpd -= Math::Min(deceleration * (float)dt, difference * (float)dt);
		this->vel.Normalize();
		this->vel *= currentSpd;
	}
	if (this->vel.LengthSquared() > forcedMAXSPD * forcedMAXSPD)
	{
		this->vel.Normalize();
		this->vel *= forcedMAXSPD;
	}


	this->pos += this->vel * (float)dt;
	//m_torque * (1.f / m_ship->momentOfInertia);
	this->angularVelocity += torque.z * (1.f / this->momentOfInertia) * (float)dt;
	//m_ship->dir = m_ship->angularVelocity * (float)dt;
	//rotateAngle += m_ship->angularVelocity * (float)dt;

	//rotateAbout = m_torque;

	//Mtx44 rotation;
	//rotation.SetToRotation(Math::RadianToDegree(m_ship->angularVelocity * (float)(dt)), 0, 0, 1);
	//m_ship->dir = rotation * m_ship->dir;

	//faster
	float theta = this->angularVelocity * (float)dt;
	this->dir.Set(this->dir.x * cos(theta) - this->dir.y * sin(theta),
		this->dir.x * sin(theta) + this->dir.y * cos(theta));

	force.SetZero();
	torque.SetZero();

	//Exercise 9: wrap ship position if it leaves screen
	//this->pos.x = Math::Wrap(m_ship->pos.x, 0.0f - m_ship->scale.x, m_worldWidth + m_ship->scale.x);
	//this->pos.y = Math::Wrap(m_ship->pos.y, 0.0f - m_ship->scale.y, m_worldHeight + m_ship->scale.y);



	this->right = this->dir.Cross(this->up);

	this->rotateAngle = Math::RadianToDegree(atan2(PLAYER_DEFAULT_DIR.y, PLAYER_DEFAULT_DIR.x) - atan2(this->dir.y, -this->dir.x));
	//if (this->dir.x > 0)
	//	rotateAngle = 360 - rotateAngle;
}


void Player::getHit(float dmg)
{
	float tempReduction = dmgreduction;
	if (dmgimmune == false)
		tempReduction = 0.f;
	hp -= (dmg * (1.f - tempReduction));
}


//CAMERA FOLLOW PLAYER CODE ========================
void Player::attachCamera(Camera* cam) {
	this->cam = cam;
}
inline void Player::updateCamPos() {
	if (!cam)
		return;
	this->cam->position.x = this->pos.x;
	this->cam->position.y = this->pos.y;

	this->cam->target = this->cam->position + Vector3(0, 0, -1);
	this->cam->up.Set(0, 1, 0);

	GlobalVariables::get()->PlayableBox.mid = this->cam->position;
	GlobalVariables::get()->PlayableBox.mid.z = 0;//Very important for collision check
	//this->cam->position.x += 1;
	//this->cam->position.x += GlobalVariables::get()->worldWidth * 0.5f;
	//this->cam->position.y += GlobalVariables::get()->worldHeight * 0.5f;
}

void Player::updateCollisionBox() {
	this->collision.mid = this->pos;
}

void Player::updateWeapon(double dt) {
	//UPDATE POSITION AND DIR OF WEAP
	weap->pos = this->pos;
	weap->dir = this->dir;

	weapHoming->pos = this->pos;
	weapHoming->dir = this->dir;


	weap->weaponUpdate(dt);
	weapHoming->weaponUpdate(dt);
	for (auto it : weap->ammo)
	{
		if (it->active)
		{
			for (auto &e : *(GlobalVariables::get()->enemies))
			{
				if (e->active)
				{
					if (it->collision.isCollide(e->collision)) {
						e->getHit(weap->getDmg());
						it->active = false;

						//GlobalVariables::get()->pScore += 5;
						break;
					}
				}

			}
			

			for (auto &a : AsteroidManager::getinstance()->asteroids) {
				if (a->active) {
					if (it->collision.isCollide(a->collision)) {
						a->getHit(weap->getDmg());
						it->active = false;

						//GlobalVariables::get()->pScore += 1;
						break;
					}
				}
			}


		}
		
	}

	//LOGICING HOMING MISSILE
	{
		//SETTING NEAREST ENEMIES
		std::vector<Enemy*>nearest;
		for (auto &e : *(GlobalVariables::get()->enemies))
		{
			if (e->active)
			{
				int index = 0;
				if (nearest.size() == 0)
					nearest.push_back(e);
				else {
					bool insertliao = false;
					for (std::vector<Enemy*>::iterator it = nearest.begin(); it != nearest.end();) 
					{
						if ((-this->pos + e->pos).LengthSquared() < (-this->pos + (*it)->pos).LengthSquared())
						{
							nearest.insert(nearest.begin() + index, (e));
							insertliao = true;
							break;
						}
						else
						{
							++it;
							++index;
						}
					}
					if (!insertliao)
						nearest.push_back(e);
				}


			}

		}


		for (auto it : weapHoming->ammo) {
			if (it->active)
			{
				Missile* temp = dynamic_cast<Missile*>(it);
				
				for (auto e : nearest)
				{
					if (temp->isLockedOn == false)
					{
						temp->setLockedOn(e);
						temp->updateLockedPos();
					}
					temp->updateLockedPos();
					if (temp->collision.isCollide(e->collision)) {
						e->getHit(weapHoming->getDmg());
						it->active = false;

						//GlobalVariables::get()->pScore += 2;
						break;
					}



				}
				for (auto a : AsteroidManager::getinstance()->asteroids)
				{
					if (a->active)
					{
						if (it->collision.isCollide(a->collision))
						{
							it->active = false;
							a->getHit(weapHoming->getDmg());

							//GlobalVariables::get()->pScore += 1;
							break;
						}
					}
				}
				
			}
		}


	}
}

void Player::updateCheckPowerUp(double dt)
{
	for each (std::pair < PowerUpManager::PowerUpTypes, std::vector<Collectibles*> > p in PowerUpManager::getInstance()->powerups)
	{
		for each (Collectibles* v in p.second)
		{
			if (v->active)
			{
				if (this->collision.isCollide(v->collision))
				{
					if (!v->checkStatus())//if not activated
					{
						v->setTaken();//take it!
					}
				}
			}

			if (v->checkStatus())//if is activated
			{
				//check whats the upgrade
				//better way would be calling a higher level function which determines what player receives when
				//taken a collectible
				if (p.first == PowerUpManager::PowerUpTypes::HPUP)
				{


					if (!v->checkValidation())//if deactivation is activated
					{

					}
					else
					{
						this->getHit(-(0.75f * MAXHP * (float)dt));
						v->incElapsed((float)dt);
					}
				}
				else if (p.first == PowerUpManager::PowerUpTypes::BOOSTREGEN)
				{
					//stackable boost regen yay
					if (v->hasCalledBo() == false)
					{
						//if havent activate powerup effect
						this->rechargeRateMultiplierPerSec *= 2.f;
						v->setEffectDone();
					}


					if (!v->checkValidation())//if deactivation is activated
					{
						this->rechargeRateMultiplierPerSec *= 0.5f;
					}
					else
					{
						v->incElapsed((float)dt);
					}
				}
				else if (p.first == PowerUpManager::PowerUpTypes::INCDMG)
				{
					if (v->hasCalledBo() == false)
					{
						this->weap->dmg *= 2.f;
						v->setEffectDone();
					}


					if (!v->checkValidation())//if deactivation is activated
					{
						this->weap->dmg *= 0.5f;
						incdmg = false;
					}
					else
					{
						incdmg = true;
						v->incElapsed((float)dt);
					}
				}
				else if (p.first == PowerUpManager::PowerUpTypes::DMGIMM) 
				{


					if (!v->checkValidation())//if deactivation is activated
					{
						this->dmgimmune = false;
					}
					else
					{
						this->dmgimmune = true;
						v->incElapsed((float)dt);
					}
				}
			}
			//END POWERUP UPGRADE UPDATE
		}
		//END VECTOR ITERATION
	}
	//END MAP ITERATION

	//std::cout << "dmginc: " << incdmg << std::endl;
	//std::cout << "dmg imm: " << dmgimmune << std::endl;
}

void Player::reset() {
	hp = MAXHP;
	vel.SetZero();
	dir.Set(0, 1, 0);
	//weap->active = false;
	weap->isAttack = false;
	weapHoming->isAttack = false;
	incdmg = false;
	dmgimmune = false;
	boostFuel = boostCap;
	weap->dmg = DEFAULTWeapDmg;
	
}