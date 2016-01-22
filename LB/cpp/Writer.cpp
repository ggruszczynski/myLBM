#include "../headers/Writer.h"


void Writer::WritePassiveScalar(const vector<vector<shared_ptr<Node>>> &mesh, FILE* dataFile) const
{
	int x, y, z;
	fprintf(dataFile, "      <DataArray type=\"Float32\" Name=\"PassiveScalar\" NumberOfComponents=\"1\" format=\"ascii\">\n");
	for (z = 0; z < this->nz; z++)
	{
		for (y = 0; y < this->ny; y++)
		{
			for (x = 0; x < this->nx; x++)
			{
				fprintf(dataFile, "%.4e ", mesh[x][y]->T);
			//	fprintf(dataFile, "%.4e ", mesh[x][y]->T/ mesh[x][y]->rho);
			}
			fprintf(dataFile, "\n");
		}
	}
	fprintf(dataFile, "      </DataArray>\n");
}

void Writer::WriteDensity(const vector<vector<shared_ptr<Node>>> &mesh, FILE *dataFile) const
{
	int x, y, z;
	fprintf(dataFile, "      <DataArray type=\"Float32\" Name=\"Density\" NumberOfComponents=\"1\" format=\"ascii\">\n");
	for (z = 0; z < this->nz; z++)
	{
		for (y = 0; y < this->ny; y++)
		{
			for (x = 0; x < this->nx; x++)
			{
				fprintf(dataFile, "%.4e ", mesh[x][y]->rho);
				//cout << "mesh[" << x << "][" << y << "] rho ->" << mesh[x][y]->rho << endl;
				//fprintf(dataFile, "%.4e ", rho[x][y][z]);
			}
			fprintf(dataFile, "\n");
		}
	}
	fprintf(dataFile, "      </DataArray>\n");
}

void Writer::WriteNodeType(const vector<vector<shared_ptr<Node>>>& mesh, FILE* dataFile) const
{
	int x, y, z;

	fprintf(dataFile, "      <DataArray type=\"Float32\" Name=\"NodeType\" NumberOfComponents=\"1\" format=\"ascii\">\n");
	for (z = 0; z < this->nz; z++)
	{
		for (y = 0; y < this->ny; y++)
		{
			for (x = 0; x < this->nx; x++)
			{
				fprintf(dataFile, "%.4e ", (double)mesh[x][y]->nodeType);
				//cout << "mesh[" << x << "][" << y << "] nodeType ->" << (double)mesh[x][y]->nodeType << endl;
			}
			fprintf(dataFile, "\n");
		}
	}
	fprintf(dataFile, "      </DataArray>\n");
}

void Writer::WriteVelocity(const vector<vector<shared_ptr<Node>>> &mesh, FILE* dataFile) const
{
	int x, y, z;
	fprintf(dataFile, "      <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"2\" format=\"ascii\">\n");
	for (z = 0; z < this->nz; z++)
	{
		for (y = 0; y < this->ny; y++)
		{
			for (x = 0; x < this->nx; x++)
			{
				fprintf(dataFile, "%.4e ", mesh[x][y]->u[0]);
				fprintf(dataFile, "%.4e ", mesh[x][y]->u[1]);
				//fprintf(dataFile, "%d ", 0);
			}
			fprintf(dataFile, "\n");
		}
	}
	fprintf(dataFile, "      </DataArray>\n");
}

void Writer::WriteEddyViscosity(const vector<vector<shared_ptr<Node>>>& mesh, FILE* dataFile) const
{
	int x, y, z;

	fprintf(dataFile, "      <DataArray type=\"Float32\" Name=\"EddyViscosity\" NumberOfComponents=\"1\" format=\"ascii\">\n");
	for (z = 0; z < this->nz; z++)
	{
		for (y = 0; y < this->ny; y++)
		{
			for (x = 0; x < this->nx; x++)
			{
				fprintf(dataFile, "%.4e ", (double)mesh[x][y]->nuTurb);
				//cout << "mesh[" << x << "][" << y << "] nodeType ->" << (double)mesh[x][y]->nodeType << endl;
			}
			fprintf(dataFile, "\n");
		}
	}
	fprintf(dataFile, "      </DataArray>\n");

}

void Writer::WriteCrossSectionData(const vector<vector<shared_ptr<Node>>> &mesh, const int &time, const string directory_, const string filename_) const
{
	const char* directory = directory_.c_str();
	string nazwa = directory_ + "/" + filename_ + ".dat";
	ofstream myfile;
	myfile.open(nazwa, ofstream::app);

	/// time, nodes -> T
	myfile << time << "\t";
	int y = mesh[0].size() / 2;
	for (int x = 0; x < mesh.size(); ++x)
		myfile << mesh[x][y]->T << "\t";

	myfile << endl;
	myfile.close();

	cout << "Cross Section Data Saved at time_step: " << time << endl;
}

void Writer::writeVTK(const vector<vector<shared_ptr<Node>>> &mesh, const int &time,const string directory_, const string filename_)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(20000));
	//std::cout << "child thread id = " << std::this_thread::get_id() << std::endl;

	int dir;
	char dataFileName[255];
	FILE *dataFile;

	//------------updates-------------------
	//assume rectangular lattice ;p
	this->nx = mesh.size();                //lattice size x
	this->ny = mesh[0].size();             //lattice size y 
	this->nz = 2;

	const char* directory = directory_.c_str();
	const char* filename = filename_.c_str();
	//---------------------------------------


	/*if (!boost::filesystem::exists("myfile.txt"))
	{
		std::cout << "Can't find my file!" << std::endl;
	}*/

	dir = _mkdir(directory);
	if (dir == 0) printf("Error: Can't create output directory!\n");
	//sprintf(dataFileName, "%s/%s_%07d.vti", directory, filename, time);
	sprintf_s(dataFileName, "%s/%s_%07d.vti", directory, filename, time);
	dataFile = fopen(dataFileName, "w");
	//dataFile = fopen_s(&dataFile, dataFileName, "w");
	fprintf(dataFile, "<?xml version=\"1.0\"?>\n");
	fprintf(dataFile, "<!-- mojeLB -->\n");
	fprintf(dataFile, "<VTKFile type=\"ImageData\" version=\"0.1\" byte_order=\"LittleEndian\">\n");
	fprintf(dataFile, "  <ImageData WholeExtent=\"0 %d 0 %d 0 %d\" Origin=\"0 0 0\" Spacing=\"1 1 1\">\n", nx - 1, ny - 1, nz - 1);
	fprintf(dataFile, "  <Piece Extent=\"0 %d 0 %d 0 %d\">\n", nx - 1, ny - 1, nz - 1);

	//fprintf(dataFile, "  <ImageData WholeExtent=\"0 %d 0 %d\" Origin=\"0 0\" Spacing=\"1 1\">\n", nx - 1, ny - 1);
	//fprintf(dataFile, "  <Piece Extent=\"0 %d 0 %d\">\n", nx - 1, ny - 1);
	fprintf(dataFile, "    <PointData Scalars=\"scalars\">\n");

	WriteDensity(mesh, dataFile);
	WriteNodeType(mesh, dataFile);
	WriteVelocity(mesh, dataFile);
	WritePassiveScalar(mesh, dataFile);
	//WriteEddyViscosity(mesh, dataFile);


	fprintf(dataFile, "    </PointData>\n");

	fprintf(dataFile, "    <CellData>\n");
	fprintf(dataFile, "    </CellData>\n");
	fprintf(dataFile, "  </Piece>\n");
	fprintf(dataFile, "  </ImageData>\n");

	fprintf(dataFile, "</VTKFile>\n");
	fclose(dataFile);

	cout << "VTK Saved at time_step: " << time << endl;
}

void Writer::writePointData(const vector<vector<shared_ptr<Node>>> &mesh, const int &time, const int &x, const int &y,const string directory_, const string filename_) const
{

	//	cout << time << "\time\time\time" << mesh[x][y]->u[0] << "\time\time\time" << mesh[x][y]->u[1] << endl;

		//std::ofstream log("output/PointData.dat", std::ios_base::app | std::ios_base::out); //append mode
		//log << time << "\time\time\time" << mesh[x][y]->u[0] << "\time\time\time" << mesh[x][y]->u[1] << endl;
	const char* directory = directory_.c_str();
	string nazwa = directory_ + "/" + filename_ + ".dat";
	ofstream myfile;
	myfile.open(nazwa, ofstream::app);
	//myfile.open("output/PointData2.dat", ofstream::app);
	//myfile << "#Computed at" << __TIME__ << " " << __DATE__ << endl;
	// myfile << setiosflags(ios::fixed) << setprecision(2);  // fixed point << decimal part

	/// time, x, y, length
	myfile << time << "\t" << mesh[x][y]->u[0] << "\t" << mesh[x][y]->u[1] << "\t" << sqrt(mesh[x][y]->u[0] * mesh[x][y]->u[0] + mesh[x][y]->u[1] * mesh[x][y]->u[1]) << endl;
	myfile.close();
	cout << "Point Data Saved at time_step: " << time << endl;
}

void Writer::WriteCaseInfo(Case* case_, string directory_, string filename_) const
{
	const char* directory = directory_.c_str();
	string nazwa = directory_ + "/" + filename_ + ".txt";
	ofstream myfile;
	myfile.open(nazwa);

	myfile << " \t all info in Lattice Bolztmann units " << endl;
	myfile << "Mesh Size: \t" << " x: " << case_->meshGeom_.x << " y: " << case_->meshGeom_.y << endl;
	myfile << "BC: \t" << " uInlet: " << case_->bcValues_.uInlet << " uLid: " << case_->bcValues_.uLid << " nu: " << case_->bcValues_.nu << endl;

	myfile << "Obstacle: \t" << " x: " << case_->obstacle_.x << " y: " << case_->obstacle_.y << " r: " << case_->obstacle_.r << endl;
	myfile << "Passive Scalar Blobb: \t" << " x: " << case_->passive_scalar_blobb_.x << " y: " << case_->passive_scalar_blobb_.y << " r:" << case_->passive_scalar_blobb_.r << endl;
	myfile << "Passive Scalar Blobb: \t" << " K (thermal conductivity): " << case_->passive_scalar_blobb_.K << " Temp: " << case_->passive_scalar_blobb_.T << endl;

	myfile << "Timer: " << " totalTime: " << case_->timer_.totalTime << " timeToSaveVTK: " << case_->timer_.timeToSaveVTK << " timeToSavePointdata: " << case_->timer_.timeToSavePointData << endl;

	double omegaT = 1. / (2 * case_->passive_scalar_blobb_.K + 0.5); //Passive Scalar relaxation parameter
	double omegaNS = 1. / (3 * case_->bcValues_.nu + 0.5);      //NS relaxation parameter

	myfile << "Relaxation Parameters: \t" << "omegaNS: " << omegaNS << " omegaT: " << omegaT << endl;



	myfile.close();

}

void Writer::ClearDirectory(string folderPath_)
{
	const char* folderPath = folderPath_.c_str();
	fs::path myFolder(folderPath);
	fs::remove_all(myFolder);

	bool success = boost::filesystem::create_directories(myFolder);
	/*if (boost::filesystem::create_directories(myFolder)) {
		std::cout << "Success" << "\n";
	}*/

	//fs::path myFolder("foobar");
	//fs::remove_all("foobar");
	//fs::create_directory("foobar");
	//ofstream file("foobar/cheeze");
	//file << "tastes good!\n";
	//file.close();f
	//if (!fs::exists("foobar/cheeze"))
	//std::cout << "Something is rotten in foobar\n";
}


void Writer::writeVTK_old(int t, int nx, int ny, int nz, double ***rho, int write_rho, double ***pre, int write_pre, double ***ux, double ***uy, double ***uz, int write_vel, char *directory, char *filename)

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
		for (z = 0; z < nz; z++)
		{
			for (y = 0; y < ny; y++)
			{
				for (x = 0; x < nx; x++)
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
		for (z = 0; z < nz; z++)
		{
			for (y = 0; y < ny; y++)
			{
				for (x = 0; x < nx; x++)
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
		for (z = 0; z < nz; z++)
		{
			for (y = 0; y < ny; y++)
			{
				for (x = 0; x < nx; x++)
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
