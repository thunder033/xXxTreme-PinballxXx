#pragma once
#include "Entity.h"
#include "Ball.h"
#include "ChuteSlide.h"

class Plunger : public Entity
{
public:
	Plunger(const vector3& start, const vector3 end);
	virtual ~Plunger();

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
	ChuteSlide* slide;
	const float slideTriggerTime = .4f;
	float slideElapsed;
	bool slideTriggered;
};