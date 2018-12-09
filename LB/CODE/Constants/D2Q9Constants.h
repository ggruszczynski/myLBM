
#pragma once

#include <iostream>
#include <vector>

#include <eigen3/Eigen/StdVector>
#include "Singleton.h"

using namespace Eigen;
using namespace std;

class D2Q9Constants : public Singleton<D2Q9Constants>
{
private:
	friend class Singleton<D2Q9Constants>;

	D2Q9Constants() : Singleton<D2Q9Constants>()
	{ 

		ee.reserve(9);

		ee.emplace_back(Eigen::Vector2d(0, 0));

		ee.emplace_back(Eigen::Vector2d(1, 0));
		ee.emplace_back(Eigen::Vector2d(0, 1));
		ee.emplace_back(Eigen::Vector2d(-1, 0));
		ee.emplace_back(Eigen::Vector2d(0, -1));

		ee.emplace_back(Eigen::Vector2d(1, 1));
		ee.emplace_back(Eigen::Vector2d(-1, 1));
		ee.emplace_back(Eigen::Vector2d(-1, -1));
		ee.emplace_back(Eigen::Vector2d(1, -1));
	}

public:
	vector<Vector2d, Eigen::aligned_allocator<Eigen::Vector2d> > ee;
	const double CSmag2 = 0.0009; // = CSmag * CSmag;

	const double w[9] = {4. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 36, 1. / 36, 1. / 36, 1. / 36 } ;

    const lattice_vectors e[9] = {{0,0},
                            {1,0},{0,1},{-1,0},{0,-1},
                            {1,1},{-1,1},{-1,-1},{1,-1}
    };

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

