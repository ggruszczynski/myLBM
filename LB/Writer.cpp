#include "Writer.h"


void Writer :: writeVTK(int t, int nx, int ny, int nz, double ***rho, int write_rho, double ***pre, int write_pre, double ***ux, double ***uy, double ***uz, int write_vel, char *directory, char *filename)

{
	int x, y, z, dir;
	char dataFileName[255];
	FILE *dataFile;

	dir = _mkdir(directory);
//#ifdef WIN32
//	dir = mkdir(directory);
//#else
//	dir = mkdir(directory, 0777);
//#endif
	if (dir == 0) printf("Error: Can't create output directory!\n");
	//sprintf(dataFileName, "%s/%s_%07d.vti", directory, filename, t);
	sprintf_s(dataFileName, "%s/%s_%07d.vti", directory, filename, t);
	dataFile = fopen(dataFileName, "w");
	//dataFile = fopen_s(&dataFile, dataFileName, "w");
	fprintf(dataFile, "<?xml version=\"1.0\"?>\n");
	fprintf(dataFile, "<!-- openLBMflow v1.0.1, www.lbmflow.com -->\n");
	fprintf(dataFile, "<VTKFile type=\"ImageData\" version=\"0.1\" byte_order=\"LittleEndian\">\n");
	fprintf(dataFile, "  <ImageData WholeExtent=\"0 %d 0 %d 0 %d\" Origin=\"0 0 0\" Spacing=\"1 1 1\">\n", nx - 1, ny - 1, nz - 1);
	fprintf(dataFile, "  <Piece Extent=\"0 %d 0 %d 0 %d\">\n", nx - 1, ny - 1, nz - 1);
	fprintf(dataFile, "    <PointData Scalars=\"scalars\">\n");

	//fprintf_s(dataFile, "<?xml version=\"1.0\"?>\n");
	//fprintf_s(dataFile, "<!-- openLBMflow v1.0.1, www.lbmflow.com -->\n");
	//fprintf_s(dataFile, "<VTKFile type=\"ImageData\" version=\"0.1\" byte_order=\"LittleEndian\">\n");
	//fprintf_s(dataFile, "  <ImageData WholeExtent=\"0 %d 0 %d 0 %d\" Origin=\"0 0 0\" Spacing=\"1 1 1\">\n", nx - 1, ny - 1, nz - 1);
	//fprintf_s(dataFile, "  <Piece Extent=\"0 %d 0 %d 0 %d\">\n", nx - 1, ny - 1, nz - 1);
	//fprintf_s(dataFile, "    <PointData Scalars=\"scalars\">\n");

	//write density
	if (write_rho != 0)
	{
		fprintf(dataFile, "      <DataArray type=\"Float32\" Name=\"Density\" NumberOfComponents=\"1\" format=\"ascii\">\n");
		for (z = 0; z<nz; z++)
		{
			for (y = 0; y<ny; y++)
			{
				for (x = 0; x<nx; x++)
				{
					fprintf(dataFile, "%.4e ", rho[x][y][z]);
				}
				fprintf(dataFile, "\n");
			}
		}
		fprintf(dataFile, "      </DataArray>\n");
	}

	//write pressure
	if (write_pre != 0)
	{
		fprintf(dataFile, "      <DataArray type=\"Float32\" Name=\"Pressure\" NumberOfComponents=\"1\" format=\"ascii\">\n");
		for (z = 0; z<nz; z++)
		{
			for (y = 0; y<ny; y++)
			{
				for (x = 0; x<nx; x++)
				{
#ifdef MultiPhase
					fprintf(dataFile, "%.4e ", rho[x][y][z] / 3.0 + G*phi[x][y][z] * phi[x][y][z] / 6.0);
#else
					fprintf(dataFile, "%.4e ", rho[x][y][z] / 3.0);
#endif
				}
				fprintf(dataFile, "\n");
			}
		}
		fprintf(dataFile, "      </DataArray>\n");
	}

	//fprintf(dataFile, "    <PointData Vectors=\"Velocity\">\n");
	//write velocity
	if (write_vel != 0)
	{
		fprintf(dataFile, "      <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\n");
		for (z = 0; z<nz; z++)
		{
			for (y = 0; y<ny; y++)
			{
				for (x = 0; x<nx; x++)
				{
					fprintf(dataFile, "%.4e ", ux[x][y][z]);
					fprintf(dataFile, "%.4e ", uy[x][y][z]);
#ifdef Lattice3D
					fprintf(dataFile, "%.4e ", uz[x][y][z]);
#else
					fprintf(dataFile, "%d ", 0);
#endif

				}
				fprintf(dataFile, "\n");
			}
		}
		fprintf(dataFile, "      </DataArray>\n");
	}
	//fprintf(dataFile, "    </PointData>\n");


	fprintf(dataFile, "    </PointData>\n");

	fprintf(dataFile, "    <CellData>\n");
	fprintf(dataFile, "    </CellData>\n");
	fprintf(dataFile, "  </Piece>\n");
	fprintf(dataFile, "  </ImageData>\n");

	fprintf(dataFile, "</VTKFile>\n");
	fclose(dataFile);
}

Writer::Writer()
{
}


Writer::~Writer()
{
}
