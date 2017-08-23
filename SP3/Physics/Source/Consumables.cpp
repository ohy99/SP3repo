#include "Consumables.h"
#include "Wallet.h"
#include "CharacterInfo.h"

//void Consumables::CraftPotion()
//{
//}

Consumables::Consumables()
{
}

Consumables::~Consumables()
{
}

void Consumables::attachWallet(Wallet *wallet)
{
	this->wallet = wallet;
}

void Consumables::attachCharacter(Character *character)
{
	this->character = character;
}

void Consumables::UseSmallRepairKit()
{
	if (wallet->getsmallrepair() > 0)
	{
		wallet->removei_smallrepair(1);
		Addhealth(150);
	}
}
void Consumables::UseMedRepairKit()
{
	if (wallet->getmediumrepair() > 0)
	{
		wallet->removei_medrepair(1);
		Addhealth(300);
	}
}
void Consumables::UseBigRepairKit()
{
	if (wallet->getbigrepair() > 0)
	{
		wallet->removei_bigrepair(1);
		Addhealth(500);
	}
}

void Consumables::Addhealth(int amt)
{
	if (character->getcurrenthealth() + amt > character->getmaxhealth())
		character->setcurrenthealth(character->getmaxhealth());
	else
		character->setcurrenthealth(character->getcurrenthealth() + amt);
	
	cout << "used" << endl;
}

//void Consumables::addSmallRepair(int amt)
//{
//	consumable.setSmallRepair(consumable.getSmallRepair() + amt);
//
//	//if (this->smallRepairKit <= 0)
//	//	this->smallRepairKit = 0;
//}
//
//void Consumables::addMedRepair(int amt)
//{
//	consumable.setMedRepair(consumable.getMedRepair() + amt);
//
//	//if (this->medRepairKit <= 0)
//	//	this->medRepairKit = 0;
//}
//
//void Consumables::addBigRepair(int amt)
//{
//	consumable.setBigRepair(consumable.getBigRepair() + amt);
//
//	//if (this->bigRepairKit <= 0)
//	//	this->bigRepairKit = 0;
//}

//void Consumables::addHerb(int amt)
//{
//	this->herb+= amt;
//
//	if (this->herb <= 0)
//		this->herb = 0;
//}
//
//UINT Consumables::getSmallRepair()
//{
//	return this->smallRepairKit;
//}
//
//UINT Consumables::getMedRepair()
//{
//	return this->medRepairKit;
//}
//
//UINT Consumables::getBigRepair()
//{
//	return this->bigRepairKit;
//}
//
//UINT Consumables::getHerb()
//{
//	return this->herb;
//}
