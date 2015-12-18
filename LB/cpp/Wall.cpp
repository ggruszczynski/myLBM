#include "../headers/Wall.h"


void Wall::Collision()
{
	cout << "Wall :: Collision()" << endl;

	unsigned N = fOut.size();
	for (unsigned i = 0; i < fOut.size(); ++i)
	{
		fOut[i] = fIn[N-i];
	}
}

Wall::Wall()
{
}


Wall::~Wall()
{
}
