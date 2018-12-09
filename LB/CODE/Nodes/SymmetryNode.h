#pragma once
#include "Node.h"
class SymmetryNode :
	public Node
{
private:
	int oppositeF[9] = { 0, 3, 4, 1, 2, 8, 7, 6, 5 };
	int oppositeT[5] = { 0, 3, 4, 1, 2 };
public:
	void NodeCollisionFout(double const & omega) override; //bounce back
	void NodeCollisionTout(double const & omega) override; //bounce back
	shared_ptr<Node> CloneShrPtr() override { return make_shared<SymmetryNode>(*this); }

	SymmetryNode() { nodeType = NodeType::SymmetryType; };
	~SymmetryNode() { }; // TODO: why not delete[] oppositeF ?;
};

inline void SymmetryNode::NodeCollisionFout(double const& omega)
{
	for (unsigned i = 0; i <  sizeof(fOut)/sizeof(double); ++i)
		fOut[i] = fIn[oppositeF[i]];
}

inline void SymmetryNode::NodeCollisionTout(double const& omega)
{
	for (unsigned i = 0; i < sizeof(TOut)/sizeof(double); ++i)
		TOut[i] = TIn[oppositeT[i]];
}
