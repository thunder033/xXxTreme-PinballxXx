#include "Ball.h"
#include "Flipper.h"

vector3 Ball::Gravity = vector3(0.0f, -6.0f, 0.0f);

Ball::Ball() : Entity((mesh = new PrimitiveClass(), mesh->GenerateSphere(0.2f, 12, REWHITE), mesh))
{
	collider->setType(ColliderType::Sphere);
	SetElasticity(.60f);
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

void Ball::OnCollision(const CollisionEvent& e)
{
	CollisionEvent collision = e;
	if (collision.collidee->GetType() == ObjectType::Flipper) {
		Translate(collision.penetrationVector);
		std::shared_ptr<Collision> newCollision = collision.collidee->GetCollider()->IsColliding(this->GetCollider());
		if (newCollision != nullptr) {
			collision = newCollision->GetEvent(this);
		}
	}

	//Get the vector from the center of the ball to it's edge
	vector3 disp = -(collision.collideeIntersectPt - GetPosition()) - collision.penetrationVector;
	//Get the normal of collision (perpendicular to collision surface)
	vector3 normal = glm::normalize(glm::length(disp) == 0 ? vector3(1) : disp);
	//get the slope of collision (parallel to collision surface or tangent if it's circular)
	vector3 slope = vector3(normal.y, -normal.x, 0);
	//This is a bit hacky, but were only interested in the slope in the direction of gravity
	slope = slope.y > 0 ? -slope : slope;

	/*
	* make the ball roll if: 
	* - there's non-zero displacment, 
	* - we're below a minimum of velocity normal to the surface
	* - and normal is in the upright direction (don't roll on upside-down surfaces)
	*/
	float normalVelocity = abs(glm::dot(normal, velocity));
	float rollLimit = .4f;
	if (glm::length2(disp) > 0 && abs(normalVelocity) < rollLimit && glm::sign(normal.y) != glm::sign(Gravity.y)) {
		//Get the magnitude of gravity in the direction of slope
		float mag = glm::dot(slope, Gravity);
		//set the acceleration to this
		acceleration = ((slope * mag) * (rollLimit - normalVelocity)/rollLimit) + (normalVelocity/rollLimit) * acceleration;	
	}

	//Don't apply bounce physics if there's no velocity normal to the surface
	float velocityInNormal = glm::dot(normal, GetVelocity());
	if (abs(velocityInNormal) > 0) {
		//calculate the reflected ball velocity (-->THIS LINE IS PROBABLY THE CAUSE OF WEIRDNESS<--)
		vector3 newBallVelocity = glm::reflect(GetVelocity(), normal);
		//get the normalized
		vector3 velocityNormal = glm::length2(newBallVelocity) > 0 ? glm::normalize(newBallVelocity) : vector3(0, 0, 0);
		//apply the ball's elascity to only the velocity component normal to the surface
		vector3 normalVelocity = velocityNormal * glm::dot(newBallVelocity, normal) * GetElasticity();
		//apply friction to the ball's roll in the component parallel to the surface
		vector3 slopeVelocity = velocityNormal * glm::dot(newBallVelocity, slope) * .83f;
		SetVelocity((normalVelocity + slopeVelocity));
	}

	//Move the ball out of the object it's intersecting with
	Translate(collision.penetrationVector);
}

ObjectType Ball::GetType()
{
	return ObjectType::Ball;
}
