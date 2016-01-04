/*
 * Solver.h
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#ifndef SOLVER_H_
#define SOLVER_H_
#include "../DConstantsTest.h"

#include "Writer.h"

#include <omp.h>
#include <iostream>
#include <memory>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "MeshDirector.h"
#include "ChannelMeshBuider.h"
#include "LidMeshBuilder.h"

class Solver {
private:	
	double omegaNS; //relaxation parameter
	double omegaT; //relaxation parameter - passive scalar

	//double omegaTturb;

	shared_ptr <Writer> writer;
	Singleton<D2Q9Constants>*d2q9Constants;
	Singleton<D2Q5Constants>*d2q5Constants;

	//DdQqConstants *d2q9Constants;
	//Singleton<D2Q5Constants> *d2q5Constants;

	vector< vector<shared_ptr <Node>> > mesh;

	Case *mycase;
	MeshDirector meshDirector;
public:
	void Collisions();
	void StreamToNeighbour(const int &x, const int &y);
	void Stream();
	void Run();
	double GetAverageT();
	double GetVarT();

	double GetEddyViscosity(Node &node) const;

	shared_ptr <Node> GetNode(const int &x, const int &y);
	void ReplaceNode(const int &x, const int &y, shared_ptr <Node>);
	void InsertNode(const int &x, const int &y, Node & newNode);

	Solver() : writer(new Writer)
	{	
		ChannelMeshBuilder channel_mesh_builder;
		LidMeshBuilder lid_mesh_builder;
		//meshDirector.SetBuilder(&lid_mesh_builder);
		meshDirector.SetBuilder(&channel_mesh_builder);

		mycase = meshDirector.GetCase();
		omegaT  = 1. / (2 * mycase -> passive_scalar_blobb_.K + 0.5 ); //Passive Scalar relaxation parameter
		omegaNS = 1. / (3 * mycase -> bcValues_.nu + 0.5);      //NS relaxation parameter
		//omegaNS = 4.5;
		cout << "omegaNS = " << omegaNS << endl;
		cout << "omegaT = " << omegaT << endl;

		d2q9Constants = Singleton<D2Q9Constants>::get_instance();
		d2q5Constants = Singleton<D2Q5Constants>::get_instance();

		//auto constants_test = DConstantsTest::get_instance();
		//constants_test->InitializeMe();
		//constants_test->wtest[0] = 666;
		//cout << constants_test->wtest[0] << endl;

		mesh = meshDirector.MakeMesh();
	}


	 ~Solver();

};

#endif /* SOLVER_H_ */
