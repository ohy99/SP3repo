#include "SpellManager.h"

#include "Vector3.h"
#include "Application.h"
#include "GameLogic.h"
#include "Projectile.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "DamageArea.h"
#include "CollisionManager.h"
#include "MinionManager.h"
#include "Minion.h"

SpellManager::SpellManager()
{
	lightning = new DamageArea();
	lightning->set_damage(100, true);
	lightning->set_collision_type(Collision::CollisionType::AABB);
	lightning->scale.Set(10, 100);
	lightning->update_collider();
	lightning->mesh = MeshList::GetInstance()->getMesh("lightning");

	//lightningQuantity = 5;
	lightningCooldown = 3.0;
	lightningReuseTime = lightningCooldown;

	lightning->set_duration(0.5);
	lightning->set_faction_side(Faction::FACTION_SIDE::PLAYER);

	RenderManager::GetInstance()->attach_renderable(lightning);


	freeze = new DamageArea();
	freeze->set_damage(10, true);
	freeze->set_collision_type(Collision::CollisionType::AABB);
	freeze->scale.Set(50, 50);
	freeze->update_collider();
	freeze->mesh = MeshList::GetInstance()->getMesh("freeze");

	freezeCooldown = 3.0;
	freezeReuseTime = freezeCooldown;
	freezeDuration = 0.0;

	freeze->set_duration(0.5);
	freeze->set_faction_side(Faction::FACTION_SIDE::PLAYER);

	RenderManager::GetInstance()->attach_renderable(freeze);


	blast = new DamageArea();
	blast->set_damage(10,true);
	blast->set_collision_type(Collision::CollisionType::AABB);
	blast->scale.Set(20, 20);
	blast->update_collider();
	blast->mesh = MeshList::GetInstance()->getMesh("blast");

	blastCooldown = 10.0;
	blastReuseTime = blastCooldown;
	blastDuration = 0.0;

	blast->set_duration(0.5);
	blast->set_faction_side(Faction::FACTION_SIDE::PLAYER);

	RenderManager::GetInstance()->attach_renderable(blast);

	fire = new DamageArea();
	fire->set_damage(10, false, 1.0);
	fire->set_collision_type(Collision::CollisionType::AABB);
	fire->scale.Set(20, 20);
	fire->update_collider();
	fire->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER");

	fireCooldown = 15.0;
	fireReuseTime = fireCooldown;

	fire->set_duration(10.0);
	fire->set_faction_side(Faction::FACTION_SIDE::PLAYER);

	RenderManager::GetInstance()->attach_renderable(fire);
}

SpellManager::~SpellManager()
{
}

void SpellManager::update(double dt)
{	
	lightningReuseTime += dt;
	lightning->update(dt);

	freezeReuseTime += dt;
	freezeDuration -= dt;
	freeze->update(dt);

	blastReuseTime += dt;
	blastDuration -= dt;
	blast->update(dt);

	fireReuseTime += dt;
	fire->update(dt);


	//cout << lightningQuantity << endl;

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
	if (lightning->active || lightningReuseTime < lightningCooldown)
		return;
	float worldWidth, worldHeight;
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);

	lightning->pos = cursor_point_in_world_space;
	lightning->pos.y = CollisionManager::GetInstance()->get_ground()->pos.y * 2.f + lightning->scale.y * 0.5f;

	if (lightningReuseTime > lightningCooldown)
	{
		lightning->active = true;
		//lightningQuantity--;
		lightningReuseTime = 0.0;
	}
}

void SpellManager::useFreezeSpell()
{
	if (freeze->active || freezeReuseTime < freezeCooldown)
		return;

		float worldWidth, worldHeight;
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);

	freeze->pos = cursor_point_in_world_space;
	freeze->pos.y = CollisionManager::GetInstance()->get_ground()->pos.y * 2.f + freeze->scale.y * 0.5f;

	if (freezeReuseTime > freezeCooldown)
	{
		freeze->active = true;
		//freezeQuantity--;
		freezeReuseTime = 0.0;
		freezeDuration = 2.0;
	}

}

void SpellManager::useBlastSpell()
{
	if (blast->active || blastReuseTime < blastCooldown)
		return;
	float worldWidth, worldHeight;
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);

	blast->pos = cursor_point_in_world_space;
	//adjust the pos to make it at the surface of the ground mesh
	blast->pos.y = CollisionManager::GetInstance()->get_ground()->pos.y * 2.f + blast->scale.y * 0.5f;

	std::list<Collidable*> * enemy_minion_list = MinionManager::GetInstance()->get_enemy_minion_list();

	for each (auto &em in *enemy_minion_list)
	{
		//applying knockback
		Minion* minion = dynamic_cast<Minion*>(em);
		if (minion)
		{
			if (minion->check_collision(blast->get_collider()))
			{
				//check blast direction
				Vector3 direction = -blast->pos + minion->pos;
				try {
					direction.y = 0;
					direction.Normalize();
				}
				catch (DivideByZero& e) {
					direction.SetZero();
				}

				//direction, duration, force variables set here
				minion->set_knockback(direction, 2, 3);
			}
		}
	}

	if (blastReuseTime > blastCooldown)
	{
		blast->active = true;
		blastReuseTime = 0.0;
		blastDuration = 1.0;
	}
}


double SpellManager::getLcooldown()
{
	return lightningReuseTime;
}

double SpellManager::getFcooldown()
{
	return freezeReuseTime;
}

double SpellManager::getBcooldown()
{
	return blastReuseTime;
}

void SpellManager::useFireSpell()
{
	if (fire->active || fireReuseTime < fireCooldown)
		return;
	float worldWidth, worldHeight;
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);

	fire->pos = cursor_point_in_world_space;
	fire->pos.y = CollisionManager::GetInstance()->get_ground()->pos.y * 2.f + fire->scale.y * 0.5f;

	if (fireReuseTime > fireCooldown)
	{
		fire->active = true;
		//lightningQuantity--;
		fireReuseTime = 0.0;
	}
}


bool SpellManager::isFreezeActive()
{
	if (freezeDuration > 0.0)
		return true;
	else
		return false;
}

bool SpellManager::isBlastActive()
{
	if (blastDuration > 0.0)
		return true;
	else
		return false;
}