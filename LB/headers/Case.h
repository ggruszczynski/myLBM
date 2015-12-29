#pragma once

struct BCValues
{
	double uLid; //Lid velocity
	double uInlet; //inlet velocity (channel flow)

	double Re; //Reynolds number
	double nu; // kinematic viscosity
};

struct Obstacle
{
	unsigned x;   // position of the cylinder; (exact
	unsigned y;   // y - symmetry is avoided)
	unsigned r;  //radius of the cylinder

	Obstacle (const unsigned & set_x, const unsigned & set_y)
	{
		x = set_x / 5;
		y = set_y / 2;
		r = 15; 

		
		//x = set_x / 5 + 1;  
		//y = set_y / 2 + 3;   
		//r = set_y / 10 + 1; 
	}
};

struct PassiveScalarBlobb
{
	double T; // value
	double K; // thermal diffusivity [lu^2/ts]

	unsigned x;   // position of the cylinder; (exact
	unsigned y;   // y - symmetry is avoided)
	unsigned r;  //radius of the cylinder

	PassiveScalarBlobb(const unsigned & set_x, const unsigned & set_y) : T(1500), K(0.25)
	{
		x = set_x / 2;
		y = set_y / 2;
		r = 15;
	}
};

struct Case
{	
	unsigned x; //width x
	unsigned y; //height y
	unsigned numberOfNodes;

	unsigned totalTime; // number of timeSteps
	unsigned timeSave; // after timeSave amount of steps -> save

	Obstacle obstacle_;
	PassiveScalarBlobb passive_scalar_blobb_;
	BCValues bcValues;

	Case(): x(400),y(100),numberOfNodes(x*y), obstacle_(x,y),passive_scalar_blobb_(x,y)
	{
		 totalTime = 1000;
		 timeSave = 10;

		 bcValues.uLid = 0.05;

		 bcValues.uInlet = 0.1;
		 bcValues.Re = 100;
		 bcValues.nu = 1. / 6;
		// bcValues.nu = bcValues.uInlet * 2 * obstacle_.r / bcValues.Re;  // kinematic viscosity

	};

};