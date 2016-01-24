#include "../headers/Wall.h"


void Wall::NodeCollisionFout(double const & omega)
{

	for (unsigned i = 0; i < fOut.size() ; ++i)
	{
		//fOut[i] = (1. - omega)* fIn[i] + omega* feq[i];
		//fOut[i] = fOut[oppositeF[i]] ;

		fOut[i] = fIn[oppositeF[i]];
	}

}

void Wall::NodeCollisionTout(double const& omega)
{
	for (unsigned i = 0; i < TOut.size(); ++i)
	{
		TOut[i] = TIn[oppositeT[i]];
	}
}
