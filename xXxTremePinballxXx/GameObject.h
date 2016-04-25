#include "RE\ReEngAppClass.h"
#include "Collider.h"
#include "GOTransform.h"
#define CT_AABB 0
#define CT_NAB 1

#pragma once
class GameObject
{
	vector3 velocity;
	vector3 acceleration;

	float mass;
	float elasictiy;

	MeshClass* mesh;

	bool hasFrameCollisions;
	vector3 debugColor;
	bool debugAABBMode;
	bool debugNABMode;

	static std::vector<GameObject*> instances;
	static int selectedInstanceIndex;
	static MeshManagerSingleton* renderer;
protected:
	Collider* collider;
	void Scale(vector3);
	GOTransform* transform;
public:
	GameObject();
	GameObject(MeshClass*);
	virtual ~GameObject();

	/*
	Sets the origin of the game object, which indicates how 
	far from the center rotations and scales will be performed
	*/
	void SetOrigin(vector3);

	inline vector3 GetOrigin();

	inline vector3 GetPosition();

	inline quaternion GetRotation();

	GOTransform* GetTransform();

	void SetDebugColor(vector3 newColor);

	void Rotate(quaternion);

	inline void Translate(vector3);

	void Scale(float);

	void RotateTo(vector3);

	void RotateTo(quaternion);

	virtual void Update(double);

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

	static int GetGameObjectCount();
};

