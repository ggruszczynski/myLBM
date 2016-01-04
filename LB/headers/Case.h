#pragma once

struct BCValues
{
	double uLid; //Lid velocity
	double uInlet; //inlet velocity (channel flow)

	double nu; // kinematic viscosity
};

struct Obstacle
{
	unsigned x;   // position of the cylinder; (exact
	unsigned y;   // y - symmetry is avoided)
	unsigned r;  //radius of the cylinder
};

struct PassiveScalarBlobb
{
	double T; // value
	double K; // thermal diffusivity [lu^2/ts]

	unsigned x;   // position of the cylinder; (exact
	unsigned y;   // y - symmetry is avoided)
	unsigned r;  //radius of the cylinder

	
};

struct Timer
{
	unsigned totalTime; // number of timeSteps
	unsigned timeToSaveVTK; // after timeToSaveVTK amount of steps -> save VTK
	unsigned timeToSavePointData; // after timeToSaveVTK amount of steps -> save Point Data
};

struct BlockGeom
{
	unsigned x; //width x
	unsigned y; //height y
	unsigned numberOfNodes;
};


struct Case
{	
	Timer timer_;
	BlockGeom meshGeom_;
	Obstacle obstacle_;
	PassiveScalarBlobb passive_scalar_blobb_;
	BCValues bcValues_;

	~Case()
	{
	//	cout << "~Case()" << endl;
	}
};