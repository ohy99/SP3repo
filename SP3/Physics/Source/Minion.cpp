#include "Minion.h"

#include "Tower.h"
#include "MinionManager.h"
#include "DamageArea.h"
#include "Projectile.h"
#include "ObjectPoolManager.h"
#include "PhysicsManager.h"
#include "HpBar.h"
#include "Collidable.h"
#include "ShowHpManager.h"

Minion::Minion()
{
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

Minion::~Minion()
{
}

void Minion::update(double dt)
{
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("GREENDRAGON"));
	if (sa)
	{

		sa->Update(dt);
		sa->m_anim->animActive = true;
	}
	SpriteAnimation* sa2 = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("GREENATTACK"));
	if (sa2)
	{

		sa2->Update(dt);
		sa2->m_anim->animActive = true;
	}
	this->prev_pos = this->pos;
	this->update_info(dt);
	this->update_state();

	respond_to_state(dt);
}

void Minion::respond_to_state(double dt)
{
	this->mesh = mesh_state[current_state];
	switch (current_state)
	{
	case STATE::DEAD:
		this->active = false;
		break;
	case STATE::WALK:
		this->pos += this->move_direction * this->get_move_speed() * (float)dt;
		break;
	case STATE::ATTACK:
		attack();
		break;
	case STATE::KNOCKBACK:
	{
		this->knockback_elapsed += dt;
		if (this->knockback_elapsed < this->knockback_duration)
			this->pos += this->knockback_direction * this->knockback_force * (float)dt;
		else
		{
			this->current_state = STATE::WALK;
			this->knockback_elapsed = 0.0;
			this->is_CCed = false;
		}
		break;
	}
	}
}

void Minion::attack()
{
	//virtual will take care.
}

void Minion::update_state()
{
	if (this->health <= 0)
	{
		this->current_state = DEAD;
		return;
	}
	//kena Cc, cannot perform normal actions
	if (this->is_CCed)
		return;
	if (enemy_target->size() == 0)
	{
		nearest_target = nullptr;
		this->current_state = WALK;
		return;
	}
	this->find_nearest_target(this->pos, this->scale);
}


void Minion::get_hit(int dmg)
{
	this->health = Math::Clamp(health - dmg, 0, max_health);
	ShowHpManager::GetInstance()->generate_hp_text(this->pos + Vector3(0, this->scale.y * 0.5f, 0), dmg);
}

void Minion::collision_response(Collidable * obj)
{
	Minion* temp_minion = dynamic_cast<Minion*>(obj);
	Tower* temp_tower = dynamic_cast<Tower*>(obj);
	if (temp_minion)//stop when hit any minion
	{
		Vector3 relativepos = obj->pos - this->pos;
		if (this->move_direction.Dot(relativepos) > 0)
		{
			this->pos = prev_pos;//collded with obj infront of me, so i stop
			//if i kena knockback but i hit tio other minion, i stop too
			//at least 0.5f cc time
			if (this->current_state == MinionInfo::STATE::KNOCKBACK && knockback_elapsed >= 0.5)
			{
				this->current_state = MinionInfo::STATE::WALK;
				this->is_CCed = false;
			}
		}
	}
	else if (temp_tower)
		if (this->get_faction_side() != obj->get_faction_side())
			this->pos = prev_pos;
}

void Minion::render()
{
	GameObject::render();

	HpBar* hp = HpBar::GetInstance();
	hp->pos = this->pos;
	hp->pos.y += this->scale.y;
	hp->scale.Set(this->scale.x, 1);
	hp->render((float)this->health / (float)this->max_health);
}
