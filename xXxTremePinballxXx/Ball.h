#pragma once
#include "GameObject.h"
class Ball :
	public GameObject
{
	PrimitiveClass* mesh;
public:
	Ball();
	~Ball();
	void Update(double) override;
	void Accelerate(vector3);
};

