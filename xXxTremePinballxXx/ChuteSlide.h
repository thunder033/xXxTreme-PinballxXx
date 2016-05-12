#pragma once
#include "GameObject.h"
class ChuteSlide :
	public GameObject
{
	PrimitiveClass* mesh;
	bool active;
public:
	ChuteSlide();
	~ChuteSlide();
	void ToggleOff();
	void ToggleOn();
};

