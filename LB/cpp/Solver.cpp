
#include "../headers/Solver.h"


void Solver::Collisions()
{
#pragma omp parallel for
	for (int x = 0; x < static_cast<int>(mesh.size()); ++x) {
		for (int y = 0; y < static_cast<int>(mesh[x].size()); ++y) {
			mesh[x][y]->ComputeRho();
			mesh[x][y]->ComputeU();
			mesh[x][y]->ComputefEq();

			//mesh[x][y]->CalcEddyViscosity(mycase->bcValues_.nu);
			omegaNSTurb = 1. / (3 * (mycase->bcValues_.nu + mesh[x][y]->nuTurb) + 0.5);
			mesh[x][y]->NodeCollisionFout(omegaNSTurb);

			//mesh[x][y]->NodeCollisionFout(omegaNS);

		//thermal stuff:
			mesh[x][y]->ComputeT();
			mesh[x][y]->ComputeTeq();
			mesh[x][y]->NodeCollisionTout(omegaT);
		}
	}
}


void Solver::Stream()
{
#pragma omp parallel for
	for (int x = 0; x < mesh.size(); ++x) {
		for (int y = 0; y < mesh[x].size(); ++y) {
			StreamToNeighbour(x, y);
		}
	}
}

void Solver::StreamToNeighbour(const int& x, const int& y)
{
	unsigned nextX, nextY;
	for (unsigned i = 0; i < d2q9Constants->e.size(); ++i)
	{
		nextX = x + static_cast<int>(d2q9Constants->e[i](0));
		nextY = y + static_cast<int>(d2q9Constants->e[i](1));

		if (nextX >= 0 && nextX < mesh.size() && nextY >= 0 && nextY < mesh[x].size())
			mesh[nextX][nextY]->fIn[i] = mesh[x][y]->fOut[i];
	}

	//thermal stuff:
	for (unsigned i = 0; i < d2q5Constants->e.size(); ++i) //Passive Scalar
	{
		nextX = x + static_cast<int>(d2q5Constants->e[i](0));
		nextY = y + static_cast<int>(d2q5Constants->e[i](1));

		if (nextX >= 0 && nextX < mesh.size() && nextY >= 0 && nextY < mesh[x].size())
			mesh[nextX][nextY]->TIn[i] = mesh[x][y]->TOut[i];
	}


	// E-->W brutal periodic BC: we know the direction of the fluid flow
	if (mesh[x][y]->nodeType == NodeType::PeriodicType && x == mesh.size()-1) 
	{
		// periodic boundary conditions for east moving particles at east/west ends
		mesh[0][y]->fIn[5] = mesh[x][y]->fOut[5];
		mesh[0][y]->fIn[1] = mesh[x][y]->fOut[1];
		mesh[0][y]->fIn[8] = mesh[x][y]->fOut[8];

		mesh[0][y]->TIn[1] = mesh[x][y]->TOut[1];

		// periodic boundary conditions for west moving particles at east/west ends
		mesh[0][y]->fIn[6] = mesh[x][y]->fOut[6];
		mesh[0][y]->fIn[3] = mesh[x][y]->fOut[3];
		mesh[0][y]->fIn[7] = mesh[x][y]->fOut[7];

		mesh[0][y]->TIn[3] = mesh[x][y]->TOut[3];
	}
}



void Solver::Run()
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::universal_time();
	string nowAsString = to_iso_string(now);

	const string fileNameVTK = "mojeLB";
	string outputDirectory = "output";

	writer->ClearDirectory(outputDirectory);
	writer->WriteCaseInfo(mycase, outputDirectory, "caseInfoData");
	//outputDirectory += "/" + nowAsString;

	unsigned t = 0;
	while (t < mycase->timer_.totalTime)
	{
		/*	if (t%50 == 0)
			cout << "time: " << t << endl;*/

		if (t % mycase->timer_.timeToSavePointData == 0)
		{
			writer->writePointData(mesh, t, mycase->meshGeom_.x / 2, mycase->meshGeom_.y / 2, outputDirectory, "PointData");
			writer->WriteCrossSectionData(mesh, t, outputDirectory, "CrossSectionData");
			//	cout << "Average Temp: " << this->GetAverageT() << endl;
		}


		if (t%mycase->timer_.timeToSaveVTK == 0)
		{
			try { this->IsDensityValid(); }
			catch (exception& e)
			{
				cout << "Solver exception: " << e.what() << endl;
				break;
			}
			vector< vector<shared_ptr <Node>> > tempMesh = std::move(this->CloneMesh()) ;
			std::thread writingThread(&Writer::writeVTK, writer, tempMesh, t, outputDirectory, fileNameVTK); 
			writingThread.detach(); 

			///old way
			//writer->writeVTK(mesh, t, outputDirectory, fileNameVTK);
		}

		this->Collisions();
		this->Stream();
		++t;
	}

	//std::vector<std::thread> threadList;
	//for (int i = 0; i < 10; i++)
	//{
	//	threadList.push_back(std::thread(WorkerThread()));
	//}

	//   std::for_each(threadList.begin(),threadList.end(), std::mem_fn(&std::thread::join));
	//   threadList.clear();
}

vector<vector<shared_ptr<Node>>> Solver::CloneMesh()
{
	vector< vector<shared_ptr <Node>> > tempMesh (this->mesh); // make a shallow copy

#pragma omp parallel for
	for (int x = 0; x < mesh.size(); ++x) {
		for (int y = 0; y < mesh[x].size(); ++y) {
			//tempMesh[x][y] = mesh[x][y]->CloneShrPtr(); // change objects // todo
			tempMesh[x][y] = std::move(mesh[x][y]->CloneShrPtr()); // change objects
		}
	}

	return tempMesh;
}

double Solver::GetAverageT()
{
	double Ttotal = 0;

	for (auto& inner : mesh) {
		for (auto& node : inner) {
			Ttotal += node->T;
		}
	}
	return Ttotal / mycase->meshGeom_.numberOfNodes;
}

double Solver::GetVarT()
{
	double VarT = 0;
	double Tavg = this->GetAverageT();

	for (auto& inner : mesh) {
		for (auto& node : inner) {
			VarT += (node->T - Tavg)*(node->T - Tavg);
		}
	}
	return VarT;
}


shared_ptr<Node> Solver::GetNode(const int& x, const int& y)
{
	return mesh[x][y];
}

void Solver::IsDensityValid()
{
	for (auto& inner : mesh) {
		for (auto& node : inner) {
			if (node->rho > 1000)
			{
				string oups = "to big rho = " + std::to_string(node->rho);
				throw std::exception(oups.c_str());
			}
		}
	}

}

void Solver::ReplaceNode(const int& x, const int& y, shared_ptr <Node> newNode)
{
	//*mesh[x][y] = newNode;
	mesh[x][y] = std::move(newNode); // TODO: move vs reset?
									   //mesh[x][y].reset(newNode);
}



//void Solver::ReplaceNode(const int& x, const int& y, Node newNode) 
//{
//	*mesh[x][y] = newNode;
//	*mesh[x][y] = std::move(newNode); // TODO: which one is better?
//	//mesh[x][y].reset(newNode);
//}


Solver::~Solver()
{
	delete mycase;
	delete d2q5Constants;
	delete d2q9Constants;
}

