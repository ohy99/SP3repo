#include "Spells.h"

#include "Vector3.h"
#include "Application.h"
#include "GameLogic.h"
#include "Projectile.h"
#include "MeshList.h"

Spells::Spells() 
{
	lightning = new Projectile();
	lightning->set_dmg(100);
	lightning->set_collision_type(Collision::CollisionType::AABB);
	lightning->scale.Set(5, 100);
	lightning->update_collider();
	lightning->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER");


	lightningQuantity = 1;
	lightningactivetime = 0.0;
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

void Spells::lightningSpell(double dt)
{
	//remove a set number of enemy AI at random
	//if (lightningQuantity == 0)
	//	return;

	float worldWidth, worldHeight;
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);


	lightning->pos = cursor_point_in_world_space;

	static double elapsedtime = 0.0;
	elapsedtime += dt;

	
	if (elapsedtime > 1.f)
	{

			lightning->active = true;
		

		lightningactivetime += dt;
		if (lightningactivetime > 1.f)
		{
			elapsedtime = 0.0;
			lightningactivetime = 0.0;

			lightning->active = false;
		}
	}

	--lightningQuantity;
}

void Spells::freezeSpell()
{
	//stops all AI from moving
}

void Spells::blastSpell()
{
	//pushes all AI back to their base
}

void Spells::renderSpells()
{

	if (lightning->active) {
		lightning->render();
	}
}