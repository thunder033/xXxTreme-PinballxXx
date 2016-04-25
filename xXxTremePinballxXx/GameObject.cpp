#include "GameObject.h"

std::vector<GameObject*> GameObject::instances;
MeshManagerSingleton* GameObject::renderer;
int GameObject::selectedInstanceIndex;

GameObject::GameObject() : GameObject(new PrimitiveClass())
{
	(static_cast<PrimitiveClass*>(mesh))->GenerateCube(1, REWHITE);
	collider = new Collider(mesh->GetVertexList(), transform);
}

GameObject::GameObject(MeshClass * mesh)
{
	this->mesh = mesh;
	transform = new GOTransform();

	velocity = vector3(0);
	acceleration = vector3(0);

	hasFrameCollisions = false;
	debugColor = REGREEN;

	GameObject::instances.push_back(this);
	collider = new Collider(mesh->GetVertexList(), transform);

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
	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}
}

void GameObject::SetOrigin(vector3 origin)
{
	transform->SetOrigin(origin);
}

vector3 GameObject::GetOrigin()
{
	return transform->GetOrigin();
}

vector3 GameObject::GetPosition()
{
	return transform->GetPosition();
}

quaternion GameObject::GetRotation()
{
	return transform->GetRotation();
}

GOTransform* GameObject::GetTransform()
{
	return transform;
}

void GameObject::SetDebugColor(vector3 newColor) 
{
	debugColor = newColor;
}

void GameObject::Rotate(quaternion rotation)
{
	transform->Rotate(rotation);
	collider->calculateAABB();
}

void GameObject::RotateTo(quaternion orientation)
{
	transform->RotateTo(orientation);
	collider->calculateAABB();
}

void GameObject::RotateTo(vector3 orientation)
{
	transform->RotateTo(orientation);
	collider->calculateAABB();
}

void GameObject::Translate(vector3 displacement)
{
	transform->Translate(displacement);
}

void GameObject::Scale(float scale)
{
	transform->Scale(scale);
	collider->calculateAABB();
}

void GameObject::Scale(vector3 scale)
{
	transform->Scale(scale);
	collider->calculateAABB();
}

void GameObject::Update(double deltaTime)
{
	velocity += acceleration * static_cast<float>(deltaTime);
	Translate(velocity * static_cast<float>(deltaTime));
	hasFrameCollisions = false;

	for (std::vector<GameObject*>::iterator it = instances.begin(); it != instances.end(); ++it)
	{
		if (*it == this)
			continue;

		bool colliding = (*it)->collider->IsColliding(this->collider);
		hasFrameCollisions = hasFrameCollisions || colliding;
	}
}

void GameObject::Render(matrix4 projection, matrix4 view)
{
	mesh->Render(projection, view, transform->GetMatrix());
}

void GameObject::RenderAABBDebugHelpers()
{
	vector3 color = hasFrameCollisions ? RERED : debugColor;
	renderer->AddCubeToQueue(collider->GetAxisAlignedTransform(), color, WIRE);
}

void GameObject::RenderNABDebugHelpers()
{
	vector3 color = hasFrameCollisions ? RERED : debugColor;
	renderer->AddCubeToQueue(transform->GetMatrix() * glm::scale(collider->GetSize()), color, WIRE);
}

/*
***BEGIN STATIC (BOUNDING BOX MANAGER) METHODS***
*/
void GameObject::Init()
{
	renderer = MeshManagerSingleton::GetInstance();
	instances = std::vector<GameObject*>();
	selectedInstanceIndex = 0;
}

void GameObject::UpdateAll(double deltaTime)
{
	for (std::vector<GameObject*>::iterator it = instances.begin(); it != instances.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void GameObject::RenderAll(matrix4 projection, matrix4 view)
{
	for (std::vector<GameObject*>::iterator it = instances.begin(); it != instances.end(); ++it)
	{
		(*it)->Render(projection, view);

		if ((*it)->debugAABBMode)
			(*it)->RenderAABBDebugHelpers();

		if ((*it)->debugNABMode)
			(*it)->RenderNABDebugHelpers();
	}
}

void GameObject::ToggleDebugMode(int colliderType)
{
	if (colliderType == CT_AABB)
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
void GameObject::CycleSelectedIndex(bool direction)
{
	SetSelectedColor(REGREEN);
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
	SetSelectedColor(REYELLOW);
}

void GameObject::SetSelectedColor(vector3 newColor)
{
	instances[selectedInstanceIndex]->SetDebugColor(newColor);
}

void GameObject::ToggleSelectedDebugMode(int colliderType)
{
	if (colliderType)
	{
		instances[selectedInstanceIndex]->debugAABBMode = !instances[selectedInstanceIndex]->debugAABBMode;
		return;
	}
	instances[selectedInstanceIndex]->debugNABMode = !instances[selectedInstanceIndex]->debugNABMode;
}

int GameObject::GetGameObjectCount()
{
	return instances.size();
}

