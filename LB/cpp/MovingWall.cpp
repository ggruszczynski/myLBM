
#include "../headers/MovingWall.h"


void MovingWall::ComputeRho()
{
	this->rho = 1. / (1 + uWall[1]);
	this->rho *= (fIn[0] + fIn[1] + fIn[3]) + 2 * (fIn[2] + fIn[5] + fIn[6]);
}

void MovingWall::ComputeU()
{
	u = uWall;
}


void MovingWall::NodeCollisionFout(double const & omega)
{

	switch (this->cardinal_directions)
	{
	case North: //Lid
		fIn[4] = fIn[2] - (2. / 3.) * rho*u[1];
		fIn[7] = fIn[5] + 0.5*(fIn[1] - fIn[3]) - 0.5 * rho*u[0] - (1. / 6.) * rho*u[1];
		fIn[8] = fIn[6] + 0.5*(fIn[3] - fIn[1]) + 0.5 * rho*u[0] - (1. / 6.) * rho*u[1];



		//----------old stuff
		//this->rho = 1. / (1 + u[1]);
		//this->rho *= (fIn[0] + fIn[1] + fIn[3]) + 2 * (fIn[2] + fIn[5] + fIn[6]);

		//fIn[4] = fIn[2] - (2 / 3) * rho*u[1];
		//fIn[8] = fIn[6] + 0.5*(fIn[3] - fIn[1]) + 0.5 * rho*u[0] - (1. / 6.) * rho*u[1];
		//fIn[7] = fIn[5] + 0.5*(fIn[1] - fIn[3]) - 0.5 * rho*u[0] - (1. / 6.) * rho*u[1];

		break;
	case East:
		throw std::exception("not implemented");
		this->rho = 1 / (1 + uWall[0]);
		this->rho *= (fIn[0] + fIn[2] + fIn[4]) + 2 * (fIn[3] + fIn[6] + fIn[7]);

		fIn[1] = fIn[3] + 2 / 3 * rho*uWall[1];
		fIn[5] = fIn[7] - 0.5*(fIn[2] - fIn[4]) + 0.5 * rho*uWall[1] + 1 / 6 * rho*uWall[0];
		fIn[8] = fIn[6] + 0.5*(fIn[2] - fIn[4]) - 0.5 * rho*uWall[1] + 1 / 6 * rho*uWall[0];

		break;
	default:
		throw std::exception("not implemented");
		break;
	}

	for (unsigned i = 0; i < fOut.size(); ++i)
	{	
		fOut[i] = (1. - omega)* fIn[i] + omega* feq[i];
	}
}

void MovingWall::SetUWall(double setU, double setV)
{
	uWall << setU, setV;
}


void MovingWall::NodeCollisionTout(double const& omegaT)
{

	//T = std::accumulate(TIn.begin(), TIn.end(), 0.0);

	//double eu;
	//Eigen::Matrix<double, 2, 1, Eigen::DontAlign> utemp;
	////utemp << 0, 0;
	//utemp = uWall;
	//for (unsigned i = 0; i < Teq.size(); ++i)
	//{
	//	eu = utemp.dot(d2q5Constants->e[i]);
	//	Teq[i] = 1 + 3 * eu;
	//	Teq[i] *= T * d2q5Constants->w[i];
	//}

	//for (unsigned i = 0; i < TOut.size(); ++i)
	//{
	//	TOut[i] = (1. - omegaT)* TIn[i] + omegaT* Teq[i];
	//}

	//for (unsigned i = 0; i < TOut.size(); ++i)
	//{
	//	TOut[i] = TOut[oppositeT[i]] ;
	//}

	for (unsigned i = 0; i < TOut.size(); ++i)
	{
		TOut[i] = TIn[oppositeT[i]] ;
	}

}


MovingWall::~MovingWall()
{
}
