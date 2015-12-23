#pragma once
#include "Node.h"
#include "Enums.h"

class MovingWall :	public Node
{
private:
	CardinalDirections cardinal_directions;
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> uWall;

public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	void ComputeRho() override;
	void ComputeU() override;
	void NodeCollision(double const & omega) override;
	void SetUWall(double setU, double setV);


	MovingWall(double setU, double setV) : cardinal_directions(North)
	{
		nodeType = NodeType::MovingWallType ;
		uWall << setU, setV;
	};
	~MovingWall();
};

