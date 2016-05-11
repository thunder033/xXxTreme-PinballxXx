#pragma once
#include "Entity.h"
#include "Ball.h"

class Plunger : public Entity
{
public:
	Plunger(const vector3& start, const vector3 end, float speed);
	~Plunger();

	void Update(double dt);

	void StartLaunch();
	void EndLaunch();

	virtual ObjectType GetType() override;

	virtual void OnCollision(const CollisionEvent e) override;

private:
	vector3 start;
	vector3 end;
	float speed;
	bool launching;

	PrimitiveClass* mesh;
};