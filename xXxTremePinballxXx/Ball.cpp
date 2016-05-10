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
	vector3 normal = glm::normalize(glm::length(disp) == 0 ? vector3(1) : disp);
	float normalVelocity = glm::dot(normal, velocity);

	if (glm::length2(disp) > 0 && normalVelocity < 1.f) {
		
		vector3 slope = vector3(-normal.y, normal.x, 0);
		if (slope.y > 0.01f) {
			acceleration = normal * glm::length(Gravity) + slope * 10.f;
		}
		
	}
}

ObjectType Ball::GetType()
{
	return ObjectType::Ball;
}
