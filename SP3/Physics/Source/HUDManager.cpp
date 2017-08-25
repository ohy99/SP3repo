#include "HUDManager.h"

#include "MeshList.h"
#include "Graphics.h"
#include "RenderHelper.h"
#include "SpellManager.h"

HUDManager::HUDManager()
{
	HUDTHING = MeshList::GetInstance()->getMesh("REDHPBAR");
	Spell1 = MeshList::GetInstance()->getMesh("lightning");
	Spell2 = MeshList::GetInstance()->getMesh("freeze");
	Spell3 = MeshList::GetInstance()->getMesh("blast");
	//Spell4 = MeshList::GetInstance()->getMesh("blast");
	Ulti = MeshList::GetInstance()->getMesh("blast");
	cooldown = MeshList::GetInstance()->getMesh("GREENHPBAR");
}

HUDManager::~HUDManager()
{
}

void HUDManager::update(double dt)
{
}

void HUDManager::render()
{
	//LIGHTNING
	MS& ms = Graphics::GetInstance()->modelStack;
	ms.PushMatrix();
	ms.Translate(30, 6, 10);
	ms.Scale(5, 5, 5);
	RenderHelper::RenderMesh(Spell1, false);

	if (SpellManager::GetInstance()->getLcooldown() < 1.0)
	{
		ms.PushMatrix();
		ms.Translate(0, -(1.0 - SpellManager::GetInstance()->getLcooldown()) * 0.5f, 0);
		ms.Scale(1, SpellManager::GetInstance()->getLcooldown(), 1);//.y 0-1
		RenderHelper::RenderMesh(cooldown, false);
		ms.PopMatrix();
	}

	ms.PopMatrix();

	//FREEZE
	ms.PushMatrix();
	ms.Translate(40, 6, 10);
	ms.Scale(5, 5, 5);
	RenderHelper::RenderMesh(Spell2, false);

	if (SpellManager::GetInstance()->getFcooldown() < 1.0)
	{
		ms.PushMatrix();
		ms.Translate(0, -(1.0 - SpellManager::GetInstance()->getFcooldown()) * 0.5f, 0);
		ms.Scale(1, SpellManager::GetInstance()->getFcooldown(), 1);//.y 0-1
		RenderHelper::RenderMesh(cooldown, false);
		ms.PopMatrix();
	}

	ms.PopMatrix();

	//FIRE
	ms.PushMatrix();
	ms.Translate(50, 6, 10);
	ms.Scale(5, 5, 5);
	RenderHelper::RenderMesh(Spell3, false);

	if (SpellManager::GetInstance()->getBcooldown() < 1.0)
	{
		ms.PushMatrix();
		ms.Translate(0, -(1.0 - SpellManager::GetInstance()->getBcooldown()) * 0.5f, 0);
		ms.Scale(1, SpellManager::GetInstance()->getBcooldown(), 1);//.y 0-1
		RenderHelper::RenderMesh(cooldown, false);
		ms.PopMatrix();
	}

	ms.PopMatrix();



}

