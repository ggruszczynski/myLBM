#pragma once

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Nodes/Node.h"
#include <memory>
#include <iomanip>
#include <iostream>    
#include "../Cases/Case.h"


#include <thread>
#include "boost/filesystem.hpp"    // includes all needed Boost.Filesystem declarations
namespace fs = boost::filesystem;

#pragma warning(disable : 4996) // some warnings due to old writing functions


class Writer
{
private:
	int nx, ny, nz; //mesh dimensions

	void WritePassiveScalar(const vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile) const;
	void WriteDensity(const vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile) const;
	void WriteNodeType(const vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile) const;
	void WriteVelocity(const vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile) const;
	void WriteEddyViscosity(const vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile) const;

public:
	void WriteCrossSectionData(const vector<vector<shared_ptr<Node>>> &mesh, const int &time, const string directory_, const string filename_) const;
	void WriteCaseInfo(Case *case_, string directory_, string filename_) const;
	void writeVTK(const vector< vector<shared_ptr<Node>> > &mesh, const int &time, const string directory, const string filename);
	void writePointData(const vector< vector<shared_ptr<Node>> > &mesh, const int &time,const int &x,const int &y, const string directory, const string filename) const;
	void ClearDirectory(string folderPath);

	void  writeVTK_old(int t, int nx, int ny, int nz, double ***rho, int write_rho, double ***pre, int write_pre, double ***ux, double ***uy, double ***uz, int write_vel, char *directory, char *filename);

	Writer();
	~Writer();
};

