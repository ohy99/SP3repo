#include "SpellManager.h"

#include "Vector3.h"
#include "Application.h"
#include "GameLogic.h"
#include "Projectile.h"
#include "MeshList.h"

SpellManager::SpellManager()
{
	lightning = new Projectile();
	lightning->set_dmg(100);
	lightning->set_collision_type(Collision::CollisionType::AABB);
	lightning->scale.Set(5, 100);
	lightning->update_collider();
	lightning->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER");

	lightningactivetime = 0.0;
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

	if (lightning->active)
	{
		static double elapsedtime = 0.0;
		elapsedtime += dt;
		cout << "hi" << endl;
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
	}
}