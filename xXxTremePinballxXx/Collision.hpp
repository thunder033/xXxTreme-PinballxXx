#pragma once
#include "RE\ReEngAppClass.h"

class GameObject;
struct Collision {
	vector3 intersectPoint1;
	vector3 penetrationVector;
	vector3 intersectPoint2;

	GameObject* collider1;
	GameObject* collider2;
	bool colliding;
};