#include "RE\ReEngAppClass.h"
#include "Collider.h"
#define AABB 0
#define NAB 1

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
	bool debugAABBMode;
	bool debugNABMode;

	static std::vector<GameObject*> instances;
	static int selectedInstanceIndex;
	static MeshManagerSingleton* renderer;
public:
	GameObject();
	GameObject(MeshClass*);
	~GameObject();

	vector3 getOrigin();

	vector3 getPosition();

	matrix4 getTransform();

	void setDebugColor(vector3 newColor);

	void update(double);

	void render(matrix4, matrix4);

	void renderAABBDebugHelpers();

	void renderNABDebugHelpers();

	//Static GameObject Methods
	//a.k.a BoundingObjectManager
	static void init();
	static void updateAll(double);

	static void renderAll(matrix4, matrix4);

	static void setAABBDebugMode(bool);

	static void setNABDebugMode(bool);

	static void cycleSelectedIndex(bool);

	static void setSelectedColor(vector3);

	static void toggleSelectedDebugMode(int);
};

