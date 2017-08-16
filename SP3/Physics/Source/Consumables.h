#ifndef CONSUMABLES_H
#define CONSUMABLES_H

#include "Application.h"
#include "Item.h"

class Consumables : public Item
{
public:
	Consumables(){}
	~Consumables(){}
	void UseSmallRepairKit();
	void UseMedRepairKit();
	void UseBigRepairKit();

	void addSmallRepair(int amt);
	void addMedRepair(int amt);
	void addBigRepair(int amt);

	void Addhealth(int amt);

	//unsigned int getSmallRepair();
	//unsigned int getMedRepair();
	//unsigned int getBigRepair();

	//int smallRepairKit = 0; // restores 5 hp
	//int medRepairKit = 0; // restores 10 hp
	//int bigRepairKit = 0; // restores 20 hp

	Item consumable;
};


#endif
