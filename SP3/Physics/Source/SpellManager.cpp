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
#include "CharacterInfo.h"
#include "GameObject.h"
#include "TowerManager.h"

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

	is_longkang_charging_active = false;
	is_longkang_active = false;
	longkang_elasped = 0.0;
	longkang_chargeup = 2.0;

	longkang = new DamageArea();
	longkang->set_damage(1, false, 5.f);
	longkang->set_collision_type(Collision::CollisionType::AABB);
	longkang->scale.Set(100, 10);
	longkang->update_collider();
	longkang->mesh = MeshList::GetInstance()->getMesh("blast");

	longkang_active_elapsed = 0.0;
	longkang_active_duration = 3.0;
	longkang->set_duration(longkang_active_duration);
	longkang->set_faction_side(Faction::FACTION_SIDE::NONE);

	RenderManager::GetInstance()->attach_renderable(longkang);
	longkang_charging_mesh = new GameObject();
	longkang_charging_mesh->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER");
	longkang_charging_mesh->pos = CollisionManager::GetInstance()->get_ground()->pos;
	RenderManager::GetInstance()->attach_renderable(longkang_charging_mesh);
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

	update_charging_longkang(dt);
	longkang->update(dt);
	update_active_longkang(dt);
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


void SpellManager::use_longkang_spell()
{
	//if (!character->can_use_ulti())
	//	return;

	longkang->pos = CollisionManager::GetInstance()->get_ground()->pos;
	//longkang->pos.y = CollisionManager::GetInstance()->get_ground()->pos.y;

	this->character->set_use_ulti(true);

	is_longkang_charging_active = true;
	longkang_charging_mesh->active = true;
}
float SpellManager::get_longkang_charge() {
	return this->character->get_ulti_charge();
}

void SpellManager::update_charging_longkang(double dt)
{
	if (!is_longkang_charging_active && !longkang_charging_mesh->active)
		return;

	static bool after_midway = false;

	static float xoffset = 0.75f, yoffset = 1.5f;

	//charge up the longkang first
	if (after_midway == false)
	{
		longkang_elasped = Math::Min(longkang_elasped + dt, longkang_chargeup);
		longkang_charging_mesh->scale.x = CollisionManager::GetInstance()->get_ground()->scale.x * xoffset
			* (float)(longkang_elasped / longkang_chargeup);
		longkang_charging_mesh->scale.y = CollisionManager::GetInstance()->get_ground()->scale.y * yoffset
			* (float)(longkang_elasped / longkang_chargeup);
	}
	else
	{
		longkang_elasped = Math::Max(longkang_elasped - dt, 0.0);
		longkang_charging_mesh->scale.x = CollisionManager::GetInstance()->get_ground()->scale.x * xoffset
			* (float)(longkang_elasped / longkang_chargeup);
		longkang_charging_mesh->scale.y = CollisionManager::GetInstance()->get_ground()->scale.y * yoffset
			* (float)(longkang_elasped / longkang_chargeup);
	}

	
	if (longkang_elasped >= longkang_chargeup && after_midway == false)
	{
		longkang->active = true;
		longkang->scale = longkang_charging_mesh->scale;
		longkang->update_collider();
		//longkang->scale.Set(100, 10);

		//longkang_elasped = 0.0;
		is_longkang_charging_active = false;

		longkang_charging_mesh->active = false;
		//longkang_charging_mesh->scale.SetZero();
		after_midway = true;

		is_longkang_active = true;
	}
	else if (longkang_elasped == 0.0 && after_midway == true)
	{
		is_longkang_charging_active = false;
		longkang_charging_mesh->active = false;
		after_midway = false;
	}
}

void SpellManager::update_active_longkang(double dt)
{
	if (!is_longkang_active)
		return;
	longkang_active_elapsed = Math::Min(longkang_active_elapsed + dt, longkang_active_duration);
	bool instantkill = false;
	if (longkang_active_elapsed == longkang_active_duration)
		instantkill = true;

	static float kbduration, kbforce;
	kbduration = 5.f;
	kbforce = 10.f;

	//make everyone drop
	std::list<Collidable*> * enemy_minion_list = MinionManager::GetInstance()->get_enemy_minion_list();

	for each (auto &em in *enemy_minion_list)
	{
		//applying knockback
		Minion* minion = dynamic_cast<Minion*>(em);
		if (minion)
		{
			if (minion->check_collision(longkang->get_collider()))
			{
				Vector3 direction(0, -1, 0);

				minion->set_knockback(direction, kbduration, kbforce);
				
				if (minion->pos.y < 0 || instantkill)
					minion->active = false;
			}
		}
	}
	std::list<Collidable*> * player_minion_list = MinionManager::GetInstance()->get_player_minion_list();

	for each (auto &pm in *player_minion_list)
	{
		//applying knockback
		Minion* minion = dynamic_cast<Minion*>(pm);
		if (minion)
		{
			if (minion->check_collision(longkang->get_collider()))
			{
				Vector3 direction(0, -1, 0);

				minion->set_knockback(direction, kbduration, kbforce);

				if (minion->pos.y < 0 || instantkill)
					minion->active = false;
			}
		}
	}

	
	if (longkang_active_elapsed == longkang_active_duration)
	{
		longkang_charging_mesh->active = true;
		is_longkang_charging_active = false;
		is_longkang_active = false;
		//instantly kill those who still collide with
		longkang_active_elapsed = 0.0;
	}
}