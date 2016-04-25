#include "Collider.h"

//  Collider
void Collider::Init(void)
{
	radius = 0.0f;
	centroid = vector3(0.0f);
	min = vector3(0.0f);
	max = vector3(0.0f);
}
void Collider::Swap(Collider& other)
{
	std::swap(radius, other.radius);
	std::swap(transform, other.transform);

	std::swap(centroid, other.centroid);
	std::swap(min, other.min);
	std::swap(max, other.max);
}
void Collider::Release(void)
{
	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}
}

void Collider::GetMinMax(vector3& min, vector3& max, std::vector<vector3> points) {
	if (points.size() == 0)
		return;

	min = points[0];
	max = points[0];

	std::vector<vector3>::iterator it;
	for (it = points.begin(); it != points.end(); ++it)
	{
		if (it->x < min.x)
			min.x = it->x;
		else if (it->x > max.x)
			max.x = it->x;

		if (it->y < min.y)
			min.y = it->y;
		else if (it->y > max.y)
			max.y = it->y;

		if (it->z < min.z)
			min.z = it->z;
		else if (it->z > max.z)
			max.z = it->z;
	}
}

//The big 3
Collider::Collider(std::vector<vector3> a_lVectorList, GOTransform* transform)
{
	this->transform = transform;
	GetMinMax(min, max, a_lVectorList);
	centroid = (min + max) / 2.0f;

	radius = glm::distance(centroid, max);

	size.x = max.x - min.x;
	size.y = max.y - min.y;
	size.z = max.z - min.z;
	alignedSize = size;
}
Collider::Collider(Collider const& other)
{
	radius = other.radius;
	transform = other.transform;

	centroid = other.centroid;
	min = other.min;
	max = other.max;
}
Collider& Collider::operator=(Collider const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Collider temp(other);
		Swap(temp);
	}
	return *this;
}
Collider::~Collider() { Release(); };
//Accessors
vector3 Collider::GetCenter(void) { return vector3(transform->GetMatrix() * vector4(centroid, 1.0f)); }
float Collider::GetRadius(void) { return radius; }

std::vector<vector3> Collider::GetBoundingBox()
{
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> box{
		vector3(-fValue, -fValue, fValue), //0
		vector3(fValue, -fValue, fValue), //1
		vector3(fValue, fValue, fValue), //2
		vector3(-fValue, fValue, fValue), //3

		vector3(-fValue, -fValue, -fValue), //4
		vector3(fValue, -fValue, -fValue), //5
		vector3(fValue, fValue, -fValue), //6
		vector3(-fValue, fValue, -fValue) //7
	};

	for (int i = 0; i < 8; i++) {
		box[i] = vector3(ToMatrix4(transform->GetRotation()) * glm::translate(centroid) * glm::scale(size) * glm::scale(transform->GetScale()) * vector4(box[i], 1));
	}

	return box;
}

void Collider::setType(ColliderType type)
{
	this->type = type;
	if (type == Circle) {
		radius = 1;
	}
}

void Collider::calculateAABB()
{
	std::vector<vector3> box = GetBoundingBox();
	GetMinMax(min, max, box);
	alignedSize.x = max.x - min.x;
	alignedSize.y = max.y - min.y;
	alignedSize.z = max.z - min.z;
}

matrix4 Collider::GetAxisAlignedTransform()
{
	return glm::translate(GetCenter()) * glm::scale(alignedSize);
}

vector3 Collider::GetSize(void) { return size; }

vector3 Collider::GetMin() {
	return vector3(transform->GetMatrix()[3] + vector4(min, 1.0f));
}

vector3 Collider::GetMax() {
	return vector3(transform->GetMatrix()[3] + vector4(max, 1.0f));
}

//--- Non Standard Singleton Methods
bool Collider::IsColliding(Collider* const a_pOther)
{
	float dist = glm::distance(GetCenter(), a_pOther->GetCenter());
	if (dist > (GetRadius() + a_pOther->GetRadius()))
		return false;

	if (type != a_pOther->type) {
		Collider* box = type == AABB ? this : a_pOther;
		Collider* circle = type == Circle ? this : a_pOther;

		std::vector<vector3> boxPts = box->GetBoundingBox();
		std::sort(boxPts.begin(), boxPts.end(), [circle, box](vector3 a, vector3 b) -> bool {
			return glm::distance(box->GetCenter() + a, circle->GetCenter()) < glm::distance(box->GetCenter() + b, circle->GetCenter());
		});
		//std::vector<vector3> displacements = {};
		for (int i = 0; i < 8; i++) {
			//displacements.push_back(boxPts[i] - circle->GetCenter());
			vector3 point = box->GetCenter() + boxPts[i];
			if (glm::distance(point, circle->GetCenter()) < circle->GetRadius())
				return true;
		}

		vector3 disp = circle->GetCenter() - (box->GetCenter() + boxPts[0]);
		vector3 disp2 = circle->GetCenter() - (box->GetCenter() + boxPts[7]);
		for (int i = 1; i < 8; i++) {
			//if (boxPts[i].x != boxPts[0].x && boxPts[i].y != boxPts[0].y && boxPts[i].z != boxPts[0].z)
			//	continue;

			vector3 edge = boxPts[i] - boxPts[0];
			vector3 center = box->GetCenter();
			vector3 point = box->GetCenter() + boxPts[i];

			//project the displacement from the closest point to the sphere onto the edge
			float dotProduct = glm::dot(disp, edge);
			if (dotProduct < 0)
				continue;

			float edgeLength = glm::length(edge);
			vector3 intersection = point - (dotProduct / edgeLength) * (edge / edgeLength);
			float dist = glm::distance(intersection, circle->GetCenter());

			if (dist < circle->GetRadius())
				return true;
		}

		return false;
	}
	else if (type == Circle) {
		return false;
	}
	else {
		vector3 v3Min = GetMin();
		vector3 v3MinO = a_pOther->GetMin();

		vector3 v3Max = GetMax();
		vector3 v3MaxO = a_pOther->GetMax();

		return !(v3Min.x > v3MaxO.x || v3MinO.x > v3Max.x ||
			v3Min.y > v3MaxO.y || v3MinO.y > v3Max.y ||
			v3Min.z > v3MaxO.z || v3MinO.z > v3Max.z);
	}

	
}