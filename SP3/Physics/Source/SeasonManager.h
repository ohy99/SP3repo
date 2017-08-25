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
