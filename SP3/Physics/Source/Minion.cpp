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
#include "CharacterInfo.h"

Minion::Minion()
{
	mesh_state[MinionInfo::STATE::DEAD] = nullptr;
	mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("GREENDRAGON");
	mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("GREENATTACK");
	mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("GREENDRAGON");

	audioPlayer.playlist.push_back(new Sound("Audio//Dragondie.mp3"));
	attacked = false;


	animation.Set(0, 5, 1, this->move_speed, true);
}

Minion::~Minion()
{
}

void Minion::update(double dt)
{
	//anim_time += (float)dt;
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(mesh_state[current_state]);
	if (sa)
	{
		sa->m_anim = &this->animation;
		sa->Update(dt);
	}
	//SpriteAnimation* sa2 = dynamic_cast<SpriteAnimation*>(mesh_state[current_state]);
	//if (sa2)
	//{
	//	sa2->Update(dt);
	//	sa2->m_anim->animActive = true;
	//	sa->m_anim->animTime = anim_time;
	//}
	MinionInfo::STATE prev_state = current_state;
	this->prev_pos = this->pos;
	this->update_info(dt);
	this->update_state();
	if (prev_state != current_state)
	{
		animation.m_currentTime = 0.f;
		if (current_state == MinionInfo::STATE::ATTACK)
			animation.Set(0, 5, 1, this->cast_time, true);
		else
			animation.Set(0, 5, 1, this->move_speed, true);
	}

	respond_to_state(dt);
}

void Minion::respond_to_state(double dt)
{
	this->mesh = mesh_state[current_state];
	switch (current_state)
	{
	case STATE::DEAD:
		this->active = false;
		audioPlayer.playSoundThreaded(audioPlayer.playlist[0]->fileName_);
		break;
	case STATE::WALK:
		this->pos += this->move_direction * this->get_move_speed() * (float)dt;
		break;
	case STATE::ATTACK:
		//wait 0.5
		//std::cout << cast_elapsed << std::endl;
		if (cast_elapsed >= cast_time * 0.5)
		{
			if (attacked == false)
			{
				attack();
				attacked = true;
			}
			if (cast_elapsed >= cast_time && attacked == true)
			{
				this->reset_attack();//reset attack delay
				attacked = false;
				cast_elapsed = 0.0;
				current_state = WALK;
			}
		}
		//0.5//finish the animation
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

	this->find_nearest_target(this->pos, this->scale);
}


void Minion::get_hit(int dmg)
{
	this->health = Math::Clamp(health - dmg, 0, max_health);
	ShowHpManager::GetInstance()->generate_hp_text(this->pos + Vector3(0, this->scale.y * 0.5f, 0), dmg);
	if (dmg > 0)
		if (this->get_faction_side() == Faction::FACTION_SIDE::ENEMY)
		{
			this->add_coin_to_character(dmg);
			this->send_damage_feedback_to_character(dmg, (this->health <= 0 ? true : false), this->max_health);
		}
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
	//GameObject::render();

	MS& ms = Graphics::GetInstance()->modelStack;
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(this->mesh);
	if (sa)
		sa->m_anim = &this->animation;
	ms.PushMatrix();
	ms.Translate(this->pos);
	ms.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)) - 90.f, 0, 0, 1);
	ms.Scale(this->scale);
	RenderHelper::RenderMesh(this->mesh, false);
	ms.PopMatrix();
	if (sa)
		sa->m_anim = nullptr;

	HpBar* hp = HpBar::GetInstance();
	hp->pos = this->pos;
	hp->pos.y += this->scale.y;
	hp->scale.Set(this->scale.x, 1);
	hp->render((float)this->health / (float)this->max_health);
}
