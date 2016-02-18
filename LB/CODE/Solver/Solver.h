/*
 * Solver.h
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#pragma managed(push, off)

#include "../IO/VTKWriter.h"
#include "../IO/XMLParser.h"

#include <thread>
#include <iostream>
#include <memory>


#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "../Mesher/MeshDirector.h"
#include "../Mesher/ChannelMeshBuider.h"
#include "../Mesher/LidMeshBuilder.h"
#include "../Mesher/DiffusionValidatorMeshBuilder.h"
#include "../Mesher/AdvectionValidatorMeshBuilder.h"
#include "../Mesher/WallForceValidatorMeshBuilder.h"

class Solver {
private:	
	double omegaNS; //NS relaxation parameter
	double omegaNSTurb; 
	double omegaT; //relaxation parameter - passive scalar

	//double omegaTturb;

	shared_ptr <VTKWriter> writer;
	shared_ptr <XMLParser> xmlParser;

	Singleton<D2Q9Constants>*d2q9Constants;
	Singleton<D2Q5Constants>*d2q5Constants;

	//DdQqConstants *d2q9Constants;
	//Singleton<D2Q5Constants> *d2q5Constants;

	vector< vector<shared_ptr <Node>> > mesh;

	shared_ptr<Case> mycase;

	MeshDirector meshDirector;
public:
	void Collisions();
	void StreamToNeighbour(const int &x, const int &y);
	void Stream();

	void Run();
	double GetAverageT();
	double GetVarT();
	double GetNWallShearForce();

	shared_ptr <Node> GetNode(const int &x, const int &y);

	void IsDensityValid();
	void ReplaceNode(const int &x, const int &y, shared_ptr <Node>);

	vector< vector<shared_ptr <Node>> > CloneMesh();


	Solver() : writer(new VTKWriter)
	{	
		ChannelMeshBuilder channel_mesh_builder("KarmanCase.xml");
		LidMeshBuilder lid_mesh_builder("LidDrivenCavity.xml");

		DiffusionValidatorMeshBuilder diffusion_validator_mesh_builder("DefaultCase.xml");
		AdvectionValidatorMeshBuilder advection_validator_mesh_builder("DefaultCase.xml");
		WallForceValidatorMeshBuilder wall_force_validator_mesh_builder("WallForceWalidatorCase.xml");



		//meshDirector.SetBuilder(&lid_mesh_builder);

		//meshDirector.SetBuilder(&wall_force_validator_mesh_builder);
		//meshDirector.SetBuilder(&diffusion_validator_mesh_builder);
		//meshDirector.SetBuilder(&advection_validator_mesh_builder);

		meshDirector.SetBuilder(&channel_mesh_builder);

		mesh = meshDirector.MakeMesh();

		mycase = meshDirector.GetCase();
		omegaNS = 1. / (3 * mycase -> bcValues_.nu + 0.5);      //NS relaxation parameter
		omegaT  = 1. / (3 * mycase -> passive_scalar_blobb_.K + 0.5 ); //Passive Scalar relaxation parameter
		cout << "omegaNS = " << omegaNS << endl;
		cout << "omegaT = " << omegaT << endl;

		d2q9Constants = Singleton<D2Q9Constants>::get_instance();
		d2q5Constants = Singleton<D2Q5Constants>::get_instance();

		//auto constants_test = DConstantsTest::get_instance();
		//constants_test->InitializeMe();
		//constants_test->wtest[0] = 666;
		//cout << constants_test->wtest[0] << endl;		
	}


	 ~Solver();
};

#endif /* SOLVER_H_ */
