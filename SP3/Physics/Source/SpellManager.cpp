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
	lightning->scale.Set(5, 100);
	lightning->update_collider();
	lightning->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER");

	lightningactivetime = 0.0;

	lightning->set_duration(3.0);
	lightning->set_faction_side(Faction::FACTION_SIDE::PLAYER);

	RenderManager::GetInstance()->attach_renderable(lightning);
}

SpellManager::~SpellManager()
{
}

void SpellManager::update(double dt)
{
	float worldWidth, worldHeight;
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);

	lightning->pos = cursor_point_in_world_space;
	lightning->update(dt);

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
	lightning->active = true;
}

int SpellManager::getQuantity()
{
	return quantity;
}

void SpellManager::setQuantity(int amt)
{
	this->quantity = amt;
}