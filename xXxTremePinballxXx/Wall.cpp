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
		quaternion orientation = this->transform->GetRotation();
		vector3 normal = vector3(0.0f, 1.0f, 0.0f) * orientation;
		vector3 newBallVelocity = glm::reflect(collision.collidee->GetVelocity(), normal);
		collision.collidee->SetVelocity(newBallVelocity);
		collision.collidee->Translate(-collision.penetrationVector);
		break;
	}
	default:
		break;
	}
}
