/*
 * Solver.h
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include "../DConstantsTest.h"

#include "Case.h"
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
#include "Mesher.h"

class Solver {
private:
	Case mycase;
	double omegaNS; //relaxation parameter
	double omegaT; //relaxation parameter - passive scalar
	//double uLid; //Lid velocity
	//unsigned totalTime; // number of timeSteps
	//unsigned timeSave; // after timeSave amount of steps -> save
	//double uInlet; //inlet velocity (channel flow)

	//double Re; //Reynolds number
	//double nu; // kinematic viscosity

	shared_ptr <Writer> writer;
	Singleton<D2Q9Constants>*d2q9Constants;
	Singleton<D2Q5Constants>*d2q5Constants;

	//DdQqConstants *d2q9Constants;
	//Singleton<D2Q5Constants> *d2q5Constants;

	//vector< shared_ptr <Node>> vec_pion;
	vector< vector<shared_ptr <Node>> > mesh;

	Mesher mesher;

public:
	void Collisions();
	//template <typename T> void StreamToNeighbour(const int &x, const int &y, typename Singleton<T>::Singleton* ddqq_constants);

	void StreamToNeighbour(const int &x, const int &y);
	void Stream();
	void Run();

	shared_ptr <Node> GetNode(const int &x, const int &y);
	void ReplaceNode(const int &x, const int &y, shared_ptr <Node>);
	void InsertNode(const int &x, const int &y, Node & newNode);
	//void MakeLidDrivenCavityMesh_old(const unsigned& set_x, const unsigned& set_y);
	//void MakeLidDrivenCavityMesh(const unsigned & set_n_rows, const unsigned & set_n_cols);
	//void MakeChannelMesh(const unsigned & set_n_rows, const unsigned & set_n_cols);

	Solver() : writer(new Writer)
	{	

		omegaNS = 1 / (3 * mycase.bcValues.nu + 0.5);      // relaxation parameter
		omegaT = 0.5;

		d2q9Constants = Singleton<D2Q9Constants>::get_instance();
		d2q5Constants = Singleton<D2Q5Constants>::get_instance();

		//auto constants_test = DConstantsTest::get_instance();
		//constants_test->InitializeMe();
		//constants_test->wtest[0] = 666;
		//cout << constants_test->wtest[0] << endl;

		//mesh = mesher.MakeChannelMesh(mycase.x, mycase.y, mycase);
		mesh = mesher.MakeLidDrivenCavityMesh(mycase.x, mycase.y, mycase);
	}


	virtual ~Solver();

};

#endif /* SOLVER_H_ */
