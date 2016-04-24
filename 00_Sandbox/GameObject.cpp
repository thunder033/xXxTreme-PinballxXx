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

	origin = vector3(0);
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

void GameObject::SetOrigin(vector3 origin)
{
	this->origin = origin;
	collider->SetPosition(vector3(GetTransform()[3]));
}

vector3 GameObject::GetOrigin()
{
	return vector3(origin.x * scale.x, origin.y * scale.y, origin.z * scale.z);
}

vector3 GameObject::GetPosition()
{
	return position;
}

quaternion GameObject::GetRotation()
{
	return rotation;
}

matrix4 GameObject::GetTransform()
{
	return glm::translate(position) * ToMatrix4(rotation) * glm::translate(GetOrigin()*(-1.0f)) * glm::scale(scale);
}

void GameObject::SetDebugColor(vector3 newColor) 
{
	debugColor = newColor;
}

void GameObject::Rotate(quaternion rotation)
{
	this->rotation = this->rotation * rotation;
	collider->RotateTo(this->rotation);
}

void GameObject::RotateTo(quaternion rotation)
{
	this->rotation = rotation;
	collider->RotateTo(rotation);
}

void GameObject::RotateTo(vector3 orientation)
{
	this->rotation = quaternion(orientation);
	collider->RotateTo(rotation);
}

void GameObject::Translate(vector3 displacement)
{
	position += displacement;
	collider->SetPosition(vector3(GetTransform()[3]));
}

void GameObject::Scale(float scale)
{
	this->scale *= vector3(scale);
	collider->SetScale(this->scale);
}

void GameObject::Scale(vector3 scale)
{
	this->scale = vector3(this->scale.x * scale.x, this->scale.y * scale.y, this->scale.z * scale.z);
	collider->SetScale(this->scale);
}

void GameObject::Update(double deltaTime)
{
	velocity += acceleration * static_cast<float>(deltaTime);
	Translate(velocity * static_cast<float>(deltaTime));
	hasFrameCollisions = false;
	collider->SetModelMatrix(GetTransform());

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
	mesh->Render(projection, view, GetTransform());
}

void GameObject::RenderAABBDebugHelpers()
{
	vector3 color = hasFrameCollisions ? RERED : debugColor;
	renderer->AddCubeToQueue(collider->GetAxisAlignedTransform(), color, WIRE);
}

void GameObject::RenderNABDebugHelpers()
{
	vector3 color = hasFrameCollisions ? RERED : debugColor;
	renderer->AddCubeToQueue(GetTransform() * glm::scale(collider->GetSize()), color, WIRE);
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

