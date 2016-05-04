#pragma once
#include "GameObject.h"
class Entity :
	public GameObject
{
	vector3 lastPosition;
protected:
	vector3 velocity;
	vector3 acceleration;
public:
	Entity(MeshClass*);
	Entity();
	virtual ~Entity();

	const vector3& GetVelocity() const;

	void SetVelocity(const vector3& newVelocity);

	virtual void PhysicsUpdate(double deltaTime);

	virtual void Update(double deltaTime) override;
};

