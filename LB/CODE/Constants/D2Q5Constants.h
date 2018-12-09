/*
 * D2Q9Constants.h
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#pragma once
#include "Singleton.h"
#include <iostream>
#include <vector>


#include <eigen3/Eigen/StdVector>

using namespace Eigen;
using namespace std;

class D2Q5Constants : public Singleton<D2Q5Constants>// Singleton
{
private:

	friend class Singleton<D2Q5Constants>;
	D2Q5Constants() : Singleton<D2Q5Constants>() //ok
	{
		ee.reserve(5);
		ee.emplace_back(0, 0);

		ee.emplace_back(Eigen::Vector2d(1, 0));
		ee.emplace_back(Eigen::Vector2d(0, 1));
		ee.emplace_back(Eigen::Vector2d(-1, 0));
		ee.emplace_back(Eigen::Vector2d(0, -1));
	}

public:
	double w[5] = {2. / 6, 1. / 6, 1. / 6, 1. / 6, 1. / 6 } ;



	//vector<vector <double> > ee; // velocities directions
	//static vector<Vector2d, Eigen::aligned_allocator<Eigen::Vector2d> > ee; // velocities directions
	//static vector <double> vw;   // weigths
	//static const double cs2;			// lattice speed ^2 //  TODO: (where shall I store it?)
	//static double omegaNS;

	//static D2Q9Constants* GetInstance();
	//virtual ~D2Q9Constants(){ instanceFlag = false; };


	//D2Q9Constants(D2Q9Constants const&) = delete;
	//void operator=(D2Q9Constants const&) = delete;
	// Make sure they are unacceptable otherwise you may accidentally get copies of
	// your singleton appearing.
	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status
};


