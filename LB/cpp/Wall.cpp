#include "../headers/Wall.h"


void Wall::NodeCollisionFout(double const & omega)
{

	for (unsigned i = 0; i < fOut.size() ; ++i)
	{
		fOut[i] = fIn[oppositeF[i]];
	}

}

void Wall::NodeCollisionTout(double const& omega)
{
	for (unsigned i = 0; i < TOut.size(); ++i)
	{
		TOut[i] = TIn[oppositeF[i]];
	}
}
