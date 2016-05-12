#include "Entity.h"
#include "OctNode.h"

std::vector<Entity*> Entity::instances;

void Entity::init() {
	instances = std::vector<Entity*>();
}

std::vector<Entity*> Entity::GetInstances() {
	return Entity::instances;
}

void Entity::SetMass(float mass)
{
	this->mass = mass;
}

void Entity::SetElasticity(float elascity)
{
	this->elasictiy = elascity;
}

Entity::Entity(MeshClass* mesh) : GameObject(mesh)
{
	instances.push_back(this);
	velocity = vector3(0);
	acceleration = vector3(0);

	mass = 1;
	elasictiy = 1;
}

Entity::Entity() : GameObject()
{
	instances.push_back(this);
	velocity = vector3(0);
	acceleration = vector3(0);

	mass = 1;
	elasictiy = 1;
}


Entity::~Entity()
{

}

const float Entity::GetMass() const
{
	return mass;
}

const float Entity::GetElasticity() const
{
	return elasictiy;
}

const vector3& Entity::GetVelocity() const
{
	return this->velocity;
}

void Entity::SetVelocity(const vector3& newVelocity)
{
	this->velocity = newVelocity;
}

void Entity::PhysicsUpdate(Octree* octree, double deltaTime)
{
	auto& instancesToCheck = octree->nearbyObjects(this);
	for (auto obj : instancesToCheck)
	{
		if (obj == this || frameCollisions.find(this->GetID()) != frameCollisions.end())
			continue;

		if (this->collisionTest != ObjectType::Default && this->collisionTest != obj->GetType())
			continue;

		checkCount++;
		std::shared_ptr<Collision> collision = obj->GetCollider()->IsColliding(this->collider);

		if (collision != nullptr) {
			collision->collider1 = obj;
			collision->collider2 = this;
		}

		AddFrameCollision(obj->GetID(), collision);
		obj->AddFrameCollision(GetID(), collision);

		if (collision != nullptr && collision->colliding) {
			OnCollision(collision->GetEvent(this));
			obj->OnCollision(collision->GetEvent(obj));
		}
	}

	frameCollisions.clear();

	velocity += acceleration * static_cast<float>(deltaTime);
	lastPosition = GetPosition();
	Translate(velocity * static_cast<float>(deltaTime));
	acceleration = vector3(0.0f, 0.0f, 0.0f);
}

void Entity::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}
