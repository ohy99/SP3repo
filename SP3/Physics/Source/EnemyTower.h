#pragma once

class EnemyTower
{
private:
	int MaxHP;
	int CurrHP;
	int SpawnRate;

public:
	EnemyTower() { }
	~EnemyTower() { }

	//Getters and Setters
	int getCurrHP() { return CurrHP; }
	void setCurrHP(int HP) { this->CurrHP = HP; }

	int getSpawnRate() { return SpawnRate; }
	void setSpawnRate(int spawnRate) { this->SpawnRate = spawnRate; }
};