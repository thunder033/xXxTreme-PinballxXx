#pragma once
#include "GameObject.h"
class Entity :
	public GameObject
{
	float mass;
	float elasictiy;

	vector3 lastPosition;
protected:
	vector3 velocity;
	vector3 acceleration;

	void SetMass(float mass);
	void SetElascity(float elascity);
public:
	Entity(MeshClass*);
	Entity();
	virtual ~Entity();

	const vector3& GetVelocity() const;

	const float GetMass() const;

	const float GetElascity() const;

	void SetVelocity(const vector3& newVelocity);

	virtual void PhysicsUpdate(double deltaTime);

	virtual void Update(double deltaTime) override;
};

