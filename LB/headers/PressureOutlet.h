#pragma once
#include "Node.h"
#include "Enums.h"

class PressureOutlet :
	public Node
{
private:
	CardinalDirections cardinal_directions;

public:
	void ComputeRho() override;
	void ComputeU() override;
	void NodeCollisionFout(double const & omega) override;
	shared_ptr<Node> CloneShrPtr() override { return make_shared<PressureOutlet>(*this); }

	PressureOutlet() : cardinal_directions(East)	{		nodeType = NodeType::PressureOutletType;	}; 

	~PressureOutlet();
};

