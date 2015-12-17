#pragma once

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning(disable : 4996)

class Writer
{
public:

	void  writeVTK(int t, int nx, int ny, int nz, double ***rho, int write_rho, double ***pre, int write_pre, double ***ux, double ***uy, double ***uz, int write_vel, char *directory, char *filename);

	Writer();
	~Writer();
};

