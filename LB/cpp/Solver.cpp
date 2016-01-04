/*
 * Solver.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#include "../headers/Solver.h"

void Solver::Collisions()
{

#pragma omp parallel for
	for (int x = 0; x < mesh.size(); ++x) {
		for (int y = 0; y < mesh[x].size(); ++y) {
			mesh[x][y]->ComputeRho();
			mesh[x][y]->ComputeRho();
			mesh[x][y]->ComputeU();
			mesh[x][y]->ComputefEq();
			mesh[x][y]->GetEddyViscosity();

			mesh[x][y]->NodeCollisionFout(omegaNS);

		/// disable ... when not needed
			mesh[x][y]->ComputeT();
			mesh[x][y]->ComputeTeq();
			mesh[x][y]->NodeCollisionTout(omegaT);
		}
	}

	//for ( auto& inner : mesh) {
	//	for ( auto& node : inner) {
	//		node->ComputeRho();
	//		node->ComputeU();
	//		node->ComputefEq();
	//		node->NodeCollisionFout(omegaNS);

	//		node->ComputeT();
	//		node->ComputeTeq();
	//		node->NodeCollisionTout(omegaT);
	//	}
	//}

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

//template <typename T>
//void Solver::StreamToNeighbour(const int& x, const int& y, typename Singleton<T>::Singleton* ddqq_constants)

void Solver::StreamToNeighbour(const int& x, const int& y)
{
	unsigned nextX, nextY;
	for (unsigned i = 0; i < d2q9Constants->e.size(); ++i)
	{
		nextX = x + d2q9Constants->e[i](0);
		nextY = y + d2q9Constants->e[i](1);

		if (nextX >= 0 && nextX < mesh.size() && nextY >= 0 && nextY < mesh[x].size())
			mesh[nextX][nextY]->fIn[i] = mesh[x][y]->fOut[i];
	}

	/// disable ... when not needed
	for (unsigned i = 0; i < d2q5Constants->e.size(); ++i) //Passive Scalar
	{
		nextX = x + d2q5Constants->e[i](0);
		nextY = y + d2q5Constants->e[i](1);

		if (nextX >= 0 && nextX < mesh.size() && nextY >= 0 && nextY < mesh[x].size())
			mesh[nextX][nextY]->TIn[i] = mesh[x][y]->TOut[i];
	}

}



void Solver::Run()
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::universal_time();
	string nowAsString = to_iso_string(now);

	const string fileNameVTK = "mojeLB";
	string outputDirectory = "output";
	string fileNamePointData = "PointData";

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
			cout << "Point Data Saved at time_step: " << t << endl;
			writer->writePointData(mesh, t, mycase->meshGeom_.x / 2, mycase->meshGeom_.y / 2, outputDirectory, fileNamePointData);
		}


		if (t%mycase->timer_.timeToSaveVTK == 0)
		{
			cout << "VTK Saved at time_step: " << t << endl;

			try { writer->writeVTK(mesh, t, outputDirectory, fileNameVTK); }
			catch (exception& e)
			{
				cout << "Standard exception: " << e.what() << endl;
				break;
			}
		}
		this->Collisions();
		this->Stream();

		++t;
	}
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

//double Solver::GetEddyViscosity()
//{
//	MatrixXd localStressTensor(2, 2);
//
//	auto wtf = d2q9Constants->e[2];
//
//	for (auto& inner : mesh) {
//		for (auto& node : inner) {
//			
//			for (unsigned i = 0; i < d2q9Constants->e.size(); ++i) //each node
//			{
//
//
//				localStressTensor(0, 0) = d2q9Constants->e[i](0)* d2q9Constants->e[i](0) * (node->fIn[i] - node->feq[i]);
//
//			}
//
//		}
//	}
//
//}

shared_ptr<Node> Solver::GetNode(const int& x, const int& y)
{
	return mesh[x][y];
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

void Solver::InsertNode(const int& x, const int& y, Node& newNode)
{
	throw std::exception("not implemented");
}


Solver::~Solver()
{
	delete mycase;
	delete d2q5Constants;
	delete d2q9Constants;
}

