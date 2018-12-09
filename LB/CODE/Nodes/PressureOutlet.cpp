
#include "PressureOutlet.h"


void PressureOutlet::ComputeRho()
{
	//this->rho = std::accumulate(fIn.begin(), fIn.end(), 0.0); 
	this -> rho = 1;
}

void PressureOutlet::ComputeU()
{
	// TODO: what would u = 0 at pressure outet mean? 
	//this->u[0] = 0;
	//this->u[0] = -1 + ((fIn[0] + fIn[1] + fIn[3]) + 2 * (fIn[1] + fIn[5] + fIn[8])) / rho; // vw pracy WR

	this->u[0] = -1 + ((fIn[0] + fIn[2] + fIn[4]) + 2 * (fIn[1] + fIn[5] + fIn[8]))/rho;  
	this->u[1] = 0;
}

void PressureOutlet::NodeCollisionFout(double const& omega)
{
	switch (this->cardinal_directions)
	{
	case East:
		fIn[3] = fIn[1] - (2. / 3.) * rho*u[0];
		fIn[7] = fIn[5] + 0.5*(fIn[2] - fIn[4]) - (1. / 6.) * rho*u[0];
		fIn[6] = fIn[8] + 0.5*(fIn[4] - fIn[2]) - (1. / 6.) * rho*u[0];

		/// since u[1] = 0 ...
		//fIn[3] = fIn[1] - (2. / 3.) * rho*u[0];
		//fIn[7] = fIn[5] + 0.5*(fIn[2] - fIn[4]) - 0.5 * rho*u[1] - (1. / 6.) * rho*u[0];
		//fIn[6] = fIn[8] + 0.5*(fIn[4] - fIn[2]) + 0.5 * rho*u[1] - (1. / 6.) * rho*u[0];
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


PressureOutlet::~PressureOutlet()
{
}
