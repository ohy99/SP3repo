#include "HUDManager.h"

#include "MeshList.h"
#include "Graphics.h"
#include "RenderHelper.h"
#include "SpellManager.h"
#include "TowerManager.h"
#include "Tower.h"
#include "ShowHpManager.h"
#include "CharacterInfo.h"

HUDManager::HUDManager()
{
	HUDTHING = MeshList::GetInstance()->getMesh("SPELLHUD");
	Spell1 = MeshList::GetInstance()->getMesh("lightning");
	Spell2 = MeshList::GetInstance()->getMesh("freeze");
	Spell3 = MeshList::GetInstance()->getMesh("blast");
	//Spell4 = MeshList::GetInstance()->getMesh("blast");
	Ulti_Bar = MeshList::GetInstance()->getMesh("chargeborder");
	Ulti_Charge = MeshList::GetInstance()->getMesh("charge");
	cooldown = MeshList::GetInstance()->getMesh("cooldown");
	ulti_ready_mesh = MeshList::GetInstance()->getMesh("ULTIREADY");

	ultbarpos = TowerManager::GetInstance()->player->pos;
	ultbarpos.y += TowerManager::GetInstance()->player->scale.y * 0.6f;
	ultbarscale.Set(0.8f * TowerManager::GetInstance()->player->scale.x, 0.5f, 1);

	ulti_ready_text = "Ulti Ready!";
	ulti_ready_scale.Set(10, 3, 0);
	ulti_ready_dir.Set(0, 1, 0);
	ulti_ready_color.Set(1, 0, 1);
	ulti_ready_pos.Set(ultbarscale.x *0.5f + ulti_ready_scale.x * 0.5f,
		0, 0);
	ulti_charge_percent = 0.f;
	ulti_ready_rotate = 0.f;
	ulti_ready_rotate_speed = 90.f;
	ulti_ready_rotate_limit = 10.f;

	brownd = MeshList::GetInstance()->getMesh("BROWNDRAGON");
	blued = MeshList::GetInstance()->getMesh("BLUEDRAGON");
	greend = MeshList::GetInstance()->getMesh("GREENDRAGON");
	blackd = MeshList::GetInstance()->getMesh("BLACKDRAGON");

	repair = MeshList::GetInstance()->getMesh("repair");

	character = nullptr;
}

HUDManager::~HUDManager()
{
}


void HUDManager::update(double dt)
{
	ulti_charge_percent = SpellManager::GetInstance()->get_longkang_charge();
	static bool turn_positive = true;
	if (ulti_charge_percent >= 1.f)
	{
		if (turn_positive)
		{
			ulti_ready_rotate += ulti_ready_rotate_speed * (float)dt;
			if (ulti_ready_rotate > ulti_ready_rotate_limit)
			{
				ulti_ready_rotate = ulti_ready_rotate_limit;
				turn_positive = false;
			}
		}
		else
		{
			ulti_ready_rotate -= ulti_ready_rotate_speed * (float)dt;
			if (ulti_ready_rotate < -ulti_ready_rotate_limit)
			{
				ulti_ready_rotate = -ulti_ready_rotate_limit;
				turn_positive = true;
			}
		}

		//Mtx44 rotation;
		//rotation.SetToRotation(ulti_ready_rotate, 0, 0, 1);
		//ulti_ready_dir
	}
	else
	{
		//keep things reseted
		turn_positive = true;
		ulti_ready_rotate = 0.f;
	}
}

void HUDManager::render()
{
	//LIGHTNING
	MS& ms = Graphics::GetInstance()->modelStack;
	ms.PushMatrix();
	ms.Translate(30, 6, 10);
	ms.Scale(17.f, 6.f, 15);
	RenderHelper::RenderMesh(HUDTHING, false);
	ms.PopMatrix();

	if (SpellManager::GetInstance()->getLcooldown() < 1.0)
	{
		ms.PushMatrix();
		ms.Translate(35.5, 6, 10);
		ms.Scale(5.f, 5.f, 15);
		ms.Translate(0, -(1.0 - SpellManager::GetInstance()->getLcooldown()) * 0.5f, 0);
		ms.Scale(1, SpellManager::GetInstance()->getLcooldown(), 1);//.y 0-1
		RenderHelper::RenderMesh(cooldown, false);
		ms.PopMatrix();
	}

	if (SpellManager::GetInstance()->getFcooldown() < 1.0)
	{
		ms.PushMatrix();
		ms.Translate(30, 6, 10);
		ms.Scale(5.f, 5.f, 15);
		ms.Translate(0, -(1.0 - SpellManager::GetInstance()->getFcooldown()) * 0.5f, 0);
		ms.Scale(1, SpellManager::GetInstance()->getFcooldown(), 1);//.y 0-1
		RenderHelper::RenderMesh(cooldown, false);
		ms.PopMatrix();
	}

	if (SpellManager::GetInstance()->getBcooldown() < 1.0)
	{
		ms.PushMatrix();
		ms.Translate(24.5, 6, 10);
		ms.Scale(5.f, 5.f, 15);
		ms.Translate(0, -(1.0 - SpellManager::GetInstance()->getBcooldown()) * 0.5f, 0);
		ms.Scale(1, SpellManager::GetInstance()->getBcooldown(), 1);//.y 0-1
		RenderHelper::RenderMesh(cooldown, false);
		ms.PopMatrix();
	}


	render_ulti_bar();

	int column = 0;
	Vector3 spacing(5, 0, 0);
	Vector3 offset(5, 50, 0);
	Vector3 scale(5, 5, 1);
	Color color(1, 1, 1);
	FontType& font = ShowHpManager::GetInstance()->get_calibri();
	ms.PushMatrix();
	ms.Translate(offset);

	ms.PushMatrix();
	ms.Translate(spacing.x * column++, spacing.y, 0);
	ms.PushMatrix();
	ms.Scale(scale * 0.5f);
	RenderHelper::RenderMesh(repair, false);
	ms.PopMatrix();
	ms.Translate(-scale.x * 0.25f, -scale.y * 0.5f, 0);
	ms.Scale(scale);
	RenderHelper::RenderText(&font, std::to_string(character->getWallet().getsmallrepair()), color);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(spacing.x * column++, spacing.y, 0);
	ms.PushMatrix();
	ms.Scale(scale * 0.75f);
	RenderHelper::RenderMesh(repair, false);
	ms.PopMatrix();
	ms.Translate(-scale.x * 0.25f, -scale.y * 0.5f, 0);
	ms.Scale(scale);
	RenderHelper::RenderText(&font, std::to_string(character->getWallet().getmediumrepair()), color);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(spacing.x * column++, spacing.y, 0);
	ms.PushMatrix();
	ms.Scale(scale);
	RenderHelper::RenderMesh(repair, false);
	ms.PopMatrix();
	ms.Translate(-scale.x * 0.25f, -scale.y * 0.5f, 0);
	ms.Scale(scale);
	RenderHelper::RenderText(&font, std::to_string(character->getWallet().getbigrepair()), color);
	ms.PopMatrix();

	//MINIONS
	ms.PushMatrix();
	ms.Translate(spacing.x * column++, spacing.y, 0);
	ms.PushMatrix();
	ms.Scale(scale);
	RenderHelper::RenderMesh(brownd, false);
	ms.PopMatrix();
	ms.Translate(-scale.x * 0.25f, -scale.y * 0.5f, 0);
	ms.Scale(scale);
	RenderHelper::RenderText(&font, std::to_string(character->getWallet().getbrowndrake()), color);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(spacing.x * column++, spacing.y, 0);
	ms.PushMatrix();
	ms.Scale(scale);
	RenderHelper::RenderMesh(blued, false);
	ms.PopMatrix();
	ms.Translate(-scale.x * 0.25f, -scale.y * 0.5f, 0);
	ms.Scale(scale);
	RenderHelper::RenderText(&font, std::to_string(character->getWallet().getbluedrake()), color);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(spacing.x * column++, spacing.y, 0);
	ms.PushMatrix();
	ms.Scale(scale);
	RenderHelper::RenderMesh(greend, false);
	ms.PopMatrix();
	ms.Translate(-scale.x * 0.25f, -scale.y * 0.5f, 0);
	ms.Scale(scale);
	RenderHelper::RenderText(&font, std::to_string(character->getWallet().getgreendrake()), color);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(spacing.x * column++, spacing.y, 0);
	ms.PushMatrix();
	ms.Scale(scale);
	RenderHelper::RenderMesh(blackd, false);
	ms.PopMatrix();
	ms.Translate(-scale.x * 0.25f, -scale.y * 0.5f, 0);
	ms.Scale(scale);
	RenderHelper::RenderText(&font, std::to_string(character->getWallet().getblackdrake()), color);
	ms.PopMatrix();


	ms.PopMatrix();//End offset
}

void HUDManager::render_ulti_bar()
{

	MS& ms = Graphics::GetInstance()->modelStack;
	ms.PushMatrix();
	ms.Translate(ultbarpos);
	//Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)) - 90.f, 0, 0, 1);
	ms.PushMatrix();
	ms.Scale(ultbarscale);
	RenderHelper::RenderMesh(Ulti_Bar, false);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(-(1.f - ulti_charge_percent) * ultbarscale.x * 0.5f, 0, 0);
	ms.Scale(ulti_charge_percent * ultbarscale.x, ultbarscale.y, ultbarscale.z);
	RenderHelper::RenderMesh(Ulti_Charge, false);
	ms.PopMatrix();

	//special text
	if (ulti_charge_percent >= 1.0f)
	{
		ms.PushMatrix();
		ms.Translate(ulti_ready_pos);
		ms.Rotate(ulti_ready_rotate, 0, 0, 1);
		ms.Scale(ulti_ready_scale);
		RenderHelper::RenderMesh(ulti_ready_mesh, false);
		ms.PopMatrix();
	}
	ms.PopMatrix();

}
