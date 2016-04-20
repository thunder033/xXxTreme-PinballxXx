#include "GameObject.h"

std::vector<GameObject*> GameObject::instances;
MeshManagerSingleton* GameObject::renderer;
int GameObject::selectedInstanceIndex;

GameObject::GameObject() : GameObject(new PrimitiveClass())
{
	(static_cast<PrimitiveClass*>(mesh))->GenerateCube(1, REWHITE);
	collider = new Collider(mesh->GetVertexList());
}

GameObject::GameObject(MeshClass * mesh)
{
	this->mesh = mesh;

	position = vector3(0);
	velocity = vector3(0);
	acceleration = vector3(0);

	scale = vector3(1);
	rotation = quaternion(vector3(0));

	hasFrameCollisions = false;
	debugColor = REGREEN;

	GameObject::instances.push_back(this);
	collider = new Collider(mesh->GetVertexList());

	debugAABBMode, debugNABMode = true;
}

GameObject::~GameObject()
{
	GameObject::instances.erase(std::remove(instances.begin(), instances.end(), this), instances.end());

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

void GameObject::setDebugColor(vector3 newColor) 
{
	debugColor = newColor;
}

void GameObject::update(double deltaTime)
{
	velocity += acceleration * static_cast<float>(deltaTime);
	position += velocity * static_cast<float>(deltaTime);
	hasFrameCollisions = false;

	for (std::vector<GameObject*>::iterator it = instances.begin(); it != instances.end(); ++it)
	{
		if (*it == this)
			continue;

		bool colliding = (*it)->collider->isColliding(this->collider);
		hasFrameCollisions = hasFrameCollisions || colliding;
	}
}

void GameObject::render(matrix4 projection, matrix4 view)
{
	mesh->Render(projection, view, getTransform());
}

void GameObject::renderAABBDebugHelpers()
{
	vector3 color = hasFrameCollisions ? RERED : debugColor;
	renderer->AddCubeToQueue(collider->GetAxisAlignedTransform(), color, WIRE);
}

void GameObject::renderNABDebugHelpers()
{
	vector3 color = hasFrameCollisions ? RERED : debugColor;
	renderer->AddCubeToQueue(getTransform(), color, WIRE);
}

/*
***BEGIN STATIC (BOUNDING BOX MANAGER) METHODS***
*/
void GameObject::init()
{
	renderer = MeshManagerSingleton::GetInstance();
	instances = std::vector<GameObject*>();
	selectedInstanceIndex = 0;
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

		if ((*it)->debugAABBMode)
			(*it)->renderAABBDebugHelpers();

		if ((*it)->debugNABMode)
			(*it)->renderNABDebugHelpers();
	}
}

void GameObject::toggleDebugMode(int colliderType)
{
	if (colliderType == AABB)
	{
		for (std::vector<GameObject*>::iterator it = instances.begin(); it != instances.end(); ++it)
		{
			(*it)->debugAABBMode = !(*it)->debugAABBMode;
		}
		return;
	}
	for (std::vector<GameObject*>::iterator it = instances.begin(); it != instances.end(); ++it)
	{
		(*it)->debugNABMode = !(*it)->debugNABMode;
	}
}

void GameObject::cycleSelectedIndex(bool direction)
{
	if (direction)
	{
		selectedInstanceIndex += 1;
		if (selectedInstanceIndex >= (int)instances.size())
		{
			selectedInstanceIndex = 0;
		}
	}
	else
	{
		selectedInstanceIndex -= 1;
		if (selectedInstanceIndex < 0)
		{
			selectedInstanceIndex = instances.size() - 1;
		}
	}
	setSelectedColor(REYELLOW);
}

void GameObject::setSelectedColor(vector3 newColor)
{
	instances[selectedInstanceIndex]->setDebugColor(newColor);
}

void GameObject::toggleSelectedDebugMode(int colliderType)
{
	if (colliderType)
	{
		instances[selectedInstanceIndex]->debugAABBMode = !instances[selectedInstanceIndex]->debugAABBMode;
		return;
	}
	instances[selectedInstanceIndex]->debugNABMode = !instances[selectedInstanceIndex]->debugNABMode;
}

