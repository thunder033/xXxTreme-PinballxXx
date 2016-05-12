#include "ChuteSlide.h"



ChuteSlide::ChuteSlide() : GameObject((mesh = new PrimitiveClass(), mesh->GenerateCube(1, RERED), mesh))
{
	Scale(vector3(1.25f, .5f, .25f));
	Rotate(quaternion(vector3(0, 0, 35.f)));
	Translate(vector3(3.25f, 3.f, 1.f));
	active = true;
}


ChuteSlide::~ChuteSlide()
{
}

void ChuteSlide::ToggleOff()
{
	if (active) {
		transform->SetPosition(vector3(3.25f, 3.f, -0.25f));
		collider->calculateAABB();
		active = false;
	}
	
}

void ChuteSlide::ToggleOn()
{
	if (!active) {
		transform->SetPosition(vector3(3.25f, 3.f, 1.f));
		collider->calculateAABB();
		active = true;
	}
		
}
