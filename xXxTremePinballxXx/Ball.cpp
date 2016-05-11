#include "Ball.h"
#include "Flipper.h"

vector3 Ball::Gravity = vector3(0.0f, -6.0f, 0.0f);

Ball::Ball() : Entity((mesh = new PrimitiveClass(), mesh->GenerateSphere(0.2, 12, REWHITE), mesh))
{
	collider->setType(ColliderType::Sphere);
	SetElascity(.55f);
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
	vector3 disp = -(collision.collideeIntersectPt - GetPosition()) - collision.penetrationVector;
	vector3 normal = glm::normalize(glm::length(disp) == 0 ? vector3(1) : disp);
	float normalVelocity = glm::dot(normal, velocity);
	vector3 slope = vector3(normal.y, -normal.x, 0);
	slope = slope.y > 0 ? -slope : slope;

	if (glm::length2(disp) > 0 && normalVelocity < 0.3f && glm::sign(normal.y) != glm::sign(Gravity.y)) {
		float mag = glm::dot(slope, Gravity);
		acceleration = slope * mag;	
	}

	float velocityInNormal = glm::dot(normal, GetVelocity());

	if (abs(velocityInNormal) > 0) {
		vector3 newBallVelocity = glm::reflect(GetVelocity(), -normal);
		vector3 velocityNormal = glm::normalize(newBallVelocity);
		vector3 normalVelocity = velocityNormal * glm::dot(newBallVelocity, normal) * GetElascity();
		vector3 slopeVelocity = velocityNormal * glm::dot(newBallVelocity, slope) * .85f;
		SetVelocity((normalVelocity + slopeVelocity));
	}

	Translate(collision.penetrationVector);
}

ObjectType Ball::GetType()
{
	return ObjectType::Ball;
}
