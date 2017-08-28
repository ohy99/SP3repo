#ifndef NOOBBOW_H
#define NOOBBOW_H

#include "Weapon.h"

class NoobBow : public Weapon
{
public:
	NoobBow();
	~NoobBow();

	virtual void Discharge(Vector3 position, Vector3 dir);
};

#endif // !NOOBBOW_H

