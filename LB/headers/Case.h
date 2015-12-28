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
		x = set_x / 5 + 1;  
		y = set_y / 2 + 3;   
		r = set_y / 10 + 1; 

	}
};

struct PassiveScalarBlobb
{
	double T; // value

	unsigned x;   // position of the cylinder; (exact
	unsigned y;   // y - symmetry is avoided)
	unsigned r;  //radius of the cylinder

	PassiveScalarBlobb(const unsigned & set_x, const unsigned & set_y): T(150)
	{
		x = set_x / 2 + 1;
		y = set_y / 2 + 3;
		r = set_y / 10 + 1;

	}
};

struct Case
{	
	unsigned x; //width x
	unsigned y; //height y

	unsigned totalTime; // number of timeSteps
	unsigned timeSave; // after timeSave amount of steps -> save

	Obstacle obstacle_;
	PassiveScalarBlobb passive_scalar_blobb_;
	BCValues bcValues;

	Case(): x(100),y(100),obstacle_(x,y),passive_scalar_blobb_(x,y)
	{
		 totalTime = 6000;
		 timeSave = 50;


		 bcValues.uInlet = 0.1;
		 bcValues.uLid = 0.05;
		 bcValues.Re = 100;
		 bcValues.nu = bcValues.uInlet * 2 * obstacle_.r / bcValues.Re;  // kinematic viscosity
	};

};