#pragma once

#include "WeaponInfo.h"
#include "Item.h"

class Weapon:public WeaponInfo, public Item
{
	
public:
	Weapon();
	virtual ~Weapon();

	// Initialise this instance to default values
	void Init(void);

};