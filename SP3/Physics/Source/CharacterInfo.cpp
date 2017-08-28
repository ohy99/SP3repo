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
#include "WeaponCannon.h"
#include "NoobBow.h"
#include "OkayBow.h"
#include "GoodBow.h"
#include "AudioPlayer.h"
using namespace std;
using std::string;

Character::Character() : maxhealth(0),
health(0),
damage(0),
levels(0),
//coins(0),
highscore(0),
keypresscooldown(3.0),
weap(nullptr),
ulti_charge(0.f),
max_ulti_charge(1500.f),
kill_enemy_extra_charge_percent(0.5f)
{
	//Audio stuff lul
	//Playlist starting from 0 

	//Spells
	audioPlayer.playlist.push_back(new Sound("Audio//lightning.mp3")); //0
	audioPlayer.playlist.push_back(new Sound("Audio//Blast.mp3")); //1
	audioPlayer.playlist.push_back(new Sound("Audio//Blizzard.mp3")); //2
	audioPlayer.playlist.push_back(new Sound("Audio//Drain.mp3")); //3

	//Consumables
	audioPlayer.playlist.push_back(new Sound("Audio//SmallRepair.mp3")); //4
	audioPlayer.playlist.push_back(new Sound("Audio//Repair.mp3"));//5
	audioPlayer.playlist.push_back(new Sound("Audio//BigRepair.mp3"));//6

	audioPlayer.playlist.push_back(new Sound("Audio//Drain.mp3"));//7
	audioPlayer.playlist.push_back(new Sound("Audio//Fire.mp3"));//8
	//set nullptr
	weapsah[0] = nullptr;
	weapsah[1] = nullptr;
	weapsah[2] = nullptr;
}

Character::~Character()
{
	//if(weap)
	//delete weap;
	for (int i = 0; i < 3; ++i)
		if (weapsah[i])
			delete weapsah[i];
}


void Character::Update(double dt)
{

	//Weapons Section Update--------------------------------//
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	//static bool keypressed = false;
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);
	weap->dir = -weap->pos + cursor_point_in_world_space;
	try {
		weap->dir.Normalize();
	}
	catch (DivideByZero &e) {
		weap->dir.Set(0, 1, 0);
	}
	if (Application::GetInstance().IsMousePressed(1))
	{
		weap->Discharge(weap->pos, weap->dir);
	}

	weap->WeaponInfo::Update(dt);
	keypresscooldown += dt;
	//------------Minon Section Update-------------------------------//
	spawn_minion();

	//------------------------Spell Section Update--------------------------//
	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('6') && !dakeypressed)
		{
			if (SpellManager::GetInstance()->useLightningSpell())
				audioPlayer.playSoundThreaded(audioPlayer.playlist[0]->fileName_);
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
			if (SpellManager::GetInstance()->useFreezeSpell())
				audioPlayer.playSoundThreaded(audioPlayer.playlist[2]->fileName_);
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
			if(SpellManager::GetInstance()->useBlastSpell())
				audioPlayer.playSoundThreaded(audioPlayer.playlist[1]->fileName_);
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('8') && dakeypressed)
		{
			dakeypressed = false;
		}
	}

	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('9') && !dakeypressed)
		{
			if (SpellManager::GetInstance()->useFireSpell())
				if (SpellManager::GetInstance()->useBlastSpell())
					audioPlayer.playSoundThreaded(audioPlayer.playlist[8]->fileName_);
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('9') && dakeypressed)
		{
			dakeypressed = false;
		}
	}
	if(keypresscooldown>=3.0f)
	{
		{
			static bool dakeypressed = false;
			if (Application::GetInstance().IsKeyPressed('Z') && !dakeypressed)
			{
				if (consumables.UseSmallRepairKit())
					audioPlayer.playSoundThreaded(audioPlayer.playlist[4]->fileName_);
				dakeypressed = true;
				keypresscooldown = 0;
			}
			else if (!Application::GetInstance().IsKeyPressed('Z') && dakeypressed)
			{
				dakeypressed = false;
			}
		}
		{
			static bool dakeypressed = false;
			if (Application::GetInstance().IsKeyPressed('X') && !dakeypressed)
			{
				if (consumables.UseMedRepairKit())
					audioPlayer.playSoundThreaded(audioPlayer.playlist[5]->fileName_);
				dakeypressed = true;
				keypresscooldown = 0;
			}
			else if (!Application::GetInstance().IsKeyPressed('X') && dakeypressed)
			{
				dakeypressed = false;
			}
		}
		{
			static bool dakeypressed = false;
			if (Application::GetInstance().IsKeyPressed('C') && !dakeypressed)
			{
				if (consumables.UseBigRepairKit())
					audioPlayer.playSoundThreaded(audioPlayer.playlist[6]->fileName_);
				dakeypressed = true;
				keypresscooldown = 0;
			}
			else if (!Application::GetInstance().IsKeyPressed('C') && dakeypressed)
			{
				dakeypressed = false;
			}
		}
	}
	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('Q') && !dakeypressed)
		{
			weapsah[currweap]->active = false;
			currweap = Math::Wrap(currweap - 1, 0, 2);
			weapsah[currweap]->active = true;
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('Q') && dakeypressed)
		{
			dakeypressed = false;
		}
	}
	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('E') && !dakeypressed)
		{
			weapsah[currweap]->active = false;
			currweap = Math::Wrap(currweap + 1, 0, 2);
			weapsah[currweap]->active = true;
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('E') && dakeypressed)
		{
			dakeypressed = false;
		}
	}
	weap = weapsah[currweap];

	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed(VK_SPACE) && !dakeypressed)
		{
			if (SpellManager::GetInstance()->use_longkang_spell()) 
				audioPlayer.playSoundThreaded(audioPlayer.playlist[7]->fileName_);

			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed(VK_SPACE) && dakeypressed)
		{
			dakeypressed = false;
		}
	}


}



void Character::Init()
{
	this->Load();
	//weap->Init();
	//weap->set_faction_side(Faction::FACTION_SIDE::PLAYER);
	//weap->mesh = MeshList::GetInstance()->getMesh("CANNON");
	//weap->scale.Set(5, 5, 5);
	//weap->active = true;
	//weap->pos.Set(7.5, 25);
	//weap->set_damage(50);
	weap = new NoobBow();
	weap->pos.Set(7.5, 25);
	weap->scale.Set(5, 5, 5);
	weap->set_faction_side(Faction::FACTION_SIDE::PLAYER);
	//weap->mesh = MeshList::GetInstance()->getMesh("CANNON");
	weap->active = false;
	RenderManager::GetInstance()->attach_renderable(weap, 1);
	weapsah[0] = weap;
	weap = new OkayBow();
	weap->pos.Set(7.5, 25);
	weap->scale.Set(7.5, 7.5, 5);
	weap->set_faction_side(Faction::FACTION_SIDE::PLAYER);
	//weap->mesh = MeshList::GetInstance()->getMesh("CANNON");
	weap->active = false;
	RenderManager::GetInstance()->attach_renderable(weap, 1);
	weapsah[1] = weap;
	weap = new GoodBow();
	weap->pos.Set(7.5, 25);
	weap->scale.Set(10, 5, 5);
	weap->set_faction_side(Faction::FACTION_SIDE::PLAYER);
	//weap->mesh = MeshList::GetInstance()->getMesh("CANNON");
	weap->active = false;
	RenderManager::GetInstance()->attach_renderable(weap, 1);
	weapsah[2] = weap;
	weap = weapsah[0];
	currweap = 0;
	weap->active = true;

	//RenderManager::GetInstance()->attach_renderable(weap, 1);
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
//
//int Character::getcurrentcoins()
//{
//	return coins;
//}

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
//
//void Character::setcurrentcoins(int coin)
//{
//	this->coins = coins;
//}

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
//
//void Character::add_coins(int value)
//{
//	this->coins += value;
//
//	//std::cout << coins << std::endl;
//}

//ULTI
void Character::set_damage_feedback(int dmg, bool killed_target, int target_max_hp)
{
	//gains 1 charge for every dmg dealt
	//if killed target, gain extra 50% charge of its max hp
	this->ulti_charge += Math::Min( (killed_target ? (float)dmg + (float)target_max_hp * kill_enemy_extra_charge_percent : (float)dmg), 
		max_ulti_charge - ulti_charge);
	//std::cout << ulti_charge << std::endl;
}

bool Character::can_use_ulti()
{
	return ulti_charge == max_ulti_charge;
}

void Character::set_use_ulti(bool use)
{
	if (use == true)
		this->ulti_charge = 0.f;
}

float Character::get_ulti_charge()
{
	return ulti_charge / max_ulti_charge;
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
	int temp[10];

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
				else if (theTag == "i_coins")
				{
					temp[9] = Token2Double(aToken);
				}
			}
		}

		//int 1 = Token2Double(aToken);
		wallet.wLoad(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7], temp[8] , temp[9]);
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
		myfile << "i_coins=" << wallet.getcoins() << endl;
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


void Character::spawn_minion()
{
	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('1') && !dakeypressed)
		{
			if (this->wallet.getbrowndrake())
			{
				MinionManager::GetInstance()->spawn_minion();
				this->wallet.removei_browndrake(1);
			}
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
			if (this->wallet.getbluedrake())
			{
				MinionManager::GetInstance()->spawn_minion(true, MinionInfo::MINION_TYPE::BASIC_RANGE);
				this->wallet.removei_bluedrake(1);
			}
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('2') && dakeypressed)
		{
			dakeypressed = false;
		}
	}

	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('3') && !dakeypressed)
		{
			if (this->wallet.getgreendrake())
			{
				MinionManager::GetInstance()->spawn_minion(true, MinionInfo::MINION_TYPE::BASIC_SIEGE);
				this->wallet.removei_greendrake(1);
			}
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('3') && dakeypressed)
		{
			dakeypressed = false;
		}
	}

	{
		static bool dakeypressed = false;
		if (Application::GetInstance().IsKeyPressed('4') && !dakeypressed)
		{
			if (this->wallet.getblackdrake())
			{
				MinionManager::GetInstance()->spawn_minion(true, MinionInfo::MINION_TYPE::BASIC_HEALER);
				this->wallet.removei_blackdrake(1);
			}
			dakeypressed = true;
		}
		else if (!Application::GetInstance().IsKeyPressed('4') && dakeypressed)
		{
			dakeypressed = false;
		}
	}

}
#endif // ! CHARACTERINFO_H