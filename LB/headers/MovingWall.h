#pragma once
#include "Node.h"
class MovingWall :
	public Node
{
public:
	void Collision() override; // moving wall
	

	MovingWall();
	~MovingWall();
};

