#include "Wall.h"


void Wall::NodeCollisionFout(double const & omega)
{

	for (unsigned i = 0; i <  sizeof(fOut)/ sizeof(double) ; ++i)
	{
		fOut[i] = fIn[oppositeF[i]];

		//fOut[i] = (1. - omega)* fIn[i] + omega* feq[i];
		//fOut[i] = fOut[oppositeF[i]] ;
	}

}

void Wall::NodeCollisionTout(double const& omegaT)
{
	for (unsigned i = 0; i <  sizeof(TOut)/ sizeof(double); ++i)
	{
		TOut[i] = TIn[oppositeT[i]];

		//TOut[i] = (1. - omegaT)* TIn[i] + omegaT* Teq[i];
		//TOut[i] = TOut[oppositeT[i]];
	}
}
