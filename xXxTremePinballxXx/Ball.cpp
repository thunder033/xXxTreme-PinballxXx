#include "Ball.h"
#include "Flipper.h"



Ball::Ball() : Entity((mesh = new PrimitiveClass(), mesh->GenerateSphere(0.2, 12, REWHITE), mesh))
{
	collider->setType(ColliderType::Sphere);
	SetElascity(.65f);
}


Ball::~Ball()
{
}

void Ball::Update(double DeltaTime)
{
	Accelerate(vector3(0.0f, -6.0f, 0.0f));
	Entity::Update(DeltaTime);
	transform->SetPosition(vector3(transform->GetPosition().x, transform->GetPosition().y, 1.0f));
}

void Ball::Accelerate(vector3 force)
{
	acceleration += force;
}

void Ball::OnCollision(CollisionEvent collision)
{
}

ObjectType Ball::GetType()
{
	return ObjectType::Ball;
}
