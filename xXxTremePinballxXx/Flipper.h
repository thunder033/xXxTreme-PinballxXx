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
	Flipper();
	~Flipper();
	void Update(double);

	void Flip();

	virtual ObjectType GetType() override;

	virtual void OnCollision(const CollisionEvent) override;
};

