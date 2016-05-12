#include "Wall.h"

Wall::Wall(vector3 scale) : GameObject((mesh = new PrimitiveClass(), mesh->GenerateCube(1.f, REGRAY), mesh))
{
	collider->setType(ColliderType::OBB);
	Scale(scale);
}

void Wall::OnCollision(const CollisionEvent& collision)
{
}

ObjectType Wall::GetType()
{
	return ObjectType::Wall;
}
