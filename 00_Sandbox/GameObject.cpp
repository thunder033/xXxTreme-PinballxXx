#include "GameObject.h"



GameObject::GameObject()
{
	position = vector3(0);
	velocity = vector3(0);
	acceleration = vector3(0);

	scale = vector3(1);
	rotation = quaternion(vector3(0));

	GameObject::instances.push_back(this);

	mesh = new MeshClass();
}


GameObject::~GameObject()
{
	GameObject::instances.erase(std::remove(instances.begin(), instances.end(), this), instances.end);

	if (mesh != nullptr) 
	{
		delete mesh;
		mesh = nullptr;
	}

	if (collider != nullptr)
	{
		delete collider;
		collider = nullptr;
	}
}

vector3 GameObject::getOrigin()
{
	return origin;
}

vector3 GameObject::getPosition()
{
	return position;
}

matrix4 GameObject::getTransform()
{
	return glm::translate(position) * ToMatrix4(rotation) * glm::scale(scale);
}

void GameObject::update(double deltaTime)
{
	velocity += acceleration * static_cast<float>(deltaTime);
	position += velocity * static_cast<float>(deltaTime);

	for (std::vector<GameObject*>::iterator it = instances.begin(); it != instances.end(); ++it)
	{
		bool colliding = (*it)->collider->isColliding(this->collider);
		//TODO: do stuff with colliding;
	}
}

void GameObject::render(matrix4 projection, matrix4 view)
{
	mesh->Render(projection, view, getTransform());
}

void GameObject::RenderDebugHelpers()
{

}

void GameObject::updateAll(double deltaTime)
{
	for (std::vector<GameObject*>::iterator it = instances.begin(); it != instances.end(); ++it)
	{
		(*it)->update(deltaTime);
	}
}

void GameObject::renderAll(matrix4 projection, matrix4 view)
{
	for (std::vector<GameObject*>::iterator it = instances.begin(); it != instances.end(); ++it)
	{
		(*it)->render(projection, view);
	}
}
