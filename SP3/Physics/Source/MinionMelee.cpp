#include "MinionMelee.h"

#include "DamageArea.h"
#include "MinionManager.h"
#include "MeshList.h"
#include "SpriteAnimation.h"

MinionMelee::MinionMelee()
{
	this->minion_type = MinionInfo::MINION_TYPE::BASIC_MELEE;
	mesh_state[MinionInfo::STATE::DEAD] = nullptr;
	mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("BROWNDRAGON");
	mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("BROWNATTACK");
	mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("BROWNDRAGON");

}

MinionMelee::~MinionMelee()
{
}

void MinionMelee::attack()
{
	if (nearest_target == nullptr)
		return;
	if (this->can_attack() == false)
		return;

	DamageArea* temp = MinionManager::GetInstance()->request_inactive_collidable(MINION_TYPE::BASIC_MELEE);
	if (temp)
	{
		temp->active = true;
		temp->mesh = MeshList::GetInstance()->getMesh("CANNONBALL");
		temp->pos.Set(this->pos.x + (this->move_direction * this->scale.x * 0.5f).x,
			this->pos.y, this->pos.z);
		temp->set_collision_type(Collision::CollisionType::AABB);
		temp->scale.Set(this->attack_range * this->scale.x * 0.5f, 
			this->attack_range * this->scale.x * 0.5f);
		temp->update_collider();
		temp->set_damage(this->get_attack_damage());
		temp->set_faction_side(this->get_faction_side());
		temp->set_duration(0.5f);
		//successful attack
		//this->reset_attack();
	}
}

void MinionMelee::set_faction_side(Faction::FACTION_SIDE side)
{
	this->Collidable::set_faction_side(side);

	switch (side)
	{
	case Faction::FACTION_SIDE::PLAYER:
		mesh_state[MinionInfo::STATE::DEAD] = nullptr;
		mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("#OBROWNDRAGON");
		mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("#OBROWNATTACK");
		mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("#OBROWNDRAGON");
		break;
	default:
		mesh_state[MinionInfo::STATE::DEAD] = nullptr;
		mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("BROWNDRAGON");
		mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("BROWNATTACK");
		mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("BROWNDRAGON");
	}
}
