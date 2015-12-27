/*
 * Solver.h
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "D2Q9Constants.h"
#include  "Writer.h"
#include "Node.h"
#include "Wall.h"
#include "MovingWall.h"
#include "VelocityInlet.h"
#include "PressureOutlet.h"

#include <iostream>
#include <memory>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

class Solver {
private:
	double omega; //relaxation parameter
	double uLid; //Lid velocity
	unsigned totalTime; // number of timeSteps
	unsigned timeSave; // after timeSave amount of steps -> save
	double uInlet; //inlet velocity (channel flow)

	double Re; //Reynolds number
	double nu; // kinematic viscosity

	shared_ptr <Writer> writer;
	DdQqConstants<D2Q9Constants>*d2q9Constants;
	DdQqConstants<D2Q5Constants>*d2q5Constants;

	//vector< shared_ptr <Node>> vec_pion;
	vector< vector<shared_ptr <Node>> > mesh;


public:
	void Collisions();
	void StreamToNeighbour(const int &x, const int &y);
	void Stream();
	void Run();

	shared_ptr <Node> GetNode(const int &x, const int &y);
	void ReplaceNode(const int &x, const int &y, shared_ptr <Node>);
	void InsertNode(const int &x, const int &y, Node & newNode);
	void MakeLidDrivenCavityMesh_old(const unsigned& set_x, const unsigned& set_y);
	void MakeLidDrivenCavityMesh(const unsigned & set_n_rows, const unsigned & set_n_cols);
	void MakeChannelMesh(const unsigned & set_n_rows, const unsigned & set_n_cols);

	Solver(const unsigned & set_x, const unsigned & set_y, const unsigned & set_totalTime, const unsigned & set_timeSave) : 
		omega(1), totalTime(set_totalTime), timeSave(set_timeSave), writer(new Writer)
	{	
		
		d2q9Constants = DdQqConstants<D2Q9Constants>::get_instance();
		d2q5Constants = DdQqConstants<D2Q5Constants>::get_instance();

		//DdQqConstants<D2Q5Constants>*test = DdQqConstants<D2Q5Constants>::get_instance();
		//test->w[0] = 123;

		//Node testnode;// = Node;

	    Re = 100;	 // Reynolds number
		uLid = 0.05;
		//double nu = uLid * set_x / Re;  
		//omega = 1 / (3 * nu + 0.5); // relaxation parameter
		//omega = 0.7;
		//MakeLidDrivenCavityMesh(set_x, set_y);

		uInlet = 0.1;
		//omega = 1.5;
		MakeChannelMesh(set_x, set_y);
	
	}


	virtual ~Solver();

};

#endif /* SOLVER_H_ */
