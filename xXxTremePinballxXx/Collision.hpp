#pragma once
#include "RE\ReEngAppClass.h"

class GameObject;

struct CollisionEvent {
	vector3 intersectPt;
	vector3 penetrationVector;
	vector3 collideeIntersectPt;
	GameObject* collidee;
};

struct Collision {
	vector3 intersectPoint1;
	vector3 penetrationVector;
	vector3 intersectPoint2;

	GameObject* collider1;
	GameObject* collider2;
	bool colliding;

	const CollisionEvent GetEvent(const GameObject* obj) {
		CollisionEvent evt = CollisionEvent();
		if (obj == collider1) {
			evt.collidee = collider2;
			evt.intersectPt = intersectPoint1;
			evt.collideeIntersectPt = intersectPoint2;
			evt.penetrationVector = penetrationVector;
		}
		else {
			evt.collidee = collider1;
			evt.intersectPt = intersectPoint2;
			evt.collideeIntersectPt = intersectPoint1;
			evt.penetrationVector = -penetrationVector;
		}
		return evt;
	}
};