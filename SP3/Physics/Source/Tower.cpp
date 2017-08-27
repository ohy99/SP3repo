#include "Tower.h"

#include "HpBar.h"
#include "MyMath.h"
#include "TowerManager.h"
#include "ShowHpManager.h"

Tower::Tower()
{
	this->active = true;
	
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
}

Tower::~Tower()
{
}

void Tower::render()
{
	GameObject::render();

	HpBar* hp = HpBar::GetInstance();
	hp->pos = this->pos;
	hp->pos.y += this->scale.y * 0.55f;
	hp->scale.Set(this->scale.x, 1);
	hp->render((float)this->health / (float)this->maxhealth);
}

void Tower::get_hit(int dmg)
{
	
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