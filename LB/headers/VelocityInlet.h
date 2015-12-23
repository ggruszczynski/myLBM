#pragma once


#include "Node.h"
#include "Enums.h"

class VelocityInlet :
	public Node
{
private:
	CardinalDirections cardinal_directions;
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> uInlet;

public:
	void ComputeRho() override;
	void ComputeU() override;
	void NodeCollision(double const & omega) override;


	VelocityInlet(double setU, double setV) : cardinal_directions(East)
	{
		nodeType = NodeType::VelocityInletType;
		uInlet << setU, setV;
	};
	~VelocityInlet();
};

