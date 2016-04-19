#include "RE\ReEngAppClass.h"
#include "Collider.h"

#pragma once
class GameObject
{
	vector3 origin;
	vector3 position;
	vector3 velocity;
	vector3 acceleration;

	vector3 scale;
	quaternion rotation;

	float mass;
	float elasictiy;

	Collider* collider;
	MeshClass* mesh;

	static std::vector<GameObject*> instances;
public:
	GameObject();
	~GameObject();

	vector3 getOrigin();

	vector3 getPosition();

	matrix4 getTransform();

	void update(double);

	void render(matrix4, matrix4);

	void RenderDebugHelpers();

	static void updateAll(double);

	static void renderAll(matrix4, matrix4);
};

