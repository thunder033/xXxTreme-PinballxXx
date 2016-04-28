#include "Wall.h"

Wall::Wall() : GameObject((mesh = new PrimitiveClass(), mesh->GenerateCube(1.f, REGRAY), mesh))
{
	collider->setType(ColliderType::OBB);
}
