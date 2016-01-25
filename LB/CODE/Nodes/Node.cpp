

#include "Node.h"


void Node::ComputeRho()
{
	rho = std::accumulate(fIn.begin(), fIn.end(), 0.0);
}

void Node::ComputeU()
{
	//for_each(d2q9Constants.e.begin(), d2q9Constants.e.end(), [&, this](Vector2d e)) {u = }
	//D2Q9Constants ::e.begin()
	u << 0, 0; // reset velocities
	auto it_f = this->fIn.begin();
	for (auto it_e = d2q9Constants->e.begin(); it_e != d2q9Constants->e.end(); ++it_e, ++it_f)
		u += *it_f* *it_e;
	//u += c* *it_f* *it_e; // c is assumed to be always = 1, thus it may be skipped

	u = u / this->rho;
}

void Node::ComputefEq()
{
	double eu;
	double u2 = u.dot(u);
	for (unsigned i = 0; i < fIn.size(); ++i)
	{
		eu = u.dot(d2q9Constants->e[i]);
		feq[i] = 1 + 3 * eu;
		feq[i] += 4.5 * eu*eu;
		feq[i] -= 1.5 * u2;
		feq[i] *= rho * d2q9Constants->w[i];
	}

	/// c is always = 1, thus it may be skipped...
	//double eu;
	//double u2 = u.dot(u);
	//double c2 = c*c;
	//double c4 = c*c*c*c;
	//for (unsigned i = 0; i < fIn.size(); ++i)
	//{
	//	eu = u.dot(d2q9Constants->e[i]);
	//	feq[i] = 1 + 3 * eu / c2;
	//	feq[i] += 4.5 * eu*eu /c4;
	//	feq[i] -= 1.5 * u2 / c2;
	//	feq[i] *= rho * d2q9Constants->w[i];
	//}
}

void Node::CalcEddyViscosity(double nu)
{
	Matrix2d localStressTensor;
	Matrix2d localStressTensor2; // coefficient wise product (each by each, ex a11* a11, a12*a12, a21*a21, a22*a22

	for (unsigned i = 0; i < d2q9Constants->e.size(); ++i) //each node
	{
		localStressTensor(0, 0) = d2q9Constants->e[i](0)* d2q9Constants->e[i](0) * (fIn[i] - feq[i]);
		localStressTensor(1, 0) = d2q9Constants->e[i](1)* d2q9Constants->e[i](0) * (fIn[i] - feq[i]);
		localStressTensor(0, 1) = d2q9Constants->e[i](0)* d2q9Constants->e[i](1) * (fIn[i] - feq[i]);
		localStressTensor(1, 1) = d2q9Constants->e[i](1)* d2q9Constants->e[i](1) * (fIn[i] - feq[i]);
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
	for (unsigned i = 0; i < fOut.size(); ++i)
	{
		fOut[i] = (1. - omega)* fIn[i] + omega* feq[i];
		//fOut[i] = fIn[i] + omega* (feq[i]- fIn[i]);  //todo is it faster?
	}
}

void Node::SetU(const double& setU, const double& setV)
{
	u << setU, setV;
}

void Node::SetFIn(vector<double> newFIn)
{
	fIn = newFIn;
}

void Node::ComputeT()
{
	T = std::accumulate(TIn.begin(), TIn.end(), 0.0);
}

void Node::ComputeTeq()
{
	double eu;

	for (unsigned i = 0; i < Teq.size(); ++i)
	{
		eu = u.dot(d2q5Constants->e[i]);
		Teq[i] = 1 + 3 * eu;
		Teq[i] *= T * d2q5Constants->w[i];
	}
}

void Node::NodeCollisionTout(double const& omegaT)
{
	for (unsigned i = 0; i < TOut.size(); ++i)
	{
		TOut[i] = (1. - omegaT)* TIn[i] + omegaT* Teq[i];
	}
}

Node::~Node() {}

