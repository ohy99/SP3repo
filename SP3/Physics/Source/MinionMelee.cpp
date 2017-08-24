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
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("BROWNDRAGON"));
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 5, 1, 10.0f, true);
	}
	SpriteAnimation* sa2 = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("BROWNATTACK"));
	if (sa2)
	{
		sa2->m_anim = new Animation();
		sa2->m_anim->Set(0, 5, 1, 10.0f, true);
	}
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
