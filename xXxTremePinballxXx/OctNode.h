#pragma once
#include "AppClass.h"

class Octree;

class OctNode
{
public:
	OctNode(Octree* octree);
	~OctNode();
	void GenerateLeaves();
	bool isLeaf();
	OctNode* GetLeaf(int whichLeaf);
	void AddObjects(GameObject**);
private:
	Octree* octTree;
	GameObject** containedObjects;
	OctNode** leaves;
};

class Octree
{
public:
	Octree(vector3, vector3, int);
	~Octree();
	void DrawOctree();
	int GetMaxObjects();
private:
	OctNode* head;
	vector3 minBoundary;
	vector3 maxBoundary;
	int maxObjects;
};

