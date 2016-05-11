#include "Flipper.h"

#include <glm/glm.hpp>


Flipper::Flipper(boolean flipped) : Entity((mesh = new PrimitiveClass(), mesh->GenerateCube(1, RERED), mesh))
{
	if (!flipped) {
		SetOrigin(vector3(-0.5f, 0, 0));
		Scale(vector3(1.5f, .4f, .4f));
		RotateTo(vector3(0.f, 0.f, -.2f));
		flipRotation = vector3(0, 0, PI / 3.0f);
	}
	else {
		SetOrigin(vector3(0.5f, 0, 0));
		Scale(vector3(1.35f, .4f, .4f));
		RotateTo(vector3(0.f, 0.f, .2f));
		flipRotation = vector3(0, 0, PI / -3.0f);
	}
	flipStart = transform->GetRotation();

	flipPct = 0;
	flipSpeed = 7.5f;
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
			flipPct = 1.0f;
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

void Flipper::Unflip()
{
	flipping = false;
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
		vector3 disp = ball->GetPosition() - collision.collideeIntersectPt;
		vector3 normal = glm::normalize(glm::length(disp) == 0 ? vector3(1) : disp);
		
		double flipperMagnitude = 0.0;
		if (flipping)
		{
			float edgePos = glm::dot(collision.collideeIntersectPt - transform->GetPosition(), collider->GetOBB().r);
			float length = (transform->GetScale().x - transform->GetOrigin().x);
			float relEdge = (edgePos + transform->GetOrigin().x);
			flipperMagnitude = relEdge / length;
			//flipperMagnitude = ((flipRotation.z - flipStart.z) * flipSpeed) * (glm::distance(collision.intersectPt, (GetPosition() + GetOrigin()))) / 3.f;
		}		
		double velocityImpulse = flipperMagnitude * flipSpeed * 1.75f;
		vector3 newBallVelocity = ball->GetVelocity() + ((float)velocityImpulse * normal);

		ball->SetVelocity(newBallVelocity);

		break;
	}
	default:
		break;
	}
}
