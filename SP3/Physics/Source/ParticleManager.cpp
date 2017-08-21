#include "ParticleManager.h"
#include "MeshList.h"

#include "Graphics.h"
#include "RenderHelper.h"

void Particle::update(double dt)
{

	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Poster"));
	if (sa)
	{

		sa->Update(dt);
		sa->m_anim->animActive = true;
	}

	active_elapsed += dt;

	if (active_elapsed >= active_duration)
	{
		this->active = false;
		active_elapsed = 0.0;
	}
}

void Particle::init()
{
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Poster"));
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 5, 1, 10.0f, true);
	}
}

void Particle::render()
{


	MS& ms = Graphics::GetInstance()->modelStack;
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Poster"));
	ms.PushMatrix();
	ms.Translate(this->pos);
	ms.Scale(this->scale);
	RenderHelper::RenderMesh(sa, false);
	//sa->Render();
	ms.PopMatrix();


}

void Particle::set_duration(double duration)
{
	this->active_duration = duration;
}
