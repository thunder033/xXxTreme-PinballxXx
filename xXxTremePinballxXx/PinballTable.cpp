#include "PinballTable.h"

PinballTable::PinballTable()
{
	WhiteCube.GenerateCube(1.f, REWHITE);

	GrayCube.GenerateCube(1.f, REGRAY);

	Wall* WallInst = nullptr;
	
	//////////////////////////////////////////////////////////////////////////
	// Walls

	// Bottom Wall
	auto Position = vector3(0.f, -5.875f, 0.75f);
	auto Scale = vector3(8.f, 0.25f, 0.5f);
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	Walls.push_back(WallInst);

	// Top Wall
	Position.y *= -1;
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	Walls.push_back(WallInst);

	// Left Wall
	Position = vector3(-3.875, 0.f, 0.75f);
	Scale = vector3(0.25f, 11.5f, 0.5f);
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	Walls.push_back(WallInst);

	// Right Wall
	Position.x *= -1;
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	Walls.push_back(WallInst);

	//////////////////////////////////////////////////////////////////////////
	// Internal Walls

	// Right wall near plunger
	Position = vector3(2.8f, -1.f, 0.75f);
	Scale = vector3(0.25f, 8.0f, 0.5f);
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	Walls.push_back(WallInst);

	// Top right angled wall
	Position = vector3(3.f, 5.1f, 0.75f);
	Scale = vector3(0.25f, 2.75f, 0.5f);
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	WallInst->RotateTo(glm::radians(vector3(0.f, 0.f, 60.f)));
	Walls.push_back(WallInst);

	// Top left angled wall
	Position.x *= -1;
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	WallInst->RotateTo(glm::radians(vector3(0.f, 0.f, -45.f)));
	Walls.push_back(WallInst);

	// Bottom angled wall
	Position = vector3(-0.35f, -5.5f, 0.75f);
	Scale = vector3(7.f, 0.25f, 0.5f);
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	WallInst->RotateTo(glm::radians(vector3(0.f, 0.f, -5.f)));
	Walls.push_back(WallInst);

	//////////////////////////////////////////////////////////////////////////
	// Flipper Area

	// Right Side
	Position = vector3(1.75f, -4.f, 0.75f);
	Scale = vector3(0.25f, 2.25f, 0.5f);
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	WallInst->RotateTo(glm::radians(vector3(0.f, 0.f, -60.f)));
	Walls.push_back(WallInst);

	// Left Side
	Position.x = -3.f;
	WallInst = new Wall(Scale);
	WallInst->Translate(Position);
	WallInst->RotateTo(glm::radians(vector3(0.f, 0.f, 60.f)));
	Walls.push_back(WallInst);
}

void PinballTable::Render(matrix4 Proj, matrix4 View)
{
	// Table
	WhiteCube.Render(Proj, View, glm::translate(0.f, 0.f, 0.f) * glm::scale(8.f, 12.f, 1.f));
}
