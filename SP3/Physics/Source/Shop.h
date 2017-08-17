#include "CharacterInfo.h"
#include "Mtx44.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using std::string;



class Shop {

private:
	
	//Coin Pouch//
	
	//Price//
	int ID;//ID for items 
	int damage;
	int price;
	//Levels//
	int levelsreq;

	//Ecnomoy & highscore//
	int coinsreq;
	string name;
	string description;

public:

	//Loading of csv file


	//Changing ID to name
	  //---------------------Token Converts-----------------//
	Vector3 Token2Vector(const string token);
	double Token2Double(const string token);
	bool Token2Bool(const string token);



	//-----------Functions--------------------//

	bool LoadCSV(const string fileName);
	void CheckReader(const string fileName = "CSV//Sample.csv");

};

