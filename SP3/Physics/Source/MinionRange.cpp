#include "MinionRange.h"

#include "MeshList.h"
#include "SpriteAnimation.h"
#include "Projectile.h"
#include "ObjectPoolManager.h"
#include "PhysicsManager.h"

MinionRange::MinionRange()
{
	this->minion_type = MinionInfo::MINION_TYPE::BASIC_RANGE;
	mesh_state[MinionInfo::STATE::DEAD] = nullptr;
	mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("BLUEDRAGON");
	mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("BLUEATTACK");
	mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("BLUEDRAGON");
}

MinionRange::~MinionRange()
{
}

void MinionRange::attack()
{
	//check if there is eligible target. if no, then return
	if (nearest_target == nullptr)
		return;
	if (this->can_attack() == false)
		return;

	Projectile* temp = ObjectPoolManager::GetInstance()->get_projectile(ObjectPoolManager::PROJECTILE_TYPE::CANNONBALL);
	if (temp)
	{
		temp->active = true;
		temp->pos = this->pos;
		temp->set_dmg(this->get_attack_damage());
		temp->set_faction_side(this->get_faction_side());
		temp->velocity.Set(this->move_direction.x * 7.5f, 0, 0);
		//calculate needed y-vel to reach target
		Vector3 displacement = *nearest_target - this->pos;
		float time_to_hit = displacement.x / 7.5f;
		if (time_to_hit <= 0)
			time_to_hit = -time_to_hit;
		temp->velocity.y = time_to_hit * 0.5f * -PhysicsManager::GetInstance()->get_gravity().y;
		//this->reset_attack();
	}
}
