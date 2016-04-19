#pragma once
class Collider
{
public:
	Collider();
	virtual ~Collider();

	virtual bool isColliding(Collider* Other) = 0;
};

