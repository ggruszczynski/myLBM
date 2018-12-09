#pragma once
#include "Node.h"
#include "../Constants/Enums.h"

class PeriodicNode :
	public Node
{
private:
public:
	//void NodeCollisionFout(double const & omega) override;
	shared_ptr<Node> CloneShrPtr() override { return make_shared<PeriodicNode>(*this); }

	PeriodicNode() { nodeType = NodeType::PeriodicType; };

	~PeriodicNode(){};
};

