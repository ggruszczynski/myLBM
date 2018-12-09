
#pragma once

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

	shared_ptr <VTKWriter> writer;
	shared_ptr <XMLParser> xmlParser;

	D2Q9Constants* d2q9Constants;
	D2Q5Constants* d2q5Constants;

//	Singleton<D2Q5Constants>*d2q5Constants;
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

	Solver();
	 ~Solver();
};

