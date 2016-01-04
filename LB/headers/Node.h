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
#include "D2Q5Constants.h"
#include "Enums.h"
using namespace std;

#include <Eigen/Dense>
using namespace Eigen;


class Node {

protected:
	Singleton<D2Q9Constants>*d2q9Constants;
	Singleton<D2Q5Constants>*d2q5Constants;
	//DdQqConstants*d2q9Constants;
	//DdQqConstants*d2q5Constants;

	NodeType nodeType;

	vector<double> fIn; //NS: probability distribution function
	vector<double> feq; 
	vector<double> fOut; // probability distribution function - temporary variable

	vector<double> TIn; //PassiveScalar: probability distribution function 
	vector<double> Teq; 
	vector<double> TOut; // probability distribution function - temporary variable


	double rho; // density
	double T; // Passive Scalar
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> u;
	// see http://eigen.tuxfamily.org/dox/group__TopicUnalignedArrayAssert.html and http://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html

	
	//double c; 

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	virtual void ComputeRho();
	virtual void ComputeU();
    void ComputefEq();


	double GetEddyViscosity();

	virtual void NodeCollisionFout(double const& omega);
	virtual void SetU(const double &setU, const double &setV);
	void SetFIn(vector<double> newFIn);

	void ComputeT();
	void ComputeTeq();
	virtual void NodeCollisionTout(double const& omegaT);

	//Node(): fIn(9, 0), feq(9, 0), fOut(9, 0), rho(1), uSqr(0),c(1),u(0,0)
	Node():  rho(1), T(0), u(0, 0)
	{
	
		//d2q9Constants = D2Q9Constants::get_instance();
		//d2q5Constants = D2Q5Constants::get_instance();
		d2q9Constants = Singleton<D2Q9Constants>::get_instance();
		d2q5Constants = Singleton<D2Q5Constants>::get_instance();


		fIn = d2q9Constants->w;
		feq = d2q9Constants->w;
		fOut = d2q9Constants->w;

		TIn = d2q5Constants->w;
		Teq = d2q5Constants->w;
		TOut = d2q5Constants->w;

		nodeType = FluidType;
	}

	virtual ~Node();

	friend class Writer;
	friend class Solver;

	friend class MeshBuilder;
	friend class LidMeshBuilder;
	friend class ChannelMeshBuilder;
	friend class MeshDirector;
};

#endif /* NODE_H_ */
