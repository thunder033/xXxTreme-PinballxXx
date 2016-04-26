#include "Ball.h"



Ball::Ball() : GameObject((mesh = new PrimitiveClass(), mesh->GenerateSphere(1, 12, REWHITE), mesh))
{
	collider->setType(ColliderType::Circle);
}


Ball::~Ball()
{
}
