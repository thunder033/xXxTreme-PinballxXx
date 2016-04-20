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

	vector3 GetOrigin();

	vector3 GetPosition();

	quaternion GetRotation();

	matrix4 GetTransform();

	void SetDebugColor(vector3 newColor);

	void Rotate(quaternion);

	void Translate(vector3);

	void Scale(float);

	void RotateTo(vector3);

	void RotateTo(quaternion);

	void Update(double);

	void Render(matrix4, matrix4);

	void RenderAABBDebugHelpers();

	void RenderNABDebugHelpers();

	//Static GameObject Methods
	//a.k.a BoundingObjectManager
	static void Init();
	static void UpdateAll(double);

	static void RenderAll(matrix4, matrix4);

	static void ToggleDebugMode(int colliderType);

	static void CycleSelectedIndex(bool);

	static void SetSelectedColor(vector3);

	static void ToggleSelectedDebugMode(int);
};

