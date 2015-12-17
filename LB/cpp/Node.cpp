/*
 * Node.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#include "../headers/Node.h"

/*Node::Node() {
	// TODO Auto-generated constructor stub

}*/

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
	u << 0, 0; // reset velociti
	auto it_f = this->fIn.begin();
	for (auto it_e = D2Q9Constants::e.begin(); it_e != D2Q9Constants::e.end(); ++it_e, ++it_f)
		u += *it_f* *it_e;

	u = u / this->rho;
	uSqr = u.dot(u);
}

void Node::ComputefEq()
{
	double eu = 0;
	double c2 = c*c;
	double c4 = c*c*c*c;
	for (unsigned i = 0; i < fIn.size();++i)
	{
		eu = u.dot(D2Q9Constants::e[i]);
		feq[i] = 1 + 3 * eu / c2;
		feq[i] += 4.5 * eu*eu /c4;
		feq[i] -= 1.5 * uSqr / c2;
		feq[i] = feq[i] * rho * D2Q9Constants::w[i];
	}
}

void Node::Collision()
{
	for (unsigned i = 0; i < fOut.size(); ++i)
	{
		fOut[i] = (1. - D2Q9Constants::omega)* fIn[i] + D2Q9Constants::omega* fIn[i];
	}

}

void Node::ZouHeVelocity_Lid()
{
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

