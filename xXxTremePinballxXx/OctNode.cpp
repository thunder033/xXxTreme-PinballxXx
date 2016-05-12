#include "OctNode.h"



OctNode::OctNode(Octree* octree, OctNode* parent)
{
	this->octTree = octree;
	this->leaves = nullptr;
	this->parent = parent;
}

OctNode::~OctNode()
{
	if (leaves)
	{
		free(leaves);
	}
}

void OctNode::GenerateLeaves()
{
	leaves = (OctNode**)malloc(sizeof(OctNode*) * 8);
	for (int i = 0; i < 8; ++i)
	{
		leaves[i] = new OctNode(this->octTree, this);
	}
}

bool OctNode::isLeaf()
{
	return !leaves;
}

bool OctNode::hasObjects()
{
	return containedObjects.size() > 0;
}

OctNode* OctNode::GetLeaf(int whichLeaf)
{
	if (whichLeaf < 0 || whichLeaf > 7) return nullptr;
	if (leaves != nullptr) return leaves[whichLeaf];
	return nullptr;
}

void OctNode::AddObjects(const std::vector<GameObject*> &objects)
{
	this->containedObjects = objects;
}

OctNode * OctNode::GetParent()
{
	return this->parent;
}

const std::vector<GameObject*>& OctNode::GetObjects() const
{
	return this->containedObjects;
}


Octree::Octree(vector3 min, vector3 max, int maxObjects)
{
	this->head = new OctNode(this, nullptr);
	this->minBoundary = min;
	this->maxBoundary = max;
	this->maxObjects = maxObjects;
}

void deleteHelper(OctNode* tempHead)
{
	if (tempHead->isLeaf())
	{
		delete tempHead;
	}
	else
	{
		deleteHelper(tempHead->GetLeaf(0));
		deleteHelper(tempHead->GetLeaf(1));
		deleteHelper(tempHead->GetLeaf(2));
		deleteHelper(tempHead->GetLeaf(3));
		deleteHelper(tempHead->GetLeaf(4));
		deleteHelper(tempHead->GetLeaf(5));
		deleteHelper(tempHead->GetLeaf(6));
		deleteHelper(tempHead->GetLeaf(7));
	}
}

Octree::~Octree()
{
	deleteHelper(head);
}

void RecurDrawTree(OctNode *start, vector3 min, vector3 max)
{
	if (start != nullptr)
	{
		if (start->isLeaf())
		{
			MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate((max + min) / 2.f) * glm::scale(max - min), /*glm::length(max) == 0 ?*/ REYELLOW /*: glm::normalize(max))*/, WIRE);
		}
		else
		{
			if (start->hasObjects())
				MeshManagerSingleton::GetInstance()->AddCubeToQueue(glm::translate((max + min) / 2.f) * glm::scale(max - min), /*glm::length(max) == 0 ?*/ REYELLOW /*: glm::normalize(max))*/, WIRE);
			RecurDrawTree(start->GetLeaf(0), min, ((min + max) / 2.f));
			RecurDrawTree(start->GetLeaf(1), min + vector3((max.x - min.x) / 2.f, 0.0f, 0.0f),
				((min + max) / 2.f) + vector3((max.x - min.x) / 2.f, 0.0f, 0.0f));
			RecurDrawTree(start->GetLeaf(2), min + vector3(0.f, 0.f, (max.z - min.z) / 2.f),
				((min + max) / 2.f) + vector3(0.f, 0.f, (max.z - min.z) / 2.f));
			RecurDrawTree(start->GetLeaf(3), min + vector3((max.x - min.x) / 2.f, 0.f, (max.z - min.z) / 2.f),
				((min + max) / 2.f) + vector3((max.x - min.x) / 2.f, 0.0f, (max.z - min.z) / 2.f));


			RecurDrawTree(start->GetLeaf(4), ((min + max) / 2.f), max);
			RecurDrawTree(start->GetLeaf(5), ((min + max) / 2.f) - vector3((max.x - min.x) / 2.f, 0.0f, 0.0f),
				max - vector3((max.x - min.x) / 2.f, 0.0f, 0.0f));
			RecurDrawTree(start->GetLeaf(6), ((min + max) / 2.f) - vector3(0.f, 0.f, (max.z - min.z) / 2.f),
				max - vector3(0.f, 0.f, (max.z - min.z) / 2.f));
			RecurDrawTree(start->GetLeaf(7), ((min + max) / 2.f) - vector3((max.x - min.x) / 2.f, 0.f, (max.z - min.z) / 2.f),
				max - vector3((max.x - min.x) / 2.f, 0.0f, (max.z - min.z) / 2.f));
		}
	}
}

void Octree::DrawOctree()
{
	if (!enabled)
		return;

	RecurDrawTree(this->head, minBoundary, maxBoundary);
}

int Octree::GetMaxObjects()
{
	return this->maxObjects;
}

void generateHelper(uint maxObjects, std::vector<GameObject*> &objects, OctNode* start,  vector3 min, vector3 max)
{
	if (objects.size() > 0)
	{
		std::vector<GameObject*> containedObjects = std::vector<GameObject*>();
		for (GameObject* temp : objects)
		{
			vector3 tempMin = temp->GetCollider()->GetAABBMin() + temp->GetPosition();
			vector3 tempMax = temp->GetCollider()->GetAABBMax() + temp->GetPosition();
			if (tempMin.x >= min.x && tempMax.x <= max.x &&
				tempMin.y >= min.y && tempMax.y <= max.y &&
				tempMin.z >= min.z && tempMax.z <= max.z)
			{
				containedObjects.push_back(temp);
			}
		}
		if (containedObjects.size() > maxObjects)
		{
			start->GenerateLeaves();
			generateHelper(maxObjects, containedObjects, start->GetLeaf(0), min, ((min + max) / 2.f));
			generateHelper(maxObjects, containedObjects, start->GetLeaf(1), min + vector3((max.x - min.x) / 2.f, 0.0f, 0.0f),
				((min + max) / 2.f) + vector3((max.x - min.x) / 2.f, 0.0f, 0.0f));
			generateHelper(maxObjects, containedObjects, start->GetLeaf(2), min + vector3(0.f, 0.f, (max.z - min.z) / 2.f),
				((min + max) / 2.f) + vector3(0.f, 0.f, (max.z - min.z) / 2.f));
			generateHelper(maxObjects, containedObjects, start->GetLeaf(3), min + vector3((max.x - min.x) / 2.f, 0.f, (max.z - min.z) / 2.f),
				((min + max) / 2.f) + vector3((max.x - min.x) / 2.f, 0.0f, (max.z - min.z) / 2.f));


			generateHelper(maxObjects, containedObjects, start->GetLeaf(4), ((min + max) / 2.f), max);
			generateHelper(maxObjects, containedObjects, start->GetLeaf(5), ((min + max) / 2.f) - vector3((max.x - min.x) / 2.f, 0.0f, 0.0f),
				max - vector3((max.x - min.x) / 2.f, 0.0f, 0.0f));
			generateHelper(maxObjects, containedObjects, start->GetLeaf(6), ((min + max) / 2.f) - vector3(0.f, 0.f, (max.z - min.z) / 2.f),
				max - vector3(0.f, 0.f, (max.z - min.z) / 2.f));
			generateHelper(maxObjects, containedObjects, start->GetLeaf(7), ((min + max) / 2.f) - vector3((max.x - min.x) / 2.f, 0.f, (max.z - min.z) / 2.f),
				max - vector3((max.x - min.x) / 2.f, 0.0f, (max.z - min.z) / 2.f));
		}
		if (containedObjects.size() > 0)
		{
			for (GameObject* temp : containedObjects)
			{
				if (std::find(objects.begin(), objects.end(), temp) != objects.end())
					objects.erase(std::remove(objects.begin(), objects.end(), temp), objects.end());
				temp->SetOctNode(start);
			}
			start->AddObjects(containedObjects);
		}
	}
}

void Octree::GenerateTree()
{
	std::vector<GameObject*> objects = GameObject::GetInstances();
	generateHelper(this->maxObjects, objects, this->head, this->minBoundary, this->maxBoundary);

	/*
	this->head = new OctNode(this);
	this->head->GenerateLeaves();
	this->head->GetLeaf(0)->GenerateLeaves();
	*/
}

void childFinderTomToldMeToDoIt(std::vector<GameObject*>& results, OctNode* current)
{
	results.insert(results.end(), current->GetObjects().begin(), current->GetObjects().end());
	if (!current->isLeaf())
	{
		for (int i = 0; i < 8; ++i)
		{
			childFinderTomToldMeToDoIt(results, current->GetLeaf(i));
		}
	}
}

std::vector<GameObject*> Octree::nearbyObjects(GameObject* object)
{
	if (!enabled)
		return GameObject::GetInstances();

	std::vector<GameObject*> toReturn = std::vector<GameObject*>();
	OctNode* start = object->GetOctNode();
	do
	{
		toReturn.insert(toReturn.end(), start->GetObjects().begin(), start->GetObjects().end());
		start = start->GetParent();
	} while (start);

	start = object->GetOctNode();
	if (!start->isLeaf())
	{
		for (int i = 0; i < 8; ++i)
		{
			childFinderTomToldMeToDoIt(toReturn, start->GetLeaf(i));
		}
	}

	return toReturn;
}

