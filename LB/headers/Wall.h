#pragma once
#include "Node.h"
class Wall :
	public Node
{
private:
	int opposite[9] = { 0, 3, 4, 1, 2, 7, 8, 5, 6 };

public:
	void NodeCollision(double const & omega) override; //bounce back

	Wall(){ nodeType = NodeType::WallType; };
	~Wall() { }; // TODO why not delete[] opposite ?;
};

