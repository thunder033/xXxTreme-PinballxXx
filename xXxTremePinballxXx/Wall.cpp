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
		Entity* ball = dynamic_cast<Entity*>(collision.collidee);
		quaternion orientation = this->transform->GetRotation();
		//vector3 normal = vector3(0.0f, 1.0f, 0.0f) * orientation;
		vector3 disp = ball->GetPosition() - collision.collideeIntersectPt;
		vector3 normal = glm::normalize(glm::length(disp) == 0 ? vector3(1) : disp) * orientation;
		vector3 newBallVelocity = glm::reflect(ball->GetVelocity(), normal);
		ball->SetVelocity(newBallVelocity);
		ball->Translate(-collision.penetrationVector);
		break;
	}
	default:
		break;
	}
}
