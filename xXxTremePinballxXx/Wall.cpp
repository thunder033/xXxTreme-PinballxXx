#include "Wall.h"

Wall::Wall(vector3 scale) : GameObject((mesh = new PrimitiveClass(), mesh->GenerateCube(1.f, REGRAY), mesh))
{
	collider->setType(ColliderType::OBB);
	Scale(scale);
}

void Wall::OnCollision(CollisionEvent collision)
{
	switch (collision.collidee->GetType())
	{
	case ObjectType::Ball:
	{
		Ball* ball = dynamic_cast<Ball*>(collision.collidee);
		quaternion orientation = this->transform->GetRotation();

		vector3 disp = ball->GetPosition() - collision.collideeIntersectPt;
		vector3 normal = glm::normalize(glm::length(disp) == 0 ? vector3(1) : disp);
		vector3 slope = vector3(normal.y, -normal.x, 0);
		slope = slope.y > 0 ? -slope : slope;
		float velocityInNormal = glm::dot(normal, ball->GetVelocity());

		if (abs(velocityInNormal) > 0) {
			vector3 newBallVelocity = glm::reflect(ball->GetVelocity(), normal);
			vector3 velocityNormal = glm::normalize(newBallVelocity);
			vector3 normalVelocity = velocityNormal * glm::dot(newBallVelocity, normal) * ball->GetElascity();
			vector3 slopeVelocity = velocityNormal * glm::dot(newBallVelocity, slope) * .85f;
			ball->SetVelocity((normalVelocity + slopeVelocity));
		}
		break;
	}
	default:
		break;
	}
}
