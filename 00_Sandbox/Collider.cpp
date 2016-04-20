#include "Collider.h"

//  Collider
void Collider::Init(void)
{
	radius = 0.0f;
	worldTransform = IDENTITY_M4;

	origin = vector3(0.0f);
	min = vector3(0.0f);
	max = vector3(0.0f);


}
void Collider::Swap(Collider& other)
{
	std::swap(radius, other.radius);
	std::swap(worldTransform, other.worldTransform);

	std::swap(origin, other.origin);
	std::swap(min, other.min);
	std::swap(max, other.max);
}
void Collider::Release(void)
{

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
Collider::Collider(std::vector<vector3> a_lVectorList)
{
	GetMinMax(min, max, a_lVectorList);
	origin = (min + max) / 2.0f;

	radius = glm::distance(origin, max);

	size.x = max.x - min.x;
	size.y = max.y - min.y;
	size.z = max.z - min.z;
	alignedSize = size;
}
Collider::Collider(Collider const& other)
{
	radius = other.radius;
	worldTransform = other.worldTransform;

	origin = other.origin;
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
void Collider::SetModelMatrix(matrix4 a_m4ToWorld) { worldTransform = a_m4ToWorld; }
vector3 Collider::GetCenter(void) { return vector3(worldTransform * vector4(origin, 1.0f)); }
float Collider::GetRadius(void) { return radius; }
std::vector<vector3> Collider::RotateTo(quaternion rot)
{
	rotation = rot;

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
		box[i] = vector3(ToMatrix4(rotation) * glm::translate(origin) * glm::scale(size) * vector4(box[i], 1));
	}

	GetMinMax(min, max, box);
	alignedSize.x = max.x - min.x;
	alignedSize.y = max.y - min.y;
	alignedSize.z = max.z - min.z;

	return box;
}

void Collider::SetPosition(vector3 position)
{
	worldTransform[3] = vector4(position, 1.0f);
}

void Collider::SetScale(vector3 scale)
{
	//Add scale
}

matrix4 Collider::GetAxisAlignedTransform()
{
	return glm::translate(GetCenter()) * glm::scale(alignedSize);
}

vector3 Collider::GetSize(void) { return size; }
matrix4 Collider::GetRotation(void)
{
	return ToMatrix4(rotation);
}


vector3 Collider::GetMin() {
	return vector3(worldTransform[3] + vector4(min, 1.0f));
}

vector3 Collider::GetMax() {
	return vector3(worldTransform[3] + vector4(max, 1.0f));
}

//--- Non Standard Singleton Methods
bool Collider::IsColliding(Collider* const a_pOther)
{
	float dist = glm::distance(GetCenter(), a_pOther->GetCenter());
	if (dist > (GetRadius() + a_pOther->GetRadius()))
		return false;

	vector3 v3Min = GetMin();
	vector3 v3MinO = a_pOther->GetMin();

	vector3 v3Max = GetMax();
	vector3 v3MaxO = a_pOther->GetMax();

	return !(v3Min.x > v3MaxO.x || v3MinO.x > v3Max.x ||
		v3Min.y > v3MaxO.y || v3MinO.y > v3Max.y ||
		v3Min.z > v3MaxO.z || v3MinO.z > v3Max.z);
}