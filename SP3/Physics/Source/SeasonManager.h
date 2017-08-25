#ifndef SEASONMANAGER_H
#define SEASONMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include "RenderHelper.h"
#include "Graphics.h"
#include "ObjectPoolManager.h"
#include "ParticleManager.h"
#include "MeshList.h"
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
	void set_season(SEASON_TYPE a) { season = a; };
	SEASON_TYPE get_season() { return season; };
	void update(double dt) 
	{
		SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("WINTER"));
		if (sa)
		{

			sa->Update(dt);
			sa->m_anim->animActive = true;
		}
		SpriteAnimation* sa2 = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("SUMMER"));
		if (sa)
		{

			sa->Update(dt);
			sa->m_anim->animActive = true;
		}
		SpriteAnimation* sa3 = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("SPRING"));
		if (sa)
		{

			sa->Update(dt);
			sa->m_anim->animActive = true;
		}
		SpriteAnimation* sa4 = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("AUTUMN"));
		if (sa)
		{

			sa->Update(dt);
			sa->m_anim->animActive = true;
		}
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
		SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("WINTER"));
		if (sa)
		{
			sa->m_anim = new Animation();
			sa->m_anim->Set(0, 8, 1, 10.0f, true);
		}
		SpriteAnimation* sa2 = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("SUMMER"));
		if (sa)
		{
			sa->m_anim = new Animation();
			sa->m_anim->Set(0, 8, 1, 10.0f, true);
		}
		SpriteAnimation* sa3 = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("SPRING"));
		if (sa)
		{
			sa->m_anim = new Animation();
			sa->m_anim->Set(0, 8, 1, 10.0f, true);
		}
		SpriteAnimation* sa4 = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("AUTUMN"));
		if (sa)
		{
			sa->m_anim = new Animation();
			sa->m_anim->Set(0, 8, 1, 10.0f, true);
		}
		
	};
	~SeasonManager() {};
};

#endif // !SEASONMANAGER_H
