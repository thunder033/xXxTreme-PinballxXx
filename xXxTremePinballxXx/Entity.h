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
	void SetElasticity(float elascity);

	static std::vector<Entity*> instances;
public:
	Entity(MeshClass*);
	Entity();
	virtual ~Entity();

	const vector3& GetVelocity() const;

	const float GetMass() const;

	const float GetElasticity() const;

	void SetVelocity(const vector3& newVelocity);

	virtual void PhysicsUpdate(class Octree* octree, double deltaTime);

	virtual void Update(double deltaTime) override;

	static void init();

	static std::vector<Entity*> GetInstances();
};

