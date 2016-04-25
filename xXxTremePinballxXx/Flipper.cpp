#include "Flipper.h"



Flipper::Flipper() : GameObject((mesh = new PrimitiveClass(), mesh->GenerateCube(1, RERED), mesh))
{
	SetOrigin(vector3(-0.5f, 0, 0));
	Scale(vector3(2, .5f, .5f));

	flipRotation = vector3(0, 0, PI / 2.0f);
	flipStart = transform->GetRotation();
	flipPct = 0;
	flipSpeed = 5.0f;
	flipping = false;
}


Flipper::~Flipper()
{
}

void Flipper::Update(double deltaTime)
{
	if (flipping) {
		flipPct += flipSpeed * deltaTime;
		if (flipPct >= 1.0f)
			flipping = false;
	}
	else if(flipPct > 0) {
		flipPct -= flipSpeed * deltaTime;
		if (flipPct < 0)
			flipPct = 0;
	}

	quaternion orientation = glm::mix(flipStart, flipStart * quaternion(flipRotation), flipPct);
	RotateTo(orientation);

	GameObject::Update(deltaTime);
}

void Flipper::Flip() {
	if (!flipping && flipPct == 0) {
		flipping = true;
		flipPct = 0;
	}
}