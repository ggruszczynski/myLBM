

#include "Node.h"


void Node::ComputeRho()
{
	rho = 0;
	for (double f : fIn) {
		rho+=f;
	}
}

void Node::ComputeU()
{
	u << 0, 0; // reset velocities

    u2D.x=0;  u2D.y=0;
    for (unsigned i = 0; i < sizeof(fIn)/ sizeof(double); ++i){
        u += fIn[i] * d2q9Constants->ee[i];
        u2D.x +=fIn[i] *d2q9Constants->e[i].x;
        u2D.y +=fIn[i] *d2q9Constants->e[i].y;
    }


	u = u / this->rho;

    u2D.x/=rho;
    u2D.y/=rho;
}

void Node::ComputefEq()
{
	double eu;
//	double u2 = u.dot(u);
    double u2 = u2D.x * u2D.x + u2D.y * u2D.y;
	for (unsigned i = 0; i < sizeof(fIn)/ sizeof(double); ++i)
	{
//		eu = u.dot(d2q9Constants->ee[i]);
        eu = u2D.x * d2q5Constants->e[i].x + u2D.y * d2q5Constants->e[i].y;
		feq[i] = 1 + 3 * eu;
		feq[i] += 4.5 * eu*eu;
		feq[i] -= 1.5 * u2;
		feq[i] *= rho * d2q9Constants->w[i];
	}
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
		fOut[i] = fIn[i] + omega* (feq[i]- fIn[i]);
	}
}

void Node::SetU(const double& setU, const double& setV)
{
	u << setU, setV;
    u2D.x=setU;  u2D.y=setV;
}

void Node::SetFIn(double newFIn[9])
{
	for (int i = 0; i < sizeof(fIn)/ sizeof(double); ++i) {
		fIn[i] = newFIn[i];
	}
}

void Node::ComputeT()
{
	T = 0;
	for (double t : TIn) {
		T+= t;
	}
}

void Node::ComputeTeq()
{
	double eu;

	for (unsigned i = 0; i < sizeof(Teq)/ sizeof(double); ++i)
	{
//		eu = u.dot(d2q5Constants->ee[i]);
//        eu = u[0] * d2q5Constants->e[i].x + u[1] * d2q5Constants->e[i].y;
        eu = u2D.x * d2q5Constants->e[i].x + u2D.y * d2q5Constants->e[i].y;
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

