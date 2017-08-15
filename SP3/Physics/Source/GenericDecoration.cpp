#include "GenericDecoration.h"

#include "GameLogic.h"
#include "MeshList.h"

GenericDecoration::GenericDecoration(DECOTYPE type)
{
	switch (type)
	{
	case BACKGROUND:
	{
		float world_width, world_height;
		GameLogic::GetInstance()->get_world_size(world_width, world_height);
		this->pos.Set(world_width * 0.5f, world_height * 0.5f);
		this->scale.Set(world_width, world_height);
		this->mesh = MeshList::GetInstance()->getMesh("BACKGROUND");
		break;
	}

	}
}
GenericDecoration::~GenericDecoration(){}