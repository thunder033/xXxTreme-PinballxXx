#ifndef _PINBALL_TABLE_H_
#define _PINBALL_TABLE_H_

#include "RE/ReEngAppClass.h"
#include <glm/glm.hpp>
#include <vector>
#include "Wall.h"

class PinballTable
{
public:
	PinballTable();

	void Render(matrix4 Proj, matrix4 View);

private:
	PrimitiveClass WhiteCube;
	PrimitiveClass GrayCube;

	std::vector<Wall*> Walls;
};

#endif