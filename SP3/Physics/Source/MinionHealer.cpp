#include "MinionHealer.h"

#include "MeshList.h"
#include "SpriteAnimation.h"
#include "DamageArea.h"
#include "MinionManager.h"

#include "Graphics.h"
#include "RenderHelper.h"
#include "TowerManager.h"
#include "Tower.h"
#include <limits>

MinionHealer::MinionHealer()
{
	this->minion_type = MinionInfo::MINION_TYPE::BASIC_HEALER;

	mesh_state[MinionInfo::STATE::DEAD] = nullptr;
	mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("BLACKDRAGON");
	mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("BLACKATTACK");
	mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("BLACKDRAGON");
}

MinionHealer::~MinionHealer()
{
}

void MinionHealer::attack()
{
	if (nearest_target == nullptr)
		return;
	if (this->can_attack() == false)
		return;

	DamageArea* temp = MinionManager::GetInstance()->request_inactive_collidable(MINION_TYPE::BASIC_MELEE);
	if (temp)
	{
		temp->active = true;
		temp->mesh = nullptr;// MeshList::GetInstance()->getMesh("CANNONBALL");
		temp->mesh = MeshList::GetInstance()->getMesh("Sphere"); //sphere appear extra large because the default radius is 1.f and not 0.5.
		temp->pos.Set(this->pos.x + (this->move_direction * this->scale.x * 0.5f).x,
			this->pos.y, this->pos.z);
		temp->set_collision_type(Collision::CollisionType::SPHERE);
		temp->scale.Set(this->attack_range * (this->scale.x * 0.5f),
			this->attack_range * (this->scale.x * 0.5f));
		temp->update_collider();
		temp->set_damage(-this->get_attack_damage());//negative coz heal
		if (this->get_faction_side() == Faction::FACTION_SIDE::PLAYER)
			temp->set_faction_side(Faction::FACTION_SIDE::ENEMY);//enemy so that damage area will only affect player
		else
			temp->set_faction_side(Faction::FACTION_SIDE::PLAYER);
		temp->set_duration(0.5);
		//successful attack
	}
}

void MinionHealer::update_state()
{
	if (this->health <= 0)
	{
		this->current_state = DEAD;
		return;
	}
	//kena Cc, cannot perform normal actions
	if (this->is_CCed)
		return;
	if (ally_target->size() == 0)
	{
		nearest_target = nullptr;
		this->current_state = WALK;
		return;
	}
	this->find_nearest_target(this->pos, this->scale);
}

void MinionHealer::find_nearest_target(Vector3 & pos, Vector3 & scale)
{
	if (this->can_attack() == false)
	{
		this->current_state = WALK;
		return;
	}

	//finding nearest target
	Collision temp;
	temp.setCollisionType(Collision::CollisionType::SPHERE);
	temp.mid = &pos;
	temp.radius = (scale.x * 0.5f) * attack_range * 1.1f;//1.1 is da offset

	for each (auto &target in *ally_target)
	{
		if (target->check_collision(temp))
		{
			//now set as attack the first one if first one is inside
			this->current_state = ATTACK;
			nearest_target = &target->pos;
			if (dynamic_cast<Minion*>(target))
				break;//if the target is minion, break
		}
		else
		{
			//nothing in range
			this->current_state = WALK;
			nearest_target = nullptr;
		}
	}
}

void MinionHealer::set_faction_side(Faction::FACTION_SIDE side)
{
	this->Collidable::set_faction_side(side);

	if (side == Faction::FACTION_SIDE::PLAYER)
	{
		mesh_state[MinionInfo::STATE::DEAD] = nullptr;
		mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("#OBLACKDRAGON");
		mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("#OBLACKATTACK");
		mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("#OBLACKDRAGON");
	}
	else
	{
		mesh_state[MinionInfo::STATE::DEAD] = nullptr;
		mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("BLACKDRAGON");
		mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("BLACKATTACK");
		mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("BLACKDRAGON");
	}

}

void MinionHealer::walk(double dt)
{
	//this shall not walk infront of first ally

	//find its home position
	Vector3 home_pos;
	if (this->get_faction_side() == Faction::FACTION_SIDE::PLAYER)
		home_pos = TowerManager::GetInstance()->player->pos;
	else
		home_pos = TowerManager::GetInstance()->enemy->pos;

	//initialize furthest guy's pos as float limit
	Vector3 furthest_pos(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	float furthest_pos_distsq = -std::numeric_limits<float>::max();
	//iterate through all the allies and see which one is furthest from base
	for each (auto &ally in *ally_target)
	{
		Minion* ally_minion = dynamic_cast<Minion*>(ally);
		if (ally_minion)
		{
			if (ally_minion == this)
				continue;

			float distance = (ally_minion->pos.x - home_pos.x);//no need length coz its linear!
			if (distance < 0)
				distance = -distance;
			if (distance > furthest_pos_distsq)
			{
				furthest_pos = ally_minion->pos;
				furthest_pos_distsq = distance;
			}
		}
	}

	//if no suitable ally found, byebye and use default movement
	if (furthest_pos_distsq == -std::numeric_limits<float>::max())
	{
		this->pos += this->move_direction * this->get_move_speed() * (float)dt;
		return;
	}

	float distancesq_from_home = (this->pos.x - home_pos.x);
	if (distancesq_from_home < 0)
		distancesq_from_home = -distancesq_from_home;
	if (distancesq_from_home > furthest_pos_distsq)
		return;//dont move if went too far.
	

	this->pos += this->move_direction * this->get_move_speed() * (float)dt;
}
