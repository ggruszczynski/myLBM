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
#include "Enums.h"
using namespace std;

#include <Eigen/Dense>
using namespace Eigen;


class Node {

protected:
	NodeType nodeType;

	//D2Q9Constants  *d2q9Constants;

	//bool isWall;// = false;
	vector<double> fIn; // probability distribution function
	vector<double> feq;// = 0;
	vector<double> fOut; // probability distribution function - temporary variable

	double rho; // density
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> u;
	// see http://eigen.tuxfamily.org/dox/group__TopicUnalignedArrayAssert.html and http://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html

	
	double c; 

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	virtual void ComputeRho();
	virtual void ComputeU();
    void ComputefEq();
	virtual void NodeCollision(double const& omega);
	void SetU(const double &setU, const double &setV);
	void SetFIn(vector<double> newFIn);

	//Node(): fIn(9, 0), feq(9, 0), fOut(9, 0), rho(1), uSqr(0),c(1),u(0,0)
	Node(): fIn(D2Q9Constants::w), feq(D2Q9Constants::w), fOut(D2Q9Constants::w),  rho(1), u(0, 0), c(1)
	{
		nodeType = FluidType;
	}

	virtual ~Node();

	friend class Writer;
	friend class Solver;
};

#endif /* NODE_H_ */
