#include "OctNode.h"



OctNode::OctNode(Octree* octree)
{
	this->octTree = octree;
	this->leaves = nullptr;
	this->containedObjects = nullptr;
}

OctNode::~OctNode()
{
}

void OctNode::GenerateLeaves()
{
	leaves = (OctNode**)malloc(sizeof(OctNode*) * 8);
	for (int i = 0; i < 8; ++i)
	{
		*(leaves[i]) = OctNode(this->octTree);
	}
}

bool OctNode::isLeaf()
{
	return !leaves;
}

OctNode* OctNode::GetLeaf(int whichLeaf)
{
	if (whichLeaf < 0 || whichLeaf > 7) return nullptr;
	if (leaves != nullptr) return leaves[whichLeaf];
	return nullptr;
}

void OctNode::AddObjects(GameObject **objects)
{
	this->containedObjects = objects;
}


Octree::Octree(vector3 min, vector3 max, int minObjects)
{
	this->head = new OctNode(this);
	this->minBoundary = min;
	this->maxBoundary = max;
	this->maxObjects = minObjects;
}

Octree::~Octree()
{

}

void RecurDrawTree(OctNode *start, vector3 min, vector3 max)
{
	if (start != nullptr)
	{
		if (start->isLeaf())
		{
			MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate((max + min) / 2.f) * glm::scale(max - min), REYELLOW, WIRE);
		}
		else
		{
			RecurDrawTree(start->GetLeaf(0), min, ((min + max) / 2.f));
			RecurDrawTree(start->GetLeaf(1), min + vector3((max.x + min.x) / 2.f, 0.0f, 0.0f),
				((min + max) / 2.f) + vector3((max.x + min.x) / 2.f, 0.0f, 0.0f));
			RecurDrawTree(start->GetLeaf(2), min + vector3(0.f, 0.f, (max.z + min.z) / 2.f),
				((min + max) / 2.f) + vector3(0.f, 0.f, (max.z + min.z) / 2.f));
			RecurDrawTree(start->GetLeaf(3), min + vector3((max.x + min.x) / 2.f, 0.f, (max.z + min.z) / 2.f),
				((min + max) / 2.f) + vector3((max.x + min.x) / 2.f, 0.0f, (max.z + min.z) / 2.f));


			RecurDrawTree(start->GetLeaf(4), ((min + max) / 2.f), max);
			RecurDrawTree(start->GetLeaf(5), ((min + max) / 2.f) - vector3((max.x + min.x) / 2.f, 0.0f, 0.0f),
				max - vector3((max.x + min.x) / 2.f, 0.0f, 0.0f));
			RecurDrawTree(start->GetLeaf(6), ((min + max) / 2.f) - vector3(0.f, 0.f, (max.z + min.z) / 2.f),
				max - vector3(0.f, 0.f, (max.z + min.z) / 2.f));
			RecurDrawTree(start->GetLeaf(7), ((min + max) / 2.f) - vector3((max.x + min.x) / 2.f, 0.f, (max.z + min.z) / 2.f),
				max - vector3((max.x + min.x) / 2.f, 0.0f, (max.z + min.z) / 2.f));
		}
	}
}

void Octree::DrawOctree()
{
	MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate((maxBoundary + minBoundary) / 2.f) * glm::scale(maxBoundary - minBoundary), REYELLOW, WIRE);
	RecurDrawTree(this->head, minBoundary, maxBoundary);
}

int Octree::GetMaxObjects()
{
	return this->maxObjects;
}