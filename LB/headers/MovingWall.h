#pragma once
#include "Node.h"

enum CardinalDirections
{
	North,	
	East,
	South,
	West,
};

class MovingWall :	public Node
{
private:
	CardinalDirections cardinal_directions;
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> uWall;

public:
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	void Collision() override; // moving wall
	

	MovingWall() : cardinal_directions(North)
	{
		uWall << 0.05, 0;
	};
	~MovingWall();
};

