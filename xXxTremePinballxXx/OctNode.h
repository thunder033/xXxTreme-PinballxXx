#pragma once
#include "RE\ReEngAppClass.h"
#include "GameObject.h"

class Octree;

class OctNode
{
public:
	OctNode(Octree* octree, OctNode* parent);
	~OctNode();
	void GenerateLeaves();
	bool isLeaf();
	bool hasObjects();
	OctNode* GetLeaf(int whichLeaf);
	void AddObjects(const std::vector<GameObject*> &objects);
	OctNode* GetParent();
	const std::vector<GameObject*>& GetObjects() const;
private:
	Octree* octTree;
	std::vector<GameObject*> containedObjects;
	OctNode** leaves;
	OctNode* parent;
};

class Octree
{
public:
	Octree(vector3, vector3, int);
	~Octree();
	void DrawOctree();
	int GetMaxObjects();
	void GenerateTree();
	std::vector<GameObject*> nearbyObjects(GameObject*);
	bool enabled = true;
private:
	OctNode* head;
	vector3 minBoundary;
	vector3 maxBoundary;
	uint maxObjects;
};

