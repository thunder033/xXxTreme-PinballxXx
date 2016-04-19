#ifndef _PINBALL_TABLE_H_
#define _PINBALL_TABLE_H_

#include "RE/ReEngAppClass.h"
#include <glm/glm.hpp>

class PinballTable
{
public:
	PinballTable();

	void Render(matrix4 Proj, matrix4 View);

private:
	PrimitiveClass WhiteCube;
	PrimitiveClass GrayCube;
};

#endif