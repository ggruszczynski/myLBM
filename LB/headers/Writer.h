#pragma once

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include <memory>

#pragma warning(disable : 4996)

class Writer
{
private:
	void WriteDensity(vector<vector<shared_ptr<Node>>> mesh, FILE *dataFile, int &nx, int &ny, int &nz);
	void WriteNodeType(vector<vector<shared_ptr<Node>>> mesh, FILE *dataFile, int &nx, int &ny, int &nz);
	void WriteVelocity(vector<vector<shared_ptr<Node>>> mesh, FILE *dataFile, int &nx, int &ny, int &nz);
public:
	void writeVTK(vector< vector<shared_ptr<Node>> > mesh, int t, string directory, string filename);
	


	void  writeVTK_old(int t, int nx, int ny, int nz, double ***rho, int write_rho, double ***pre, int write_pre, double ***ux, double ***uy, double ***uz, int write_vel, char *directory, char *filename);

	Writer();
	~Writer();
};

