
#include "MovingWall.h"


void MovingWall::ComputeRho()
{
	this->rho = 1. / (1 + uWall[1]);
//	this->rho = 1. / (1 + uWall2D.y);
	this->rho *= (fIn[0] + fIn[1] + fIn[3]) + 2 * (fIn[2] + fIn[5] + fIn[6]);
}

void MovingWall::ComputeU()
{
	u = uWall;
//	u2D.x = uWall2D.x;
//	u2D.y = uWall2D.y;
}


void MovingWall::NodeCollisionFout(double const & omega)
{

	switch (this->cardinal_directions)
	{
	case North: //Lid
		fIn[4] = fIn[2] - (2. / 3.) * rho*u[1];
		fIn[7] = fIn[5] + 0.5*(fIn[1] - fIn[3]) - 0.5 * rho*u[0] - (1. / 6.) * rho*u[1];
		fIn[8] = fIn[6] + 0.5*(fIn[3] - fIn[1]) + 0.5 * rho*u[0] - (1. / 6.) * rho*u[1];

//		fIn[4] = fIn[2] - (2. / 3.) * rho*uWall2D.y;
//		fIn[7] = fIn[5] + 0.5*(fIn[1] - fIn[3]) - 0.5 * rho*u[0] - (1. / 6.) * rho*uWall2D.y;
//		fIn[8] = fIn[6] + 0.5*(fIn[3] - fIn[1]) + 0.5 * rho*u[0] - (1. / 6.) * rho*uWall2D.y;

		//----------old stuff
		//this->rho = 1. / (1 + u[1]);
		//this->rho *= (fIn[0] + fIn[1] + fIn[3]) + 2 * (fIn[2] + fIn[5] + fIn[6]);

		//fIn[4] = fIn[2] - (2 / 3) * rho*u[1];
		//fIn[8] = fIn[6] + 0.5*(fIn[3] - fIn[1]) + 0.5 * rho*u[0] - (1. / 6.) * rho*u[1];
		//fIn[7] = fIn[5] + 0.5*(fIn[1] - fIn[3]) - 0.5 * rho*u[0] - (1. / 6.) * rho*u[1];

		break;
	case East:

		throw std::runtime_error("not implemented");
//		this->rho = 1 / (1 + uWall[0]);
//		this->rho *= (fIn[0] + fIn[2] + fIn[4]) + 2 * (fIn[3] + fIn[6] + fIn[7]);
//
//		fIn[1] = fIn[3] + 2 / 3 * rho*uWall[1];
//		fIn[5] = fIn[7] - 0.5*(fIn[2] - fIn[4]) + 0.5 * rho*uWall[1] + 1 / 6 * rho*uWall[0];
//		fIn[8] = fIn[6] + 0.5*(fIn[2] - fIn[4]) - 0.5 * rho*uWall[1] + 1 / 6 * rho*uWall[0];


	default:
		throw std::runtime_error("not implemented");

	}

	for (unsigned i = 0; i < sizeof(fOut)/ sizeof(double); ++i)
	{	
		//fOut[i] = fIn[i];
		fOut[i] = (1. - omega)* fIn[i] + omega* feq[i]; 
	}
}

void MovingWall::SetUWall(double setU, double setV)
{
	uWall << setU, setV;

//	uWall2D.x = setU;
//	uWall2D.y = setV;
}


void MovingWall::NodeCollisionTout(double const& omegaT)
{
	TIn[4] = TIn[2];
	for (unsigned i = 0; i < sizeof(TOut)/ sizeof(double); ++i)
	{
		TOut[i] = (1. - omegaT)* TIn[i] + omegaT* Teq[i];
	}
}
