#ifndef GENERICDECORATION_H
#define GENERICDECORATION_H

#include "GameObject.h"

class GenericDecoration : public GameObject
{
public:
	enum DECOTYPE
	{
		BACKGROUND = 0
	};
	GenericDecoration(DECOTYPE type = (DECOTYPE)0);
	~GenericDecoration();
};

#endif // !GENERICDECORATION_H
