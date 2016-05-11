#pragma once
#include "Entity.h"
#include "Ball.h"

class Flipper : public Entity
{
	quaternion flipStart;
	vector3 flipRotation;
	float flipPct;
	float flipSpeed;
	bool flipping;

	PrimitiveClass* mesh;
public:
	Flipper(boolean flipped);

	virtual void Update(double) override;

	void Flip();
	void Unflip();

	virtual ObjectType GetType() override;

	virtual void OnCollision(const CollisionEvent&) override;
};

