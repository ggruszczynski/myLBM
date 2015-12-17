/*
 * Solver.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#include "../headers/Solver.h"

void Solver::NaiveCollision()
{

	for ( auto& inner : mesh) {
		for ( auto& node : inner) {
			node.ComputeRho();
			node.ComputeU();
			node.ComputefEq();
			//ComputeNodeProperties(node);
			node.Collision();
			//for (int i = 0; i < node.fOut.size(); ++i)
			//{
			//	node.fOut[i] = (1. - omega)* node.fIn[i] + omega* node.fIn[i];
			//}
			//for_each(item.fOut.begin(), item.fOut.end(), )

		}
	}

}

void Solver::StreamToNeighbour(const int& x, const int& y)
{
	unsigned nextX, nextY;
	for (unsigned i = 0; i < d2q9Constants->e.size(); ++i)
	{
		nextX = x + d2q9Constants->e[i](0); 
		nextY = y + d2q9Constants->e[i](1);

		if (nextX >= 0  && nextX < mesh.size() && nextY >= 0 && nextY < mesh[x].size() ) 
			mesh[nextX][nextY].fIn[i] = mesh[x][y].fOut[i];

		//cout << d2q9Constants->e[i](0) << endl;
	}
}

void Solver::Update()
{ 
	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) {
			StreamToNeighbour(x, y);
		}
	}
}


//Solver::Solver() {
//	// TODO Auto-generated constructor stub
//
//}

Solver::~Solver() {
	// TODO Auto-generated destructor stub
}

