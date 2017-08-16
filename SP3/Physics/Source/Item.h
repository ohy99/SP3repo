#pragma once

class Item
{
public:
	//repair kits
	int getSmallRepair() { return smallRepairNum; }
	int getMedRepair() { return medRepairNum; }
	int getBigRepair() { return bigRepairNum; }

	void setSmallRepair(int amt) { this->smallRepairNum = amt; }
	void setMedRepair(int amt) { this->medRepairNum = amt; }
	void setBigRepair(int amt) { this->bigRepairNum = amt; }

	//current weapon
	int getCurrWeapon() { return currWeapon; }

	//boosts/magic
	int getDamBoostNum() { return damBoostNum; }
	int getHPboostNum() { return HPboostNum; }
	int getLightningNum() { return lightningNum; }

protected:
	//repair kits
	int smallRepairNum, medRepairNum,bigRepairNum;
	
	//boosts/magic
	int damBoostNum, HPboostNum, lightningNum;
	
	//current weapon
	int currWeapon;
};