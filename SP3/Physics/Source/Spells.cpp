#include "Spells.h"

#include "Vector3.h"
#include "Application.h"
#include "GameLogic.h"
#include "Projectile.h"
#include "MeshList.h"

Spells::Spells() 
{

}
Spells::~Spells() 
{

}

int Spells::getLightningQuantity()
{
	return lightningQuantity;
}

void Spells::setLightningQuantity(int amt)
{
	this->lightningQuantity = amt;
}

//void Spells::lightningSpell(double dt)
//{
//	//remove a set number of enemy AI at random
//	//if (lightningQuantity == 0)
//	//	return;
//
//}
//
//void Spells::freezeSpell()
//{
//	//stops all AI from moving
//}
//
//void Spells::blastSpell()
//{
//	//pushes all AI back to their base
//}
//
//void Spells::renderSpells()
//{
//
//	if (lightning->active) {
//		lightning->render();
//	}
//}