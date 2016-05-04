#pragma once
#include "GameObject.h"
class Entity :
	public GameObject
{
	vector3 velocity;
	vector3 acceleration;
protected:
	std::unordered_map<int, Collision*> frameCollisions;
	void AddFrameCollision(int, Collision*);
public:
	Entity();
	virtual ~Entity();

	const vector3& GetVelocity() const;

	void SetVelocity(const vector3& newVelocity);

	virtual void OnCollision(const CollisionEvent);
};

