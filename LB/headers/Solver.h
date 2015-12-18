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

#include <iostream>
#include <memory>

class Solver {
private:
	D2Q9Constants  *d2q9Constants;
	double omega; //relaxation parameter
	//vector<Node> vcol666;
	//vector< vector<Node> >  mesh666;


	vector< shared_ptr <Node>> vcol;
	vector< vector<shared_ptr <Node>> > mesh;

public:
	void NaiveCollision();
	void StreamToNeighbour(const int &x, const int &y);
	void Update();

	shared_ptr <Node> GetNode(const int &x, const int &y);
	void ReplaceNode(const int &x, const int &y, shared_ptr <Node>);
	void InsertNode(const int &x, const int &y, Node & newNode);
	void MakeLidDrivenCavityMesh(const unsigned & set_n_rows, const unsigned & set_n_cols);

	Solver(const unsigned & set_n_rows, const unsigned & set_n_cols) : omega(1)//, vcol666(set_n_cols), mesh666(set_n_rows, vcol666 )
	{
		MakeLidDrivenCavityMesh(set_n_rows, set_n_cols);
		d2q9Constants = D2Q9Constants::GetInstance();
	}


	virtual ~Solver();

};

#endif /* SOLVER_H_ */
