#include "Flipper.h"

#include <glm/glm.hpp>


Flipper::Flipper() : Entity((mesh = new PrimitiveClass(), mesh->GenerateCube(1, RERED), mesh))
{
	SetOrigin(vector3(-0.5f, 0, 0));
	Scale(vector3(2, .5f, .5f));

	flipRotation = vector3(0, 0, PI / 2.0f);
	flipStart = transform->GetRotation();
	flipPct = 0;
	flipSpeed = 5.0f;
	flipping = false;
}


Flipper::~Flipper()
{
}

void Flipper::Update(double deltaTime)
{
	if (flipping) {
		flipPct += flipSpeed * deltaTime;
		if (flipPct >= 1.0f)
			flipping = false;
	}
	else if(flipPct > 0) {
		flipPct -= flipSpeed * deltaTime;
		if (flipPct < 0)
			flipPct = 0;
	}

	quaternion orientation = glm::mix(flipStart, flipStart * quaternion(flipRotation), flipPct);
	RotateTo(orientation);

	Entity::Update(deltaTime);
}

void Flipper::Flip() {
	if (!flipping && flipPct == 0) {
		flipping = true;
		flipPct = 0;
	}
}

ObjectType Flipper::GetType()
{
	return ObjectType::Flipper;
}

void Flipper::OnCollision(CollisionEvent collision)
{
	switch (collision.collidee->GetType())
	{
	case ObjectType::Ball:
	{
		Entity* ball = dynamic_cast<Entity*>(collision.collidee);
		quaternion orientation = this->transform->GetRotation();
		vector3 normal = vector3(0.0f, 1.0f, 0.0f) * orientation;
		double flipperMagnitude = 0.0;
		if (flipping)
		{
			flipperMagnitude = ((flipRotation.z - flipStart.z) * flipSpeed) * (glm::distance(collision.intersectPt, (GetPosition() + GetOrigin()))) / 3.f;
		}		
		double newVelocityPercent = flipperMagnitude / glm::length(ball->GetVelocity());
		vector3 newBallVelocity = glm::reflect(ball->GetVelocity(), normal) *  (1.0f + (float)newVelocityPercent);
		//ball->SetVelocity(newBallVelocity);
		break;
	}
	default:
		break;
	}
}
