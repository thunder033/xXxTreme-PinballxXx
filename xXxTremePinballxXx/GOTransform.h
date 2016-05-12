#include "RE\ReEngAppClass.h"
#pragma once
class GOTransform
{
	vector3 origin;
	vector3 position;
	vector3 scale;
	quaternion orientation;
	matrix4 matrix;

	void calculateMatrix();

	GOTransform* parent;
	std::vector<GOTransform*> children;

public:
	GOTransform();
	~GOTransform();

	const matrix4 GetMatrix() const;

	const matrix4& GetLocalMatrix() const;

	/*
	Sets the origin of the game object, which indicates how
	far from the center rotations and scales will be performed
	*/
	void SetOrigin(vector3);

	vector3 GetOrigin() const;

	const vector3 GetPosition() const;

	const vector3 GetScale() const;

	const quaternion GetRotation() const;

	const vector3& GetLocalPosition() const;

	const vector3& GetLocalScale() const;

	const quaternion& GetLocalRotation() const;

	void SetPosition(vector3 position);

	void SetScale(vector3 scale);

	void Translate(vector3 offset);

	void Scale(float scale);

	void Scale(vector3 scale);

	void Rotate(quaternion rotation);

	void RotateTo(vector3 orientation);

	void RotateTo(quaternion orientation);

	void RemoveChild(GOTransform* child);

	const GOTransform* GetParent() const;

	void AddChild(GOTransform* child);

	void SetParent(GOTransform* parent);

	void RemoveParent();
};

