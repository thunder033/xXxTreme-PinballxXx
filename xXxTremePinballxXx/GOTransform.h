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

public:
	GOTransform();
	~GOTransform();

	const matrix4& GetMatrix() const;

	/*
	Sets the origin of the game object, which indicates how
	far from the center rotations and scales will be performed
	*/
	void SetOrigin(vector3);

	vector3 GetOrigin() const;

	const vector3& GetPosition() const;

	const vector3& GetScale() const;

	const quaternion& GetRotation() const;

	void SetPosition(vector3);

	void SetScale(vector3);

	void Translate(vector3);

	void Scale(float);

	void Scale(vector3);

	void Rotate(quaternion);

	void RotateTo(vector3);

	void RotateTo(quaternion);
};

