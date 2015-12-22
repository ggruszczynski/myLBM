#include "PressureOutlet.h"


void PressureOutlet::ComputeRho()
{
	this -> rho = 1;
}

void PressureOutlet::ComputeU()
{
	this->u[0] = -1 + 1 /rho;
	this->u[0] *= (fIn[0] + fIn[2] + fIn[4]) + 2 * (fIn[1] + fIn[5] + fIn[8]);

	this->u[1] = 0;
}

void PressureOutlet::NodeCollision(double const& omega)
{
	switch (this->cardinal_directions)
	{
	case West:
		fIn[3] = fIn[2] - (2 / 3) * rho*u[0];
		fIn[7] = fIn[7] + 0.5*(fIn[2] - fIn[4]) - 0.5 * rho*u[1] - (1 / 6) * rho*u[0];
		fIn[6] = fIn[8] + 0.5*(fIn[4] - fIn[2]) + 0.5 * rho*u[1] - (1 / 6) * rho*u[0];

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


PressureOutlet::~PressureOutlet()
{
}
