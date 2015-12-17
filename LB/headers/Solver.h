/*
 * Solver.h
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "Node.h"
#include "Wall.h"
#include "MovingWall.h"


class Solver {
private:
	D2Q9Constants  *d2q9Constants;
	double omega; //relaxation parameter
	vector<Node> vcol;
	vector< vector<Node> >  mesh;



public:
	void NaiveCollision();
	void StreamToNeighbour(const int &x, const int &y);
	void Update();

	Solver(const int & set_n_rows, const int & set_n_cols) : omega(1), vcol(set_n_rows), mesh(set_n_cols, vcol )
	{
		
		vector<Node> vcol2(set_n_rows);
		mesh.push_back(vcol2);
		//vector< vector<int> > A;
		//std::vector<std::vector<int>> A(dimension, std::vector<int>(dimension));

		//d2q9Constants = D2Q9Constants::GetInstance();

	}


	virtual ~Solver();

};

#endif /* SOLVER_H_ */
