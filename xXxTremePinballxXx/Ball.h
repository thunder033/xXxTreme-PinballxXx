#pragma once
#include "Entity.h"
class Ball :
	public Entity
{
	PrimitiveClass* mesh;
public:
	Ball();
	~Ball();
	virtual void Update(double) override;
	void Accelerate(vector3);
	virtual void OnCollision(const CollisionEvent) override;
	virtual ObjectType GetType() override;
};

