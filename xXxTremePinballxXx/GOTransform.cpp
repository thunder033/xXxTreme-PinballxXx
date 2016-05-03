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

const vector3& GOTransform::GetPosition() const
{
	return position;
}

const vector3& GOTransform::GetScale() const
{
	return scale;
}

const quaternion& GOTransform::GetRotation() const
{
	return orientation;
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

const matrix4& GOTransform::GetMatrix() const
{
	return matrix;
}

void GOTransform::Rotate(quaternion rotation)
{
	this->orientation = this->orientation * rotation;
	calculateMatrix();
}

void GOTransform::RotateTo(quaternion rotation)
{
	this->orientation = rotation;
	calculateMatrix();
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