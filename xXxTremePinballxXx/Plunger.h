#pragma once
#include "Entity.h"
#include "Ball.h"

class Plunger : public Entity
{
public:
	Plunger(const vector3& start, const vector3 end);

	void Update(double dt);

	void StartLaunch();
	void EndLaunch();

	virtual void OnCollision(const CollisionEvent& collision) override;

private:
	vector3 start;
	vector3 end;
	float speed;
	bool launching;
	float launchPct;

	PrimitiveClass* mesh;
};