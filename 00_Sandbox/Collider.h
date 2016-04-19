/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __Collider_H_
#define __Collider_H_

#include "RE\ReEngAppClass.h"


//System Class
class Collider
{
	float radius = 0.0f; //Radius of the Bounding Sphere
	matrix4 worldTransform = IDENTITY_M4; //Matrix that will take us from local to world coordinate
	vector3 origin = vector3(0.0f); //Will store the center point of the Sphere Class
	vector3 min = vector3(0.0f); //Will store the minimum vector of the Sphere Class
	vector3 max = vector3(0.0f); //Will store the maximum vector of the Sphere Class
	vector3 size = vector3(0.0f);
	vector3 alignedSize = vector3(0.0f);
	quaternion rotation = quaternion();

	void GetMinMax(vector3& min, vector3& max, std::vector<vector3> points);
public:
	/*
	Collider
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Collider(std::vector<vector3> a_lVectorList);
	/*
	Collider
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	Collider(Collider const& other);
	/*
	operator=
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	Collider& operator=(Collider const& other);
	/*
	~Collider
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Collider(void);

	/*
	Swap
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(Collider& other);

	/*
	SetToWorldMatrix
	USAGE: Sets the Bounding Sphere into world coordinates
	ARGUMENTS:
	matrix4 a_m4ToWorld -> Model to World matrix
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	GetCenter
	USAGE: Gets the Bounding Sphere's center in world coordinates
	ARGUMENTS: ---
	OUTPUT: vector3 -> Center's of the sphere in world coordinates
	*/
	vector3 GetCenter(void);

	/*
	GetRadius
	USAGE: Gets the Bounding Sphere's radius
	ARGUMENTS: ---
	OUTPUT: float -> radius of the Bounding Sphere
	*/
	float GetRadius(void);

	std::vector<vector3> Rotate(quaternion);
	vector3 GetSize(void);
	matrix4 GetRot(void);
	matrix4 GetAxisAlignedTransform(void);
	vector3 GetMin();
	vector3 GetMax();

	/*
	IsColliding
	USAGE: Asks if there is a collision with another Bounding sphere Object
	ARGUMENTS:
	Collider* const a_pOther -> Other object to check collision with
	OUTPUT: bool -> check of the collision
	*/
	bool isColliding(Collider* const a_pOther);

private:
	/*
	Release
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	Init
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

#endif //__Collider_H__