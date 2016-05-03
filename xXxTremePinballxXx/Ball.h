#pragma once
#include "GameObject.h"
class Ball :
	public GameObject
{
	PrimitiveClass* mesh;
public:
	Ball();
	~Ball();
	virtual void Update(double) override;
	void Accelerate(vector3);
	virtual void OnCollision(vector3, GameObject*) override;
	virtual ObjectType GetType() override;
};

