#include "Ball.h"
#include "Flipper.h"

vector3 Ball::Gravity = vector3(0.0f, -6.0f, 0.0f);

Ball::Ball() : Entity((mesh = new PrimitiveClass(), mesh->GenerateSphere(0.2, 12, REWHITE), mesh))
{
	collider->setType(ColliderType::Sphere);
	SetElascity(.65f);
	angularVelocity = vector3(0.0f, 0.0f, 9.1f);
}


Ball::~Ball()
{
}

void Ball::PhysicsUpdate(double deltaTime)
{
	Entity::PhysicsUpdate(deltaTime);
	angularVelocity.z = -velocity.x * 2.f;
	GameObject::Rotate(quaternion(angularVelocity * static_cast<float>(deltaTime)));
}

void Ball::Update(double DeltaTime)
{
	Accelerate(Gravity);
	Entity::Update(DeltaTime);
	transform->SetPosition(vector3(transform->GetPosition().x, transform->GetPosition().y, 1.0f));
}
	

void Ball::Accelerate(vector3 force)
{
	acceleration += force;
}

void Ball::OnCollision(CollisionEvent collision)
{
	vector3 disp = collision.collideeIntersectPt - GetPosition();
	if (glm::length2(disp) > 0 && glm::length2(velocity) < 1.f) {
		vector3 normal = glm::normalize(glm::length(disp) == 0 ? vector3(1) : disp);
		//vector3 slope = vector3(-normal.y, normal.x, 0);
		acceleration = normal * glm::length(Gravity) + vector3(-normal.x * 100.0f, 0, 0);
	}
}

ObjectType Ball::GetType()
{
	return ObjectType::Ball;
}
