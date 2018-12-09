
#pragma

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
	D2Q5Constants() : Singleton<D2Q5Constants>(){};
public:
	const double w[5] = {2. / 6, 1. / 6, 1. / 6, 1. / 6, 1. / 6 } ;
    const lattice_vectors e[5] = {{0,0},{1,0},{0,1},{-1,0},{0,-1}};
	const int n = 5;
};


