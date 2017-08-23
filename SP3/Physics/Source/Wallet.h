#ifndef WALLET_H
#define WALLET_H


class Wallet 
{
private:
	int i_smallrepair;
	int i_medrepair;
	int i_bigrepair;

	int i_greendrake;
	int i_browndrake;
	int i_bluedrake;
	int i_blackdrake;

	int i_weaplevel;
	int i_towerlevel;


public:
	
	Wallet() : i_smallrepair(0),
		i_medrepair(0),
		i_bigrepair(0),
		i_greendrake(0),
		i_browndrake(0),
		i_bluedrake(0),
		i_blackdrake(0),
		i_weaplevel(0),
		i_towerlevel(0){
	};
	~Wallet() {};
	//Functions
	void wLoad(int getsmallrepair, int getmediumrepair, int getbigrepair, int getgreendrake, int getbrowndrake, int getbluedrake, int getblackdrake, int getweaplevel, int gettowerlevel)
	{
		this->i_smallrepair = getsmallrepair;
		this->i_medrepair = getmediumrepair;
		this->i_bigrepair = getbigrepair;

		this->i_greendrake = getgreendrake;
		this->i_browndrake = getbrowndrake;
		this->i_bluedrake = getbluedrake;
		this->i_blackdrake = getblackdrake;
		this->i_weaplevel = getweaplevel;
		this->i_towerlevel = gettowerlevel;
	};
	//Getters
	int getsmallrepair()
	{
		return i_smallrepair;
	}


	int getmediumrepair()
	{
		return i_medrepair;
	}

	int getbigrepair()
	{
		return i_bigrepair;
	}

	int getgreendrake()
	{
		return i_greendrake;
	}

	int getbrowndrake()
	{
		return i_browndrake;
	}

	int getbluedrake()
	{
		return i_bluedrake;
	}

	int getblackdrake()
	{
		return i_blackdrake;
	}


	int getweaplevel()
	{
		return i_weaplevel;
	}


	int gettowerlevel()
	{
		return i_towerlevel;
	}

	//Buy(add items)

	//Repairs--------------------------------------------------------------------------------------------------//
	void addi_smallrepair(int i_smallrepair) { this->i_smallrepair += 1 ;  }
	void addi_medrepair(int i_medrepair) { this->i_medrepair += 1; }
	void addi_bigrepair(int i_bigrepair) { this->i_bigrepair += 1; }

	//Summoning of Minons
	void addi_greendrake(int i_greendrake) { this->i_greendrake += 1; }
	void addi_browndrake(int i_browndrake) { this->i_browndrake += 1; }
	void addi_bluedrake(int i_bluedrake) { this->i_bluedrake += 1; }
	void addi_blackdrake(int i_blackdrake) { this->i_blackdrake += 1; }

	//
	void addi_weaplevel(int i_weaplevel) { this->i_weaplevel += 1; }
	void addi_towerlevel(int i_weaplevel) { this->i_towerlevel += 1; }



	//Sell (remove items)--------------------------------------------------------------------------------------//
	void removei_smallrepair(int i_smallrepair) { this->i_smallrepair -= 1; }
	void removei_medrepair(int i_medrepair) { this->i_medrepair -= 1; }
	void removei_bigrepair(int i_bigrepair) { this->i_bigrepair -= 1; }

	//Summoning of Minons
	void removei_greendrake(int i_greendrake) { this->i_greendrake -= 1; }
	void removei_browndrake(int i_browndrake) { this->i_browndrake -= 1; }
	void removei_bluedrake(int i_bluedrake) { this->i_bluedrake -= 1; }
	void removei_blackdrake(int i_blackdrake) { this->i_blackdrake -= 1; }

	//Weapon levels
	void removei_weaplevel(int i_weaplevel) { this->i_weaplevel -= 1; }
	void removei_towerlevel(int i_weaplevel) { this->i_towerlevel -= 1; }
};
#endif