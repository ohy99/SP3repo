#include "lightningSpell.h"

#include "Vector3.h"
#include "Application.h"
#include "GameLogic.h"
#include "Projectile.h"
#include "MeshList.h"

LightningSpell::LightningSpell()
{
	//lightning = new Projectile();
	//lightning->set_dmg(100);
	//lightning->set_collision_type(Collision::CollisionType::AABB);
	//lightning->scale.Set(5, 100);
	//lightning->update_collider();
	//lightning->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER");

	lightningQuantity = 1;
	//lightningactivetime = 0.0;
}

LightningSpell::~LightningSpell()
{
}

void LightningSpell::useLightningSpell()
{
	SpellManager::lightning->active = true;

	setLightningQuantity(getLightningQuantity() - 1);
}

void LightningSpell::renderSpell()
{
	if (lightning->active) {
		lightning->render();
	} 
}
