#include "Entity.h"


Entity::Entity(MeshClass* mesh) : GameObject(mesh)
{

}

Entity::Entity() : GameObject()
{
	velocity = vector3(0);
	acceleration = vector3(0);
}


Entity::~Entity()
{

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
	for (std::vector<GameObject*>::iterator it = GameObject::instances.begin(); it != instances.end(); ++it)
	{
		if (*it == this || frameCollisions.find((*it)->GetID()) != frameCollisions.end())
			continue;

		checkCount++;
		Collision* collision = (*it)->GetCollider()->IsColliding(this->collider);

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
	GameObject::Update(deltaTime);
	PhysicsUpdate(deltaTime);
}
