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

//class Entity;
class GameObject
{
	const int id;
	MeshClass* mesh;

	vector3 debugColor;
	bool debugAABBMode;
	bool debugNABMode;
	
	static int selectedInstanceIndex;
	static int curID;

	class OctNode* parent = nullptr;
protected:
	Collider* collider;
	void Scale(vector3);
	GOTransform* transform;
	vector3 velocity;
	vector3 acceleration;
	bool hasFrameCollisions;
	std::unordered_map<int, std::shared_ptr<Collision>> frameCollisions;

	static MeshManagerSingleton* renderer;
	static std::vector<GameObject*> instances;
	static int checkCount;
public:
	GameObject();
	GameObject(MeshClass*);
	virtual ~GameObject();

	OctNode* GetOctNode();
	void SetOctNode(OctNode*);

	virtual ObjectType GetType();

	/*
	Sets the origin of the game object, which indicates how 
	far from the center rotations and scales will be performed
	*/
	const int GetID();

	void SetOrigin(vector3);

	vector3 GetOrigin() const;

	const vector3 GetPosition() const;

	const quaternion GetRotation() const;

	GOTransform* GetTransform() const;

	void SetDebugColor(vector3 newColor);

	void Rotate(quaternion);

	void Translate(vector3);

	void Scale(float);

	void RotateTo(vector3);

	void RotateTo(quaternion);

	virtual void Update(double);

	void AddFrameCollision(int id, std::shared_ptr<Collision> collision);

	virtual void OnCollision(const CollisionEvent&);

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

	static const std::vector<GameObject*>& GetInstances();

	static void ReleaseInstances();
};

#endif