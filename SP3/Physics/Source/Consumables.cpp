#include "Consumables.h"

//void Consumables::CraftPotion()
//{
//}

void Consumables::UseSmallRepairKit()
{
	if (consumable.getSmallRepair() > 0)
	{
		consumable.setSmallRepair(consumable.getSmallRepair() - 1);
		Addhealth(5);
	}
}
void Consumables::UseMedRepairKit()
{
	if (consumable.getMedRepair() > 0)
	{
		consumable.setMedRepair(consumable.getMedRepair() - 1);
		Addhealth(10);
	}
}
void Consumables::UseBigRepairKit()
{
	if (consumable.getBigRepair() > 0)
	{
		consumable.setBigRepair(consumable.getBigRepair() - 1);
		Addhealth(20);
	}
}

void Consumables::Addhealth(int amt)
{
	//player HP += amt
}

void Consumables::addSmallRepair(int amt)
{
	consumable.setSmallRepair(consumable.getSmallRepair() + amt);

	//if (this->smallRepairKit <= 0)
	//	this->smallRepairKit = 0;
}

void Consumables::addMedRepair(int amt)
{
	consumable.setMedRepair(consumable.getMedRepair() + amt);

	//if (this->medRepairKit <= 0)
	//	this->medRepairKit = 0;
}

void Consumables::addBigRepair(int amt)
{
	consumable.setBigRepair(consumable.getBigRepair() + amt);

	//if (this->bigRepairKit <= 0)
	//	this->bigRepairKit = 0;
}

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
