#include "GOTransform.h"




GOTransform::GOTransform()
{
	origin = vector3(0);
	position = vector3(0);
	scale = vector3(1);
	orientation = quaternion();
}


GOTransform::~GOTransform()
{
	std::vector<GOTransform*>::iterator it;
	for (it = children.begin(); it != children.end(); ++it) {
		if ((*it) != nullptr) {
			GOTransform* transform = *it;
			delete transform;
		}
	}
}

void GOTransform::calculateMatrix()
{
	matrix = glm::translate(position) * ToMatrix4(orientation) * glm::translate(GetOrigin()*(-1.0f)) * glm::scale(scale);
}


void GOTransform::SetOrigin(vector3 origin)
{
	this->origin = origin;
	calculateMatrix();
}

vector3 GOTransform::GetOrigin() const
{
	return vector3(origin.x * scale.x, origin.y * scale.y, origin.z * scale.z);
}

const vector3& GOTransform::GetLocalPosition() const
{
	return position;
}

const vector3 GOTransform::GetPosition() const
{
	return parent != nullptr ? parent->GetPosition() + position : position;
}

const vector3& GOTransform::GetLocalScale() const
{
	return scale;
}

const vector3 GOTransform::GetScale() const
{
	return parent != nullptr ? parent->GetScale() * scale : scale;
}

const quaternion& GOTransform::GetLocalRotation() const
{
	return orientation;
}

const quaternion GOTransform::GetRotation() const
{
	return  parent != nullptr ? orientation * parent->GetRotation() : orientation;
}

void GOTransform::SetPosition(vector3 position)
{
	this->position = position;
	calculateMatrix();
}

void GOTransform::SetScale(vector3 scale)
{
	this->scale = scale;
	calculateMatrix();
}

const matrix4& GOTransform::GetLocalMatrix() const
{
	return matrix;
}

const matrix4 GOTransform::GetMatrix() const
{
	return parent != nullptr ? parent->GetMatrix() * matrix : matrix;
}

void GOTransform::Rotate(quaternion rotation)
{
	this->orientation = glm::normalize(rotation * this->orientation);
	calculateMatrix();
}

void GOTransform::RotateTo(quaternion rotation)
{
	this->orientation = rotation;
	calculateMatrix();
}

void GOTransform::RemoveChild(GOTransform * child)
{
	if (child->GetParent() == this) {
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
		child->RemoveParent();
	}
	
}

const GOTransform * GOTransform::GetParent() const
{
	return parent;
}

void GOTransform::AddChild(GOTransform * child)
{
	children.push_back(child);
	if (child->GetParent() != this) {
		child->SetParent(this);
	}
}

void GOTransform::SetParent(GOTransform * parent)
{
	if (this->parent == parent)
		return;

	if (this->parent != nullptr) {
		parent->RemoveChild(this);
	}

	parent->AddChild(this);
	this->parent = parent;
}

void GOTransform::RemoveParent()
{
	if (parent != nullptr) {
		parent->RemoveChild(this);
		parent = nullptr;
	}
	
}

void GOTransform::RotateTo(vector3 orientation)
{
	this->orientation = quaternion(orientation);
	calculateMatrix();
}

void GOTransform::Translate(vector3 displacement)
{
	position += displacement;
	calculateMatrix();
}

void GOTransform::Scale(float scale)
{
	this->scale *= vector3(scale);
	calculateMatrix();
}

void GOTransform::Scale(vector3 scale)
{
	this->scale = vector3(this->scale.x * scale.x, this->scale.y * scale.y, this->scale.z * scale.z);
	calculateMatrix();
}