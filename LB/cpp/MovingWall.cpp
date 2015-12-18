
#include "../headers/MovingWall.h"


 void MovingWall::Collision()
{

	switch (this -> cardinal_directions)
	{
	case North: //Lid
		this->rho = 1 / (1 + u[1]);
		this->rho *= (fIn[0] + fIn[1] + fIn[3]) + 2 * (fIn[2] + fIn[5] + fIn[6]);

		fIn[4] = fIn[3] - 2 / 3 * rho*u[1];
		fIn[8] = fIn[6] + 0.5*(fIn[3] - fIn[1]) + 0.5 * rho*u[0] - 1 / 6 * rho*u[1];
		fIn[7] = fIn[6] + 0.5*(fIn[1] - fIn[3]) - 0.5 * rho*u[0] - 1 / 6 * rho*u[1];

		break;
	case East:
		throw std::exception("not implemented");
		break;
	default:
		throw std::exception("not implemented");
		break;
	}

}

 MovingWall::~MovingWall()
{
}
