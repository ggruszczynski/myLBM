/*
 * Node.h
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include <numeric>
#include "D2Q9Constants.h"
using namespace std;

#include <Eigen/Dense>
using namespace Eigen;

class Node {

protected:
	//D2Q9Constants  *d2q9Constants;

	bool isWall;// = false;
	vector<double> fIn; // probability distribution function
	vector<double> feq;// = 0;
	vector<double> fOut; // probability distribution function - temporary variable

	double rho; // density
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> u;
	// see http://eigen.tuxfamily.org/dox/group__TopicUnalignedArrayAssert.html and http://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
	// Vector2d  u; // velocity
	double uSqr; // u*u
	
	double c; 

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	void ComputeRho();
	void ComputeU();
	void ComputefEq();
	virtual void Collision();

	void ZouHeVelocity_Lid();

	Node(): isWall(false) , fIn(9, 0), feq(9, 0), fOut(9, 0), rho(1), uSqr(0),c(1)
	{
		//d2q9Constants = D2Q9Constants::GetInstance();
		u << 0, 0;
		
		
		//d2q9Constants->w[1] = 666;
		//cout << "inside Node " << d2q9Constants->w[1]<< endl ;
		//d2q9Constants = new D2Q9Constants();
	}

	virtual ~Node();


	friend class Solver;
};

#endif /* NODE_H_ */
