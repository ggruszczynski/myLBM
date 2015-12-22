#include "../headers/Wall.h"


void Wall::NodeCollision(double const & omega)
{

	for (unsigned i = 0; i < fOut.size() ; ++i)
	{
		fOut[i] = fIn[opposite[i]];
	}
}

