#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include <eigen3/Eigen/StdVector>
#include <memory>

#include "../Constants/D2Q9Constants.h"
#include "../Constants/D2Q5Constants.h"
#include "../Constants/Enums.h"

using namespace std;
using namespace Eigen;

struct u2D_Struct
{
    double x;
    double y;
    double length() const { return sqrt(x*x + y*y); }
};


class Node {

protected:

	D2Q9Constants* d2q9Constants;
	D2Q5Constants* d2q5Constants;
//	Singleton<D2Q5Constants>*d2q5Constants;

	NodeType nodeType;

	double fIn[9] = {4. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 36, 1. / 36, 1. / 36, 1. / 36 } ; // NS: PDF
	double feq[9] = {4. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 36, 1. / 36, 1. / 36, 1. / 36 } ;
	double fOut[9] = {4. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 36, 1. / 36, 1. / 36, 1. / 36 } ; // PDF - temporary variable

	double TIn[5] = {2. / 6, 1. / 6, 1. / 6, 1. / 6, 1. / 6 } ; // PassiveScalar: PDF
	double Teq[5] = {2. / 6, 1. / 6, 1. / 6, 1. / 6, 1. / 6 } ;
	double TOut[5] = {2. / 6, 1. / 6, 1. / 6, 1. / 6, 1. / 6 } ; // PDF - temporary variable


	double rho; // density
	double T; // Passive Scalar
	double nuTurb; //eddy Viscosity 

	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> u;
	// see http://eigen.tuxfamily.org/dox/group__TopicUnalignedArrayAssert.html and http://eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html

    u2D_Struct  u2D;
	
	Node& operator=(const Node& cSource);
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	virtual void ComputeRho();
	virtual void ComputeU();
    void ComputefEq();


	void CalcEddyViscosity(double nu);

	virtual void NodeCollisionFout(double const& omega);
	virtual void SetU(const double &setU, const double &setV);
	void SetFIn(double newFIn[9]);

	void ComputeT();
	void ComputeTeq();

	virtual void NodeCollisionTout(double const& omegaT);

	//Node(): fIn(9, 0), feq(9, 0), fOut(9, 0), rho(1), uSqr(0),c(1),u(0,0)
	Node():  rho(1), T(0), nuTurb(0), u(0, 0)
	{
	
		//d2q9Constants = D2Q9Constants::get_instance();
//		d2q5Constants = D2Q5Constants::get_instance();
		d2q9Constants = Singleton<D2Q9Constants>::get_instance();
		d2q5Constants = Singleton<D2Q5Constants>::get_instance();


		nodeType = FluidType;
	}

	virtual ~Node();

	//Node(const Node & nSource)
	//{
	//	fIn = nSource.fIn;
	//	feq = nSource.feq;
	//	fOut = nSource.fOut;

	//	TIn = nSource.TIn;
	//	Teq = nSource.Teq;
	//	TOut = nSource.TOut;

	//	rho = nSource.rho;
	//	T = nSource.T;
	//	nuTurb = nSource.nuTurb;

	//	d2q9Constants = Singleton<D2Q9Constants>::get_instance();
	//	d2q5Constants = Singleton<D2Q5Constants>::get_instance();
	//	nodeType = nSource.nodeType;
	//}

	//Node CloneObj() { return *this; }
	//Node* ClonePtr() { return this; }

	virtual shared_ptr<Node> CloneShrPtr(){ return make_shared<Node>(*this); }

	friend class VTKWriter;
	friend class Solver;

	//hrhr todo
	friend class MeshBuilder;
	friend class LidMeshBuilder;
	friend class ChannelMeshBuilder;
	friend class DiffusionValidatorMeshBuilder;
	friend class AdvectionValidatorMeshBuilder;
	friend class WallForceValidatorMeshBuilder;

	friend class MeshDirector;
};

