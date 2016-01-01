#pragma once

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include "Node.h"
#include <memory>
#include <iomanip>
#include <iostream>    
#include "Case.h"

#include "boost/filesystem.hpp"    // includes all needed Boost.Filesystem declarations
namespace fs = boost::filesystem;

#pragma warning(disable : 4996) // some warnings due to old writing functions


class Writer
{
private:
	int nx, ny, nz; //mesh dimensions

	void WritePassiveScalar(vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile);
	void WriteDensity(vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile);
	void WriteNodeType(vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile);
	void WriteVelocity(vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile);
public:
	void WriteCaseInfo(Case *case_, string directory_, string filename_);
	void writeVTK(vector< vector<shared_ptr<Node>> > &mesh, int t, string directory, string filename);
	void writePointData(vector< vector<shared_ptr<Node>> > &mesh, const int &t,const int &x,const int &y, string directory, string filename);
	void ClearDirectory(string folderPath);

	void  writeVTK_old(int t, int nx, int ny, int nz, double ***rho, int write_rho, double ***pre, int write_pre, double ***ux, double ***uy, double ***uz, int write_vel, char *directory, char *filename);

	Writer();
	~Writer();
};

