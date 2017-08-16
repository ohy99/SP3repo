#pragma once

class EnemyMinion
{
private:
	int MaxHP;
	int CurrHP;
	int Atk;
	float MoveSpd;

public:
	EnemyMinion() { }
	~EnemyMinion() { }

	EnemyMinion(int MaxHP, int Atk, float MoveSpd)
	{
		this->MaxHP = MaxHP;
		this->CurrHP = MaxHP;
		this->Atk = Atk;
		this->MoveSpd = MoveSpd;
	}

	//Getters and Setters
	int getMaxHP() { return MaxHP; }
	void setMaxHP(int MaxHP) { this->MaxHP = MaxHP; }

	int getCurrHP() { return CurrHP; }
	void setCurrHP(int HP) { this->CurrHP = HP; }

	int getAtk() { return Atk; }
	void setAtk(int Atk) { this->Atk = Atk; }

	float getMoveSpd() { return MoveSpd; }
	void setMoveSpd(int moveSpd) { this->MoveSpd = moveSpd; }
};