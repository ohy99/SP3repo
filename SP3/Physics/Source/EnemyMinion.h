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

	//Getters and Setters
	int getCurrHP() { return CurrHP; }
	void setCurrHP(int HP) { this->CurrHP = HP; }

	int getAtk() { return Atk; }
	void setAtk(int Atk) { this->Atk = Atk; }

	float getMoveSpd() { return MoveSpd; }
	void setMoveSpd(int moveSpd) { this->MoveSpd = moveSpd; }
};