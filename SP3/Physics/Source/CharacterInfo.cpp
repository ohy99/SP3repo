#include "CharacterInfo.h"
#include "Mtx44.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using std::string;

Character::Character(): maxhealth(1000),
health(100),
damage(0),
levels(0),
coins(0),
highscore(0)
{ 
}

Character::~Character()
{

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
			}
		}
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
		myfile << "maxhealth=" << maxhealth  << endl;
		myfile << "health=" << health << endl;
		myfile << "damage=" << damage << endl;
		myfile << "levels=" << levels << endl;
		myfile << "coin=" << coins << endl;
		myfile << "highscore=" << highscore << endl;
		myfile << "currentsound=" << soundtrack << endl;
		myfile << "muteornot=" << mute << endl;
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
