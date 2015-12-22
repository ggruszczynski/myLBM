

#include "../headers/Node.h"


void Node::ComputeRho()
{
	rho = std::accumulate(fIn.begin(), fIn.end(), 0.0);

	//rho = 0;
	//for (auto iter = fIn.begin(); iter != fIn.end(); ++iter)
	//{
	//	rho += *iter;
	//}
}

void Node::ComputeU()
{
	//for_each(d2q9Constants.e.begin(), d2q9Constants.e.end(), [&, this](Vector2d e)) {u = }
	//D2Q9Constants ::e.begin()
	u << 0, 0; // reset velocities
	auto it_f = this->fIn.begin();
	for (auto it_e = D2Q9Constants::e.begin(); it_e != D2Q9Constants::e.end(); ++it_e, ++it_f)
		u += c* *it_f* *it_e;

	u = u / this->rho;
}

void Node::ComputefEq()
{
	double eu;
	double u2 = u.dot(u);
	double c2 = c*c;
	double c4 = c*c*c*c;
	for (unsigned i = 0; i < fIn.size(); ++i)
	{
		eu = u.dot(D2Q9Constants::e[i]);
		feq[i] = 1 + 3 * eu / c2;
		feq[i] += 4.5 * eu*eu /c4;
		feq[i] -= 1.5 * u2 / c2;
		feq[i] *= rho * D2Q9Constants::w[i];
	}
}

void Node::NodeCollision(double const & omega)
{
	for (unsigned i = 0; i < fOut.size(); ++i)
	{
		fOut[i] = (1. - omega)* fIn[i] + omega* feq[i];
	}
}

Node::~Node() {}

