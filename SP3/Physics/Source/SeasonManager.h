#ifndef SEASONMANAGER_H
#define SEASONMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include "RenderHelper.h"
#include "Graphics.h"
#include "ObjectPoolManager.h"
#include "ParticleManager.h"
#include "MeshList.h"
#include "SpriteAnimation.h"
#include "MinionManager.h"
class Mesh;
class SeasonManager : public Singleton<SeasonManager>
{
public:
	enum SEASON_TYPE
	{
		WINTER,
		SUMMER,
		SPRING,
		AUTUMN,	
		COUNT
	}season;
	Animation season_animation[SEASON_TYPE::COUNT];
	void set_season(SEASON_TYPE a) { season = a; };
	SEASON_TYPE get_season() { return season; };
	void apply_season()
	{
		switch (season)
		{
		case SeasonManager::WINTER:
			MinionManager::GetInstance()->adjust_minions_move_speed(80);
			MinionManager::GetInstance()->adjust_minions_dmg(90);
			MinionManager::GetInstance()->adjust_minions_hp(110);
			MinionManager::GetInstance()->adjust_minions_att_spd(80);
			break;
		case SeasonManager::SUMMER:
			MinionManager::GetInstance()->adjust_minions_move_speed(110);
			MinionManager::GetInstance()->adjust_minions_dmg(120);
			MinionManager::GetInstance()->adjust_minions_att_spd(110);
			MinionManager::GetInstance()->adjust_minions_hp(90);
			break;
		case SeasonManager::SPRING:
			MinionManager::GetInstance()->reset_minions_att_spd();
			MinionManager::GetInstance()->reset_minions_dmg();
			MinionManager::GetInstance()->reset_minions_hp();
			MinionManager::GetInstance()->reset_minions_move_speed();
			break;
		case SeasonManager::AUTUMN:
			MinionManager::GetInstance()->adjust_minions_hp(80);
			MinionManager::GetInstance()->adjust_minions_dmg(80);
			MinionManager::GetInstance()->adjust_minions_move_speed(120);
			MinionManager::GetInstance()->adjust_minions_att_spd(80);
			break;
		}
	}
	void update(double dt) 
	{
		SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(season_mesh[season]);
		sa->m_anim = &season_animation[season];
		sa->Update(dt);
	}
	void render_season()
	{
		MS& ms = Graphics::GetInstance()->modelStack;
		ms.PushMatrix();
		ms.Translate(50, 50, 0);
		ms.Scale(15, 15, 15);
		RenderHelper::RenderMesh(season_mesh[season], false);
		ms.PopMatrix();

	}
private:
	friend Singleton;

	Mesh* season_mesh[SEASON_TYPE::COUNT];
	
protected:
	SeasonManager() {
		//season_mesh[WINTER] = ObjectPoolManager::GetInstance()->get_particle(ObjectPoolManager::PARTICLE_CASE::WINTER);
		//season_mesh[SUMMER] = ObjectPoolManager::GetInstance()->get_particle(ObjectPoolManager::PARTICLE_CASE::SUMMER);
		//season_mesh[SPRING] = ObjectPoolManager::GetInstance()->get_particle(ObjectPoolManager::PARTICLE_CASE::SPRING);
		//season_mesh[AUTUMN] = ObjectPoolManager::GetInstance()->get_particle(ObjectPoolManager::PARTICLE_CASE::AUTUMN);
		season_mesh[WINTER] = MeshList::GetInstance()->getMesh("WINTER");
		season_mesh[SUMMER] = MeshList::GetInstance()->getMesh("SUMMER");
		season_mesh[SPRING] = MeshList::GetInstance()->getMesh("SPRING");
		season_mesh[AUTUMN] = MeshList::GetInstance()->getMesh("AUTUMN");

		season_animation[SEASON_TYPE::WINTER].Set(0, 8, 1, 10.f, true);
		season_animation[SEASON_TYPE::SUMMER].Set(0, 8, 1, 10.f, true);
		season_animation[SEASON_TYPE::SPRING].Set(0, 8, 1, 10.f, true);
		season_animation[SEASON_TYPE::AUTUMN].Set(0, 8, 1, 10.f, true);
	};
	~SeasonManager() {};
};

#endif // !SEASONMANAGER_H
