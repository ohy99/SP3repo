//Shop.h
#ifndef SHOP_H
#define SHOP_H

#include "GameObject.h"

#include "Button.h"


using namespace std;
using std::string;

class Wallet;
class Mesh;
class Character;
class Shop {





public:
	Shop();
	~Shop();
	void Render();
	void init();
	void Update(double dt);
	void attachWalletInfo(Wallet* walletshop);
	
protected:
	Wallet *walletshop;
	
	//Title
	Button Title;
	//Buy Buttons

	Button Buy1;
	Button Buy2;
	Button Buy3;
	Button Buy4;
	Button Buy5;
	Button Buy6;
	Button Buy7;
	Button Buy8;
	Button Buy9;
	//Sell Buttons
	Button Sell1;
	Button Sell2;
	Button Sell3;
	Button Sell4;
	Button Sell5;
	Button Sell6;
	Button Sell7;
	Button Sell8;
	Button Sell9;

	Button ShopUI;
	float worldWidth;
	float worldHeight;
};

#endif
