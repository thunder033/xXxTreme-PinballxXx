#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "RE\ReEngAppClass.h"
#include "Collider.h"
#include "Collision.hpp"
#include "GOTransform.h"
#include <unordered_map>
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
	const int id;
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
	static int curID;
	static int checkCount;
protected:
	Collider* collider;
	void Scale(vector3);
	GOTransform* transform;
	vector3 velocity;
	vector3 acceleration;
	std::unordered_map<int, Collision*> frameCollisions;
	void AddFrameCollision(int, Collision*);
public:
	GameObject();
	GameObject(MeshClass*);
	virtual ~GameObject();

	virtual ObjectType GetType();

	/*
	Sets the origin of the game object, which indicates how 
	far from the center rotations and scales will be performed
	*/
	const int GetID();

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

	virtual void OnCollision(const CollisionEvent);

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

	static int GetCheckCount();
};

#endif