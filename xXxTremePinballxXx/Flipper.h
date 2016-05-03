#pragma once
#include "GameObject.h"

class Flipper : public GameObject
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
};

