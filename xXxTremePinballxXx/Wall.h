#ifndef _WALL_H_
#define _WALL_H_

#include "GameObject.h"

class Wall : public GameObject
{
	PrimitiveClass* mesh;

public:
	Wall();

	virtual void OnCollision(vector3, GameObject*) override;
};


#endif