#pragma once
#include "Node.h"
class Wall :
	public Node
{
private:
	int oppositeF[9] = { 0, 3, 4, 1, 2, 7, 8, 5, 6 };
	int oppositeT[5] = { 0, 3, 4, 1, 2 };
public:
	void NodeCollisionFout(double const & omega) override; //bounce back
	void NodeCollisionTout(double const & omega) override; //bounce back
	shared_ptr<Node> CloneShrPtr() override { return make_shared<Wall>(*this); }

	Wall(){ nodeType = NodeType::WallType; };
	~Wall() { }; // TODO: why not delete[] oppositeF ?;
};

