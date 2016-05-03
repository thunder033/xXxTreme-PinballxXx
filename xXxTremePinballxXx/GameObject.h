#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "RE\ReEngAppClass.h"
#include "Collider.h"
#include "GOTransform.h"
#define CT_AABB 0
#define CT_NAB 1

enum class ObjectType
{
	Default,
	Flipper,
	Ball
};


class GameObject
{

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
	vector3 velocity;
	vector3 acceleration;
public:
	GameObject();
	GameObject(MeshClass*);
	virtual ~GameObject();

	virtual ObjectType GetType();

	/*
	Sets the origin of the game object, which indicates how 
	far from the center rotations and scales will be performed
	*/
	void SetOrigin(vector3);

	const vector3& GetVelocity() const;

	void SetVelocity(const vector3& newVelocity);

	vector3 GetOrigin() const;

	const vector3& GetPosition() const;

	const quaternion& GetRotation() const;

	GOTransform* GetTransform() const;

	void SetDebugColor(vector3 newColor);

	void Rotate(quaternion);

	void Translate(vector3);

	void Scale(float);

	void RotateTo(vector3);

	void RotateTo(quaternion);

	virtual void Update(double);

	virtual void OnCollision(vector3, GameObject*);

	void Render(matrix4, matrix4);

	void RenderAABBDebugHelpers();

	void RenderNABDebugHelpers();

	inline Collider* GetCollider()
	{
		return collider;
	}

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

#endif