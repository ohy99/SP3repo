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

	EnemyTower(int MaxHP, float SpawnRate)
	{
		this->MaxHP = MaxHP;
		this->CurrHP = MaxHP;
		this->SpawnRate = SpawnRate;
	}

	//Getters and Setters
	int getMaxHP() { return MaxHP; }
	void setMaxHP(int MaxHP) { this->MaxHP = MaxHP; }

	int getCurrHP() { return CurrHP; }
	void setCurrHP(int HP) { this->CurrHP = HP; }

	int getSpawnRate() { return SpawnRate; }
	void setSpawnRate(int spawnRate) { this->SpawnRate = spawnRate; }
};