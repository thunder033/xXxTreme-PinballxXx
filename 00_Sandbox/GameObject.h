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

	bool hasFrameCollisions;
	vector3 debugColor;

	static std::vector<GameObject*> instances;
	static bool debugMode;
	static MeshManagerSingleton* renderer;
public:
	GameObject();
	GameObject(MeshClass*);
	~GameObject();

	vector3 getOrigin();

	vector3 getPosition();

	matrix4 getTransform();

	void update(double);

	void render(matrix4, matrix4);

	void renderDebugHelpers();

	//Static GameObject Methods
	//a.k.a BoundingObjectManager
	static void init();
	static void updateAll(double);

	static void renderAll(matrix4, matrix4);

	static void setDebugMode(bool);
};

