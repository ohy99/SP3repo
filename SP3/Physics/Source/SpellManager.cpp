#include "SpellManager.h"

#include "Vector3.h"
#include "Application.h"
#include "GameLogic.h"
#include "Projectile.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "DamageArea.h"

SpellManager::SpellManager()
{
	lightning = new DamageArea();
	lightning->set_damage(50);
	lightning->set_collision_type(Collision::CollisionType::AABB);
	lightning->scale.Set(10, 100);
	lightning->update_collider();
	lightning->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER");

	lightningQuantity = 5;
	lightningReuseTime = 3.0;

	lightning->set_duration(0.5);
	lightning->set_faction_side(Faction::FACTION_SIDE::PLAYER);

	RenderManager::GetInstance()->attach_renderable(lightning);
}

SpellManager::~SpellManager()
{
}

void SpellManager::update(double dt)
{	
	lightningReuseTime += dt;
	lightning->update(dt);

	cout << lightningQuantity << endl;
	//if (lightning->active)
	//{
	//	lightning->pos = cursor_point_in_world_space;
	//	static double elapsedtime = 0.0;
	//	elapsedtime += dt;
	//	cout << "hi" << endl;
	//	if (elapsedtime > 1.f)
	//	{
	//		lightning->active = true;

	//		lightningactivetime += dt;
	//		if (lightningactivetime > 1.f)
	//		{
	//			elapsedtime = 0.0;
	//			lightningactivetime = 0.0;

	//			lightning->active = false;
	//		}
	//	}
	//}
}

void SpellManager::useLightningSpell()
{
	float worldWidth, worldHeight;
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);

	lightning->pos = cursor_point_in_world_space;

	if (lightningQuantity > 0 && lightningReuseTime>3.0)
	{
		lightning->active = true;
		lightningQuantity--;
		lightningReuseTime = 0.0;
	}
}

int SpellManager::getLQuantity()
{
	return lightningQuantity;
}

void SpellManager::setLQuantity(int amt)
{
	this->lightningQuantity = amt;
}