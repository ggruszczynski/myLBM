
#include "VelocityInlet.h"


void VelocityInlet::ComputeRho()
{
	this->rho = 1. / (1 - uInlet[0]);
	this->rho *= (fIn[0] + fIn[2] + fIn[4]) + 2 * (fIn[3] + fIn[6] + fIn[7]);
}

void VelocityInlet::ComputeU()
{
	u = uInlet;
}

void VelocityInlet::NodeCollisionFout(double const& omega)
{
	switch (this->cardinal_directions)
	{
	case West:

		fIn[1] = fIn[3] + (2. / 3.) * rho*u[0];
		fIn[5] = fIn[7] + 0.5*(fIn[4] - fIn[2]) +  (1. / 6.) * rho*u[0];
		fIn[8] = fIn[6] + 0.5*(fIn[2] - fIn[4])  + (1. / 6.) * rho*u[0];

		/// since u[1] = 0...
		//fIn[1] = fIn[3] + (2 / 3) * rho*u[0];
		//fIn[5] = fIn[7] + 0.5*(fIn[4] - fIn[2]) + 0.5 * rho*u[1] + (1 / 6) * rho*u[0];
		//fIn[8] = fIn[6] + 0.5*(fIn[2] - fIn[4]) - 0.5 * rho*u[1] + (1 / 6) * rho*u[0];

		break;
	default:
		throw std::runtime_error("not implemented");
		break;
	}

	for (unsigned i = 0; i < sizeof(fOut)/ sizeof(double); ++i)
	{
		fOut[i] = (1. - omega)* fIn[i] + omega* feq[i];
	}
}

void VelocityInlet::SetU(const double& setU, const double& setV)
{
	u << setU, setV;
	uInlet << setU, setV;

//	u2D.x=setU;  u2D.y=setV;
//	uInlet2D.x=setU;  uInlet2D.y=setV;
}

VelocityInlet::~VelocityInlet()
{
}
