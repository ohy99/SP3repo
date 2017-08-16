#include "Consumables.h"

//void Consumables::CraftPotion()
//{
//}

void Consumables::UseSmallRepairKit()
{
	if (smallRepairKit > 0)
	{
		smallRepairKit--;
		Addhealth(5);
	}
}

void Consumables::Addhealth(int amt)
{
	//player HP += amt
}

void Consumables::addSmallRepair(int amt)
{
	this->smallRepairKit += amt;

	if (this->smallRepairKit <= 0)
		this->smallRepairKit = 0;
}

void Consumables::addMedRepair(int amt)
{
	this->medRepairKit += amt;

	if (this->medRepairKit <= 0)
		this->medRepairKit = 0;
}

void Consumables::addBigRepair(int amt)
{
	this->bigRepairKit += amt;

	if (this->bigRepairKit <= 0)
		this->bigRepairKit = 0;
}

//void Consumables::addHerb(int amt)
//{
//	this->herb+= amt;
//
//	if (this->herb <= 0)
//		this->herb = 0;
//}

UINT Consumables::getSmallRepair()
{
	return this->smallRepairKit;
}

UINT Consumables::getMedRepair()
{
	return this->medRepairKit;
}

UINT Consumables::getBigRepair()
{
	return this->bigRepairKit;
}
//
//UINT Consumables::getHerb()
//{
//	return this->herb;
//}
