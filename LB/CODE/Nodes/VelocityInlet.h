#pragma once


#include "../Nodes/Node.h"
#include "../Constants/Enums.h"

class VelocityInlet :
	public Node
{
private:
	CardinalDirections cardinal_directions;
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> uInlet;
//	u2D_Struct  uInlet2D;
public:
	void ComputeRho() override;
	void ComputeU() override;
	void NodeCollisionFout(double const & omega) override;
	void SetU(const double &setU, const double &setV) override;
	shared_ptr<Node> CloneShrPtr() override { return make_shared<VelocityInlet>(*this); }

	//void SetU(const double &setU, const double &setV) override;

	VelocityInlet(double setU, double setV) : cardinal_directions(West)
	{
		nodeType = NodeType::VelocityInletType;
		uInlet << setU, setV;
	};
	~VelocityInlet();
};

