#include "Wall.h"


void Wall::NodeCollisionFout(double const & omega)
{

	for (unsigned i = 0; i < fOut.size() ; ++i)
	{
		fOut[i] = fIn[oppositeF[i]];

		//fOut[i] = (1. - omega)* fIn[i] + omega* feq[i];
		//fOut[i] = fOut[oppositeF[i]] ;
	}

}

void Wall::NodeCollisionTout(double const& omegaT)
{
	for (unsigned i = 0; i < TOut.size(); ++i)
	{
		TOut[i] = TIn[oppositeT[i]];

		//TOut[i] = (1. - omegaT)* TIn[i] + omegaT* Teq[i];
		//TOut[i] = TOut[oppositeT[i]];
	}
}
