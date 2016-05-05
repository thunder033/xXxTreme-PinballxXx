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
		
		vector3 disp = ball->GetPosition() - collision.collideeIntersectPt;
		vector3 normal = glm::normalize(glm::length(disp) == 0 ? vector3(1) : disp);
		vector3 newBallVelocity = glm::reflect(ball->GetVelocity(), normal);
		ball->SetVelocity(newBallVelocity * ball->GetElascity());
		ball->Translate(-collision.penetrationVector);
		break;
	}
	default:
		break;
	}
}
