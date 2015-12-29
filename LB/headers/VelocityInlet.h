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
	void NodeCollisionFout(double const & omega) override;
	void SetU(const double &setU, const double &setV) override;
	//void SetU(const double &setU, const double &setV) override;

	VelocityInlet(double setU, double setV) : cardinal_directions(East)
	{
		nodeType = NodeType::VelocityInletType;
		uInlet << setU, setV;
	};
	~VelocityInlet();
};

