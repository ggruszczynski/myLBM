#pragma once
#include "Singleton.h"

#include <iostream>
#include <vector>

#include <Eigen/StdVector>
//#include <Eigen/Dense>
using namespace Eigen;
using namespace std;


class DdQqConstants : public Singleton<DdQqConstants>// Singleton
{
	friend class Singleton<DdQqConstants>;
public:
	DdQqConstants():Singleton<DdQqConstants>()
	{
		cout << "DdQqConstants():Singleton<DdQqConstants>()" << endl;
	};
	virtual void InitializeMe(){ cout << "DdQqConstants():virtual void InitializeMe()" << endl; } ;

	vector <double> wtest;

	//vector<Vector2d, Eigen::aligned_allocator<Eigen::Vector2d> > e; // velocities directions				
	//vector <double> w;   // weigths
	//					 //	 const double cs2;			// lattice speed ^2 //  TODO: (where shall I store it?)

	//DdQqConstants();
	//~DdQqConstants();
};

