#include "Entity.h"

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

void Entity::PhysicsUpdate(double deltaTime)
{
	for (std::vector<GameObject*>::iterator it = GameObject::instances.begin(); it != GameObject::instances.end(); ++it)
	{
		if (this->collisionTest != ObjectType::Default && this->collisionTest != (*it)->GetType())
			continue;

		if (*it == this || frameCollisions.find((*it)->GetID()) != frameCollisions.end())
			continue;

		checkCount++;
		std::shared_ptr<Collision> collision = (*it)->GetCollider()->IsColliding(this->collider);

		if (collision != nullptr) {
			collision->collider1 = *it;
			collision->collider2 = this;
		}

		AddFrameCollision((*it)->GetID(), collision);
		(*it)->AddFrameCollision(GetID(), collision);

		if (collision != nullptr && collision->colliding) {
			OnCollision(collision->GetEvent(this));
			(*it)->OnCollision(collision->GetEvent(*it));
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
	PhysicsUpdate(deltaTime);
	GameObject::Update(deltaTime);
}
