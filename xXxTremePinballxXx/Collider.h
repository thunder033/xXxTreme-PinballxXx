/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __Collider_H_
#define __Collider_H_

#include "RE\ReEngAppClass.h"
#include "GOTransform.h"

struct OBB
{
	vector3 c;
	matrix3 u;
	vector3 e;
};

enum class ColliderType
{
	Circle = 0,
	AABB
};
//System Class
class Collider
{
	float radius = 0.0f; //Radius of the Bounding Sphere
	vector3 centroid = vector3(0.0f); //Will store the center point of the Sphere Class
	vector3 min = vector3(0.0f); //Will store the minimum vector of the Sphere Class
	vector3 max = vector3(0.0f); //Will store the maximum vector of the Sphere Class
	vector3 size = vector3(0.0f);
	vector3 alignedSize = vector3(0.0f);
	vector3 lastCollision;
	GOTransform* transform;
	ColliderType type = ColliderType::AABB;

	void GetMinMax(vector3& min, vector3& max, std::vector<vector3> points);
public:
	/*
	Collider
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Collider(std::vector<vector3> a_lVectorList, GOTransform* transform);
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

	vector3 GetSize(void);
	matrix4 GetAxisAlignedTransform(void);
	vector3 GetMin();
	vector3 GetMax();
	std::vector<vector3> GetBoundingBox();
	void setType(ColliderType);
	void calculateAABB();
	vector3 GetLastCollision();

	OBB CreateOBB();

	/*
	IsColliding
	USAGE: Asks if there is a collision with another Bounding sphere Object
	ARGUMENTS:
	Collider* const a_pOther -> Other object to check collision with
	OUTPUT: bool -> check of the collision
	*/
	bool IsColliding(Collider* const a_pOther);

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