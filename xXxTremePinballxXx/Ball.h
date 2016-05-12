#pragma once
#include "Entity.h"
class Ball :
	public Entity
{
	vector3 angularVelocity;
	PrimitiveClass* mesh;
public:
	Ball();
	~Ball();
	virtual void PhysicsUpdate(double) override;
	virtual void Update(double) override;
	void Accelerate(vector3);
	virtual void OnCollision(const CollisionEvent&) override;
	virtual ObjectType GetType() override;
	static vector3 Gravity;
};

