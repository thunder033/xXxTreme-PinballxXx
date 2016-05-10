#ifndef _WALL_H_
#define _WALL_H_

#include "GameObject.h"
#include "Entity.h"
#include "Ball.h"

class Wall : public GameObject
{
	PrimitiveClass* mesh;

public:
	Wall(vector3);

	virtual void OnCollision(const CollisionEvent) override;
};


#endif