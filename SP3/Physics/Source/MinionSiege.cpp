#include "MinionSiege.h"

#include "MeshList.h"
#include "SpriteAnimation.h"
#include "Projectile.h"
#include "ObjectPoolManager.h"
#include "PhysicsManager.h"

MinionSiege::MinionSiege()
{
	this->minion_type = MinionInfo::MINION_TYPE::BASIC_SIEGE;
	mesh_state[MinionInfo::STATE::DEAD] = nullptr;
	mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("GREENDRAGON");
	mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("GREENATTACK");
	mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("GREENDRAGON");
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("GREENDRAGON"));
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 5, 1, 10.0f, true);
	}
	SpriteAnimation* sa2 = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("GREENATTACK"));
	if (sa2)
	{
		sa2->m_anim = new Animation();
		sa2->m_anim->Set(0, 5, 1, 10.0f, true);
	}
}

MinionSiege::~MinionSiege()
{
}

void MinionSiege::attack()
{
	if (nearest_target == nullptr)
		return;
	if (this->can_attack() == false)
		return;

	Projectile* temp = ObjectPoolManager::GetInstance()->get_projectile(ObjectPoolManager::PROJECTILE_TYPE::CANNONBALL);
	if (temp)
	{
		static float x_vel = 5.f;
		temp->active = true;
		temp->pos = this->pos;
		temp->set_dmg(this->get_attack_damage());
		temp->set_faction_side(this->get_faction_side());
		temp->velocity.Set(this->move_direction.x * x_vel, 0, 0);
		//calculate needed y-vel to reach target
		Vector3 displacement = *nearest_target - this->pos;
		float time_to_hit = displacement.x / x_vel;
		if (time_to_hit <= 0)
			time_to_hit = -time_to_hit;
		temp->velocity.y = time_to_hit * 0.5f * -PhysicsManager::GetInstance()->get_gravity().y;
		//this->reset_attack();
	}
}
