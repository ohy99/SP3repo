#include "Tower.h"

#include "HpBar.h"
#include "MyMath.h"
#include "TowerManager.h"
#include "ShowHpManager.h"
#include "RenderManager.h"
#include "Application.h"
#include "GameLogic.h"
#include "Graphics.h"
#include <sstream>

Tower::Tower()
{
	this->active = true;
	this->dmg_reduction = 0.f;
	show_stats_info = false;
	stats_info_pos.SetZero();
}

Tower::Tower(Faction::FACTION_SIDE side)
{
	this->active = true;
	this->set_faction_side(side);

	this->maxhealth = 1000;
	this->health = this->maxhealth;
	audioPlayer.playlist.push_back(new Sound("Audio//Towerhit.mp3"));
	if (side == Faction::FACTION_SIDE::PLAYER)
		TowerManager::GetInstance()->player = this;
	else
		TowerManager::GetInstance()->enemy = this;

	this->dmg_reduction = 0.f;
	show_stats_info = false;
	stats_info_pos.SetZero();
}

Tower::~Tower()
{
}

void Tower::update(double dt)
{
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

void Tower::render()
{
	GameObject::render();

	HpBar* hp = HpBar::GetInstance();
	hp->pos = this->pos;
	hp->pos.y += this->scale.y * 0.55f;
	hp->scale.Set(this->scale.x, 1);
	hp->render((float)this->health / (float)this->maxhealth);

	if (show_stats_info) {
		if (this->pos.x > 50)//at right side
			show_stats(stats_info_pos, false);
		else
			show_stats(stats_info_pos, true);
		RenderManager::GetInstance()->render_this_last(this);
	}
}

void Tower::get_hit(int dmg)
{
	dmg = (int)((float)dmg * (1.f - dmg_reduction));
	this->health = Math::Clamp(health - dmg, 0, maxhealth);
	if (dmg > 0)
	{
		audioPlayer.playSoundThreaded(audioPlayer.playlist[0]->fileName_);
	}
	ShowHpManager::GetInstance()->generate_hp_text(this->pos + Vector3(0, this->scale.y * 0.5f, 0), dmg);
	//check if hp is good or bad
	if (this->health <= 0.25f * this->maxhealth)
		this->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER25");
	else if (this->health <= 0.5f * this->maxhealth)
		this->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER50");
	else if (this->health <= 0.75f * this->maxhealth)
		this->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER75");
	else
		this->mesh = MeshList::GetInstance()->getMesh("PLAYERTOWER");
}

void Tower::set_dmg_reduction(float value)
{
	this->dmg_reduction = Math::Clamp(value, 0.f, 1.f);
}

float Tower::get_dmg_reduction()
{
	return this->dmg_reduction;
}


void Tower::show_stats(Vector3 pos, bool render_right)
{
	static Vector3 statscale(8.5f, 8.5f, 1);
	FontType& font = ShowHpManager::GetInstance()->get_calibri();
	static Vector3 fontscale(1.35f, 1.35f, 1);
	//static float addition_row_x = statscale.x * 0.8f;
	static Color default_color(0.f, 0.f, 0.f);
	//static Color changed_color(0.15f, 0.15f, 0.15f);
	static Vector3 default_offset(statscale.x * 0.025f, -statscale.y * 0.0f, 0);
	//static Vector3 changed_offset(statscale.x * 0.4f, -statscale.y * 0.0f, 0);
	//static Vector3 addition_offset(statscale.x * 0.76f, -statscale.y * 0.0f, 0);
	//static Color positive_color(0, 1, 0);
	//static Color negative_color(1, 0, 0);
	//float difference = 0;
	int textrow = 1;


	MS& ms = Graphics::GetInstance()->modelStack;
	ms.PushMatrix();
	//	ms.Translate(50,50,0);
	ms.Translate(pos.x, pos.y, 0);

	ms.PushMatrix();
	if (render_right)
		ms.Translate(statscale.x * 0.5f, -statscale.y * 0.5f, 0);
	else
		ms.Translate(-statscale.x * 0.5f, -statscale.y * 0.5f, 0);

	ms.PushMatrix();
	ms.Scale(statscale);
	RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("STATSCREEN"), false);
	ms.PopMatrix();

	ms.PopMatrix();

	ms.PushMatrix();
	if (render_right == false)
	ms.Translate(-statscale.x, 0, 0);
	//Offset from border
	ms.Translate(default_offset);

	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, "Tower: ", default_color);
	ms.PopMatrix();

	std::stringstream ss;
	ss << std::fixed;
	ss.precision(0);

	ss.str("");
	ss << "Hp : " << this->health << " / " << this->maxhealth;
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, ss.str(), default_color);
	ms.PopMatrix();

	ss.str("");
	ss << "Armor : " << 100.f / (1.f - this->dmg_reduction) - 100.f;
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, ss.str(), default_color);
	ms.PopMatrix();

	++textrow;
	ss.precision(2);
	ss.str("");
	ss << "Damage";
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, ss.str(), default_color);
	ms.PopMatrix();
	ss.str("");
	ss << "Reduction: " << this->dmg_reduction << "%";
	ms.PushMatrix();
	ms.Translate(0, -fontscale.y * textrow++, 0);
	ms.Scale(fontscale);
	RenderHelper::RenderText(&font, ss.str(), default_color);
	ms.PopMatrix();

	ms.PopMatrix();

	ms.PopMatrix();
}
