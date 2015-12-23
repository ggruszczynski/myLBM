
#include "../headers/VelocityInlet.h"


void VelocityInlet::ComputeRho()
{
	this->rho = 1 / (1 - uInlet[0]);
	this->rho *= (fIn[0] + fIn[2] + fIn[4]) + 2 * (fIn[3] + fIn[6] + fIn[7]);
}

void VelocityInlet::ComputeU()
{
	u = uInlet;
}

void VelocityInlet::NodeCollision(double const& omega)
{
	switch (this->cardinal_directions)
	{
	case East:
		fIn[1] = fIn[3] + (2 / 3) * rho*u[0];
		fIn[5] = fIn[7] + 0.5*(fIn[4] - fIn[2]) + 0.5 * rho*u[1] + (1 / 6) * rho*u[0];
		fIn[8] = fIn[6] + 0.5*(fIn[2] - fIn[4]) - 0.5 * rho*u[1] + (1 / 6) * rho*u[0];

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

VelocityInlet::~VelocityInlet()
{
}
