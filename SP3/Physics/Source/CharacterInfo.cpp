//Characterinfo.cpp

#ifndef  CHARACTERINFO_H
#define CHARACTERINFO_H


#include "CharacterInfo.h"
#include "Mtx44.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Tower.h"
#include "TowerManager.h"
using namespace std;
using std::string;

Character::Character() : maxhealth(0),
health(0),
damage(0),
levels(0),
coins(0),
highscore(0)
{

}

Character::~Character()
{

}


void Character::Update(double dt)
{

	//Weapons Section Update--------------------------------//
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	static bool keypressed = false;
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);
	if (Application::GetInstance().IsMousePressed(1) && !keypressed)
	{
		weap.dir = -weap.pos + cursor_point_in_world_space;
		weap.dir.Normalize();
		weap.Discharge(weap.pos, weap.dir);
		keypressed = true;
	}
	else if (!Application::GetInstance().IsMousePressed(1) && keypressed)
	{
		keypressed = false;
	}
	weap.WeaponInfo::Update(dt);

	//------------Minon Section Update-------------------------------//

	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('1') && !dakeypressed)
		{
			MinionManager::GetInstance()->spawn_minion();
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('1') && dakeypressed)
		{
			dakeypressed = false;
		}
	}

	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('2') && !dakeypressed)
		{
			MinionManager::GetInstance()->spawn_minion(true, MinionInfo::MINION_TYPE::BASIC_RANGE);
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('2') && dakeypressed)
		{
			dakeypressed = false;
		}
	}

	//------------------------Spell Section Update--------------------------//
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


	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('7') && !dakeypressed)
		{
			SpellManager::GetInstance()->useFreezeSpell();
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('7') && dakeypressed)
		{
			dakeypressed = false;
		}
	}

	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('8') && !dakeypressed)
		{
			SpellManager::GetInstance()->useBlastSpell();
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('8') && dakeypressed)
		{
			dakeypressed = false;
		}
	}

	{
	static bool dakeypressed = false;
	if (Application::GetInstance().IsKeyPressed('5') && !dakeypressed)
	{
		consumables.UseBigRepairKit();
		dakeypressed = true;
	}
	else if (!Application::GetInstance().IsKeyPressed('5') && dakeypressed)
	{
		dakeypressed = false;
	}
}

}

void Character::Init()
{
	this->Load();
	weap.Init();
	weap.set_faction_side(Faction::FACTION_SIDE::PLAYER);
	weap.mesh = MeshList::GetInstance()->getMesh("CANNON");
	weap.scale.Set(5, 5, 5);
	weap.active = true;
	weap.pos.Set(7.5, 25);
	weap.set_damage(50);
	RenderManager::GetInstance()->attach_renderable(&weap, 1);
	consumables.attachCharacter(this);
	consumables.attachWallet(&this->wallet);
	charTower = TowerManager::GetInstance()->player;
	charTower->health = this->health;
	charTower->maxhealth = this->maxhealth;
}


void Character::changetowerhp(int hp)
{
	charTower->get_hit(-hp);
}

//---------------------Getters------------------------------------//
int Character::getlevel()
{
	return levels;
}


int Character::getmaxhealth()
{
	return maxhealth;
}

int Character::getcurrenthealth()
{
	return health;
}

int Character::getcurrentcoins()
{
	return coins;
}

int Character::getcurrenthighscore()
{
	return highscore;
}

int Character::getcurrentst()
{
	return soundtrack;
}

void Character::setlevel(int levels)
{
	this->levels = levels;
}

void Character::setmaxhealth(int maxhealth)
{
	this->maxhealth = maxhealth;
}

void Character::setcurrenthealth(int health)
{
	this->health = health;
}

void Character::setcurrentcoins(int coin)
{
	this->coins = coins;
}

void Character::setcurrenthighscore(int highscore)
{
	this->highscore = highscore;
}
void Character::setcurrentst(int soundtrack)
{
	this->soundtrack = soundtrack;
}

//Pos,Target,Up-------------------------//

Vector3 Character::GetPos(void) const
{
	return pos;
}

Vector3 Character::GetTarget(void) const
{
	return target;
}

Vector3 Character::GetUp(void) const
{
	return up;
}

Wallet & Character::getWallet()
{
	return wallet;
}

void Character::SetPos(const Vector3 & pos)
{
	this->pos = pos;
}

void Character::SetTarget(const Vector3 & target)
{
	this->target = target;
}

void Character::SetUp(const Vector3 & up)
{
	this->up = up;
}




//----------------------Tokens , load and save---------------------------//


// Load this class
bool Character::Load(const string saveFileName)
{
	int temp[9];

	ifstream myfile(saveFileName.c_str(), ios::in);
	if (myfile.is_open())
	{
		string line;
		while (getline(myfile, line))
		{
			cout << line << '\n';

			std::istringstream ss(line);
			std::string aToken = "";

			// Get the tag from the line
			while (std::getline(ss, aToken, '=')) {
				std::cout << aToken << endl;

				// Get the data from the line
				std::string theTag = aToken;
				std::getline(ss, aToken, '=');
				std::cout << aToken << endl;
				if (theTag == "maxhealth")
				{
					maxhealth = Token2Double(aToken);
				}
				else if (theTag == "health")
				{
					health = Token2Double(aToken);
				}
				else if (theTag == "damage")
				{
					damage = Token2Double(aToken);
				}
				else if (theTag == "level")
				{
					levels = Token2Double(aToken);
				}
				else if (theTag == "coin")
				{
					coins = Token2Double(aToken);
				}
				else if (theTag == "highscore")
				{
					highscore = Token2Double(aToken);
				}
				else if (theTag == "currentsound")
				{
					soundtrack = Token2Double(aToken);
				}
				else if (theTag == "mute")
				{
					mute = Token2Bool(aToken);
				}
				else if (theTag == "i_smallrepair")
				{
					temp[0] = Token2Double(aToken);
				}
				else if (theTag == "i_mediumrepair")
				{
					temp[1] = Token2Double(aToken);
				}
				else if (theTag == "i_bigrepair")
				{
					temp[2] = Token2Double(aToken);
				}
				else if (theTag == "i_greendrake")
				{
					temp[3] = Token2Double(aToken);
				}
				else if (theTag == "i_bluedrake")
				{
					temp[4] = Token2Double(aToken);
				}
				else if (theTag == "i_browndrake")
				{
					temp[5] = Token2Double(aToken);
				}
				else if (theTag == "i_blackdrake")
				{
					temp[6] = Token2Double(aToken);
				}
				else if (theTag == "i_weaplevel")
				{
					temp[7] = Token2Double(aToken);
				}
				else if (theTag == "i_towerlevel")
				{
					temp[8] = Token2Double(aToken);
				}
			}
		}

		//int 1 = Token2Double(aToken);
		wallet.wLoad(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8]);
		myfile.close();
	}
	else
	{
#if(_DEBUG == TRUE)
		cout << "PlayerInfo: Unable to load " << saveFileName.c_str() << endl;
#endif
		myfile.close();
		return false;
	}

	return true;
}

bool Character::Save(const string saveFileName)
{
	ofstream myfile;
	myfile.open(saveFileName.c_str(), ios::out | ios::ate);
	if (myfile.is_open())
	{
		myfile << "maxhealth=" << maxhealth << endl;
		myfile << "health=" << health << endl;
		myfile << "damage=" << damage << endl;
		myfile << "levels=" << levels << endl;
		myfile << "coin=" << coins << endl;
		myfile << "highscore=" << highscore << endl;
		myfile << "currentsound=" << soundtrack << endl;
		myfile << "muteornot=" << mute << endl;
		myfile << "i_smallrepair=" << wallet.getsmallrepair() << endl;
		myfile << "i_mediumrepair=" << wallet.getmediumrepair() << endl;
		myfile << "i_bigrepair=" << wallet.getbigrepair() << endl;
		myfile << "i_greendrake=" << wallet.getgreendrake() << endl;
		myfile << "i_bluedrake=" << wallet.getbluedrake() << endl;
		myfile << "i_browndrake=" << wallet.getbrowndrake() << endl;
		myfile << "i_blackdrake=" << wallet.getblackdrake() << endl;
		myfile << "i_weaplevel=" << wallet.getweaplevel() << endl;
		myfile << "i_towerlevel=" << wallet.gettowerlevel() << endl;
		myfile.close();
		return true;
	}
	else
	{
#if(_DEBUG == TRUE)
		cout << "PlayerInfo: Unable to save " << saveFileName.c_str() << endl;
#endif
		myfile.close();
		return false;
	}
}


Vector3 Character::Token2Vector(const string token)
{
	Vector3 tempVector(0.0f, 0.0f, 0.0f);

	std::istringstream ss(token);
	std::string aToken = "";
	std::getline(ss, aToken, ',');
	tempVector.x = Token2Double(aToken);
	std::getline(ss, aToken, ',');
	tempVector.y = Token2Double(aToken);
	std::getline(ss, aToken, ',');
	tempVector.z = Token2Double(aToken);

	return tempVector;
}
double Character::Token2Double(const string token)
{
	return atof(token.c_str());
}

bool Character::Token2Bool(const string token)
{
	return token.at(0) == '1';
}
#endif // ! CHARACTERINFO_H