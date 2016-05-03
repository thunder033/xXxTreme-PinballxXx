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

	CalculateOBB();
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
float Collider::GetRadius(void) { 
	vector3 scale = transform->GetScale();
	return radius * std::max(std::max(scale.x, scale.y), scale.z);
}

std::vector<vector3> Collider::CalculateOBB()
{
	
	if (type == ColliderType::Sphere)
		return std::vector<vector3>();

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

	obb.verts = box;

	obb.r = obb.verts[1] - obb.verts[0];
	obb.s = obb.verts[3] - obb.verts[0];
	obb.t = obb.verts[0] - obb.verts[4];

	return box;
}

OBB Collider::UpdateOBB()
{
	obb.c = transform->GetPosition() - transform->GetRotation() * transform->GetOrigin();
	obb.u = glm::mat3_cast(transform->GetRotation());
	obb.e = size * transform->GetScale() / 2.f;

	return obb;
}

void Collider::setType(ColliderType type)
{
	this->type = type;
	if (type == ColliderType::Sphere) {
		radius = std::max(std::max(size.x, size.y), size.z) / 2.0f;
	}
}

void Collider::calculateAABB()
{	
	if (type == ColliderType::Sphere) {
		alignedSize = vector3(1) * transform->GetScale();
	}
	else {
		CalculateOBB();

		GetMinMax(min, max, obb.verts);
		alignedSize.x = max.x - min.x;
		alignedSize.y = max.y - min.y;
		alignedSize.z = max.z - min.z;
	}
}

vector3 Collider::GetLastCollision()
{
	return lastCollision;
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
		Collider* box = type == ColliderType::OBB ? this : a_pOther;
		Collider* sphere = type == ColliderType::Sphere ? this : a_pOther;

		vector3 axes[] = {
			box->obb.r,
			box->obb.s,
			box->obb.t
		};

		vector3 closestPt = box->obb.c;
		vector3 disp = sphere->GetCenter() - box->obb.c;

		for (int i = 0; i < 3; i++) {
			float dist = glm::dot(disp, glm::normalize(axes[i]));

			float extent = glm::length(axes[i]) / 2.0f;
			if (dist > extent)
				dist = extent;

			if (dist < -extent)
				dist = -extent;

			closestPt += dist * glm::normalize(axes[i]);	
		}

		vector3 normal = closestPt - sphere->GetCenter();
		return glm::dot(normal, normal) <= sphere->GetRadius() * sphere->GetRadius();
	}
	//If they are both circles, we have already checked their radii
	else if (type == ColliderType::Sphere) {
		return true;
	}
	else {

		vector3 r1 = obb.r;
		vector3 s1 = obb.s;
		vector3 t1 = obb.t;

		OBB obb2 = a_pOther->obb;
		vector3 r2 = obb2.r;
		vector3 s2 = obb2.s;
		vector3 t2 = obb2.t;

		vector3 axes[] = {
			//Normals of OBB1
			glm::cross(r1, s1),
			glm::cross(r1, t1),
			glm::cross(s1, t1),
			//Normals of OBB2
			glm::cross(r2, s2),
			glm::cross(r2, t2),
			glm::cross(s2, t2),
			//Normals between OBB1 & 2
			glm::cross(r1, r2),
			glm::cross(r1, s2),
			glm::cross(r1, t2),
			glm::cross(s1, r2),
			glm::cross(s1, s2),
			glm::cross(s1, t2),
			glm::cross(t1, r2),
			glm::cross(t1, s2),
			glm::cross(t1, t2),
		};

		for (int i = 0; i < 15; i++) {
			if (glm::length(axes[i]) == 0)
				continue;

			Projection proj1 = Projection(obb.GetWorldVerts(), axes[i]); 
			Projection proj2 = Projection(a_pOther->obb.GetWorldVerts(), axes[i]);

			lastCollision = (obb.c + a_pOther->obb.c) / 2.0f;
			if (!proj1.Overlaps(proj2)) {
				return false;
			}
		}

		return true;
	}

	
}