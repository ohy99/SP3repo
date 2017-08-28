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
#include "Application.h"
#include "GameLogic.h"
#include "ShowHpManager.h"
#include <sstream>

Minion::Minion()
{
	mesh_state[MinionInfo::STATE::DEAD] = nullptr;
	mesh_state[MinionInfo::STATE::WALK] = MeshList::GetInstance()->getMesh("GREENDRAGON");
	mesh_state[MinionInfo::STATE::ATTACK] = MeshList::GetInstance()->getMesh("GREENATTACK");
	mesh_state[MinionInfo::STATE::KNOCKBACK] = MeshList::GetInstance()->getMesh("GREENDRAGON");

	audioPlayer.playlist.push_back(new Sound("Audio//Dragondie.mp3"));
	attacked = false;


	animation.Set(0, 5, 1, this->move_speed, true);

	heal_elapsed = 0.0;
	heal_duration = 1.f;

	show_stats_info = false;
	stats_info_pos.SetZero();
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

	heal_elapsed = Math::Max(heal_elapsed - dt, 0.0);

	float worldWidth, worldHeight;
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	//static bool keypressed = false;
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);
	Collision cursor_collider;
	cursor_collider.collisionType = Collision::POINT;
	cursor_collider.mid = &cursor_point_in_world_space;
	if (this->collider.isCollide(cursor_collider))
	{
		//show_stats(cursor_point_in_world_space);
		show_stats_info = true;
		stats_info_pos = cursor_point_in_world_space;
	}
	else
		show_stats_info = false;
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
		walk(dt);
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

void Minion::walk(double dt)
{
	this->pos += this->move_direction * this->get_move_speed() * (float)dt;
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
		
	if (dmg < 0)
		heal_elapsed = heal_duration;
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

	if (heal_elapsed > 0.0)
	{
		ms.PushMatrix();
		ms.Translate(this->pos);
		ms.Scale(this->scale * 0.8f);
		RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("HEAL"), false);
		ms.PopMatrix();
	}

	if (show_stats_info) {
		show_stats(this->pos);
		RenderManager::GetInstance()->render_this_last(this);
	}
}

void Minion::show_stats(Vector3 pos)
{
	static Vector3 statscale(11.f, 8.5f, 1);
	FontType& font = ShowHpManager::GetInstance()->get_calibri();
	static Vector3 fontscale(1.35f, 1.35f, 1);
	static float addition_row_x = statscale.x * 0.8f;
	static Color default_color(0.f, 0.f, 0.f);
	static Color changed_color(0.15f, 0.15f, 0.15f);
	static Vector3 default_offset(statscale.x * 0.025f, -statscale.y * 0.0f, 0);
	static Vector3 changed_offset(statscale.x * 0.4f, -statscale.y * 0.0f, 0);
	static Vector3 addition_offset(statscale.x * 0.76f, -statscale.y * 0.0f, 0);
	static Color positive_color(0, 1, 0);
	static Color negative_color(1, 0, 0);
	float difference = 0;
	int textrow = 1;
	MinionManager::MINION_INFO info = MinionManager::GetInstance()->get_info(this->minion_type);
	MinionManager::MINION_INFO default_info = MinionManager::GetInstance()->get_default_info(this->minion_type);

	MS& ms = Graphics::GetInstance()->modelStack;
	ms.PushMatrix();
//	ms.Translate(50,50,0);
	ms.Translate(pos.x, pos.y, 0);

	ms.PushMatrix();
	ms.Translate(statscale.x * 0.5f, -statscale.y * 0.5f, 0);
	ms.PushMatrix();
	ms.Scale(statscale);
	RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("STATSCREEN"), false);
	ms.PopMatrix();
	//ms.PushMatrix();
	//ms.Scale(statscale * 1.1f);
	//RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("STATBORDER"), false);
	//ms.PopMatrix();
	ms.PopMatrix();

	ms.PushMatrix();
	//Offset from border
	ms.Translate(default_offset);

	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "Default", default_color);
	ms.PopMatrix();

	std::stringstream ss;
	ss << std::fixed;
	ss.precision(1);

	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++,0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "Hp : " + std::to_string(default_info.max_hp), default_color);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "Dmg: " + std::to_string(default_info.dmg), default_color);
	ms.PopMatrix();

	ss.str("");
	ss << default_info.att_spd;
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "AS : " + ss.str(), default_color);
	ms.PopMatrix();

	ss.str("");
	ss << default_info.att_range;
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "AR : " + ss.str(), default_color);
	ms.PopMatrix();

	ss.str("");
	ss << default_info.move_spd;
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "MS : " + ss.str(), default_color);
	ms.PopMatrix();

	ms.PopMatrix();
	
	ms.PushMatrix();
	ms.Translate(changed_offset);
	//CHANGED VALUES
	textrow = 1;
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "Season", changed_color);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.PushMatrix();
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "Hp : " + std::to_string(info.max_hp), changed_color);
	ms.PopMatrix();
	difference = info.max_hp - default_info.max_hp;
	if (difference != 0.f)
	{
		ss.str("");
		ss << difference;
		ms.PushMatrix();
		ms.Translate(-changed_offset);
		ms.Translate(addition_offset);
		ms.Scale(fontscale);
		RenderHelper::RenderText(&font, (difference > 0.f ? "+" : "") + ss.str(), (difference > 0.f ? positive_color : negative_color));
		ms.PopMatrix();
	}

	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.PushMatrix();
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "Dmg: " + std::to_string(info.dmg), changed_color);
	ms.PopMatrix();
	difference = info.dmg - default_info.dmg;
	if (difference != 0.f)
	{
		ss.str("");
		ss << difference;
		ms.PushMatrix();
		ms.Translate(-changed_offset);
		ms.Translate(addition_offset);
		ms.Scale(fontscale);
		RenderHelper::RenderText(&font, (difference > 0.f ? "+" : "") + ss.str(), (difference > 0.f ? positive_color : negative_color));
		ms.PopMatrix();
	}
	ms.PopMatrix();

	ss.str("");
	ss << info.att_spd;
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.PushMatrix();
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "AS : " + ss.str(), changed_color);
	ms.PopMatrix();
	difference = info.att_spd - default_info.att_spd;
	if (difference != 0.f)
	{
		ss.str("");
		ss << difference;
		ms.PushMatrix();
		ms.Translate(-changed_offset);
		ms.Translate(addition_offset);
		ms.Scale(fontscale);
		RenderHelper::RenderText(&font, (difference > 0.f ? "+" : "") + ss.str(), (difference > 0.f ? positive_color : negative_color));
		ms.PopMatrix();
	}
	ms.PopMatrix();

	ss.str("");
	ss << info.att_range;
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.PushMatrix();
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "AR : " + ss.str(), changed_color);
	ms.PopMatrix();
	difference = info.att_range - default_info.att_range;
	if (difference != 0.f)
	{
		ss.str("");
		ss << difference;
		ms.PushMatrix();
		ms.Translate(-changed_offset);
		ms.Translate(addition_offset);
		ms.Scale(fontscale);
		RenderHelper::RenderText(&font, (difference > 0.f ? "+" : "") + ss.str(), (difference > 0.f ? positive_color : negative_color));
		ms.PopMatrix();
	}
	ms.PopMatrix();

	ss.str("");
	ss << info.move_spd;
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);

	ms.PushMatrix();
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "MS : " + ss.str(), changed_color);
	ms.PopMatrix();

	difference = info.move_spd - default_info.move_spd;
	if (difference != 0.f)
	{
		ss.str("");
		ss << difference;
		ms.PushMatrix();
		ms.Translate(-changed_offset);
		ms.Translate(addition_offset);
		ms.Scale(fontscale);
		RenderHelper::RenderText(&font, (difference > 0.f ? "+" : "") + ss.str(), (difference > 0.f ? positive_color : negative_color));
		ms.PopMatrix();
	}
	ms.PopMatrix();

	ms.PopMatrix();

	ms.PopMatrix();
}