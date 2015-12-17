#pragma once
#include "Node.h"
class Wall :
	public Node
{
public:
	void Collision() override; //bounce back

	Wall();
	~Wall();
};

