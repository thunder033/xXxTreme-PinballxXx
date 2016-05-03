#include "Ball.h"
#include "Flipper.h"



Ball::Ball() : GameObject((mesh = new PrimitiveClass(), mesh->GenerateSphere(0.2, 12, REWHITE), mesh))
{
	collider->setType(ColliderType::Circle);
}


Ball::~Ball()
{
}

void Ball::Update(double DeltaTime)
{
	Accelerate(vector3(0.0f, -6.0f, 0.0f));
	GameObject::Update(DeltaTime);
	transform->SetPosition(vector3(transform->GetPosition().x, transform->GetPosition().y, 1.0f));
}

void Ball::Accelerate(vector3 force)
{
	GameObject::acceleration += force;
}

void Ball::OnCollision(vector3 collisionPoint, GameObject* collidee)
{
	if (collidee->GetType() == ObjectType::Flipper)
	{
		auto temp = reinterpret_cast<Flipper*>(collidee);
	}
}

ObjectType Ball::GetType()
{
	return ObjectType::Ball;
}
