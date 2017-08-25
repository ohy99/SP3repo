#include "MinionHealer.h"

#include "MeshList.h"
#include "SpriteAnimation.h"
#include "DamageArea.h"
#include "MinionManager.h"

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
		temp->pos.Set(this->pos.x + (this->move_direction * this->scale.x * 0.5f).x,
			this->pos.y, this->pos.z);
		temp->set_collision_type(Collision::CollisionType::SPHERE);
		temp->scale.Set(this->attack_range * this->scale.x * 0.5f,
			this->attack_range * this->scale.x * 0.5f);
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
