#pragma once
#include "Node.h"
#include "Enums.h"

class MovingWall :	public Node
{
private:
	CardinalDirections cardinal_directions;
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> uWall;

	int oppositeT[5] = { 0, 3, 4, 1, 2 };
public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	void ComputeRho() override;
	void ComputeU() override;
	void NodeCollisionFout(double const & omega) override;
	void SetUWall(double setU, double setV);

	void NodeCollisionTout(double const& omegaT) override;
	shared_ptr<Node> CloneShrPtr() override { return make_shared<MovingWall>(*this); }

	MovingWall(double setU, double setV) : cardinal_directions(North)
	{
		nodeType = NodeType::MovingWallType ;
		uWall << setU, setV;
	};


	~MovingWall();
};

