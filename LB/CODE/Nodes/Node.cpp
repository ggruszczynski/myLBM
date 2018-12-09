

#include "Node.h"


void Node::ComputeRho()
{
	rho = 0;

	for (int i = 0; i < sizeof(fIn)/ sizeof(double); ++i) {
		rho+=fIn[i];
	}
	//rho = std::accumulate(fIn.begin(), fIn.end(), 0.0);
}

void Node::ComputeU()
{
	u << 0, 0; // reset velocities

	//auto it_f = this->fIn.begin();
	//for (auto it_e = d2q9Constants->ee.begin(); it_e != d2q9Constants->ee.end(); ++it_e, ++it_f)
	//	u += *it_f* *it_e;
	//u += c* *it_f* *it_e; // c is assumed to be always = 1, thus it may be skipped

	for (unsigned i = 0; i < sizeof(fIn)/ sizeof(double); ++i)
		u += fIn[i] * d2q9Constants->ee[i];

	u = u / this->rho;
}

void Node::ComputefEq()
{
	double eu;
	double u2 = u.dot(u);
	for (unsigned i = 0; i < sizeof(fIn)/ sizeof(double); ++i)
	{
		eu = u.dot(d2q9Constants->ee[i]);
		feq[i] = 1 + 3 * eu;
		feq[i] += 4.5 * eu*eu;
		feq[i] -= 1.5 * u2;
//		feq[i] *= rho * d2q9Constants->vw[i];
		feq[i] *= rho * d2q9Constants->w[i];
	}

	/// c is always = 1, thus it may be skipped...
	//double eu;
	//double u2 = u.dot(u);
	//double c2 = c*c;
	//double c4 = c*c*c*c;
	//for (unsigned i = 0; i < fIn.size(); ++i)
	//{
	//	eu = u.dot(d2q9Constants->ee[i]);
	//	feq[i] = 1 + 3 * eu / c2;
	//	feq[i] += 4.5 * eu*eu /c4;
	//	feq[i] -= 1.5 * u2 / c2;
	//	feq[i] *= rho * d2q9Constants->vw[i];
	//}
}

void Node::CalcEddyViscosity(double nu)
{
	Matrix2d localStressTensor;
	Matrix2d localStressTensor2; // coefficient wise product (each by each, ex a11* a11, a12*a12, a21*a21, a22*a22

	for (unsigned i = 0; i < d2q9Constants->ee.size(); ++i) //each node
	{
		localStressTensor(0, 0) = d2q9Constants->ee[i](0)* d2q9Constants->ee[i](0) * (fIn[i] - feq[i]);
		localStressTensor(1, 0) = d2q9Constants->ee[i](1)* d2q9Constants->ee[i](0) * (fIn[i] - feq[i]);
		localStressTensor(0, 1) = d2q9Constants->ee[i](0)* d2q9Constants->ee[i](1) * (fIn[i] - feq[i]);
		localStressTensor(1, 1) = d2q9Constants->ee[i](1)* d2q9Constants->ee[i](1) * (fIn[i] - feq[i]);
	}
	localStressTensor2 = localStressTensor.cwiseProduct(localStressTensor);

	double Q = sqrt(localStressTensor2.sum()); // magnitude of the non-equilibrium stress tensor

	double S;
	S = sqrt(nu * nu + 18 * d2q9Constants->CSmag2 *Q);
	S -= nu;
	S /= 6;

	this->nuTurb = S;
}

void Node::NodeCollisionFout(double const & omega)
{
	for (unsigned i = 0; i <sizeof(fOut)/ sizeof(double); ++i)
	{
		fOut[i] = (1. - omega)* fIn[i] + omega* feq[i];
		//fOut[i] = fIn[i] + omega* (feq[i]- fIn[i]);  //todo is it faster?
	}
}

void Node::SetU(const double& setU, const double& setV)
{
	u << setU, setV;
}

void Node::SetFIn(double newFIn[9])
{
	for (int i = 0; i < 9; ++i) {
		fIn[i] = newFIn[i];
	}
}

void Node::ComputeT()
{
//	T = std::accumulate(TIn.begin(), TIn.end(), 0.0);
	T = 0;
	for (int i = 0; i < sizeof(TIn)/ sizeof(double); ++i) {
		T+=TIn[i];
	}
}

void Node::ComputeTeq()
{
	double eu;

	for (unsigned i = 0; i < sizeof(Teq)/ sizeof(double); ++i)
	{
		eu = u.dot(d2q5Constants->ee[i]);
		Teq[i] = 1 + 3 * eu;
		Teq[i] *= T * d2q5Constants->w[i];
	}
}

void Node::NodeCollisionTout(double const& omegaT)
{
	for (unsigned i = 0; i < sizeof(TOut)/ sizeof(double); ++i)
	{
		TOut[i] = (1. - omegaT)* TIn[i] + omegaT* Teq[i];
	}
}

Node::~Node() {}

