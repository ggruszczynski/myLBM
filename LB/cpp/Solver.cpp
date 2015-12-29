/*
 * Solver.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#include "../headers/Solver.h"

void Solver::Collisions()
{
	for ( auto& inner : mesh) {
		for ( auto& node : inner) {
			node->ComputeRho();
			node->ComputeU();
			node->ComputefEq();
			node->NodeCollisionFout(omegaNS);

			node->ComputeT();
			node->ComputeTeq();
			node->NodeCollisionTout(omegaT);
		}
	}

}


void Solver::Stream()
{
	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) {
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

		//cout << d2q9Constants->e[i](0) << endl;
	}


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
	//outputDirectory += "/" + nowAsString;

	unsigned t = 0;
	while (t < mycase ->timer_.totalTime)
	{
	/*	if (t%50 == 0)
		cout << "time: " << t << endl;*/
		writer->writePointData(mesh, t, mycase ->meshGeom_.x/2, mycase -> meshGeom_.y/2, outputDirectory, fileNamePointData);

		if (t%mycase->timer_.timeToSave == 0)
		{
			cout << "Saved at time_step: " << t << endl;
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
			//node->ComputeT();
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

void Solver::ReplaceNode(const int& x, const int& y, shared_ptr <Node> newNode)
{
	//*mesh[x][y] = newNode;
	mesh[x][y] = std::move(newNode); // TODO move vs reset?
									   //mesh[x][y].reset(newNode);
}


// TODO would it crash when newNode goes out of the skope?

//void Solver::ReplaceNode(const int& x, const int& y, Node newNode) 
//{
//	*mesh[x][y] = newNode;
//	*mesh[x][y] = std::move(newNode); // TODO which one is better?
//	//mesh[x][y].reset(newNode);
//}

void Solver::InsertNode(const int& x, const int& y, Node& newNode)
{
	throw std::exception("not implemented");
}




//void Solver::MakeLidDrivenCavityMesh_old(const unsigned& set_x, const unsigned& set_y) //obsolete
//{
//	vector< shared_ptr <Node>>vec_pion;
//	vector< shared_ptr <Node>> bottomWall; // (set_y); how to add in place instead of after the last element... why pushback doesnt work?
//	vector< shared_ptr <Node>> lid;
//	vec_pion.reserve(set_y);
//	for (unsigned i = 0; i < set_y; ++i) {
//		vec_pion.emplace_back(new Node);
//		bottomWall.emplace_back(new Wall);
//		lid.emplace_back(new MovingWall(uLid, 0));
//	}
//
//	// TODO push_back vs emplace_back
//	//shared_ptr <Wall> ptr(new WallType); OK
//	//bottomWall.push_back(ptr); OK
//	//bottomWall.push_back(new Wall); ERROR
//
//	mesh.reserve(set_x);
//	mesh.emplace_back(bottomWall);
//	for (unsigned i = 0; i < set_x - 2; ++i)
//		mesh.emplace_back(vec_pion);
//
//	//mesh.push_back(bottomWall); //OK
//	//mesh.emplace_back(bottomWall); //OK
//	mesh.push_back(lid); //OK
//
//						 // transpozycje
//						 //vector<vector<double>> outtrans(out[0].size(),	vector<double>(out.size()));
//						 //for (size_t i = 0; i < out.size(); ++i)
//						 //	for (size_t j = 0; j < out[0].size(); ++j)
//						 //		outtrans[j][i] = out[i][j];
//
//
//	for (unsigned i = 1; i < mesh.size() - 1; ++i) // TODO what about corners? lid ws wall? 
//	{
//		mesh[i][0] = std::move(std::make_shared<Wall>());
//		mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());
//	}
//
//
//	//vector<Node> mojvec(set_y); 
//	//mesh666.push_back(mojvec);
//	////vector< vector<int> > A;
//	////std::vector<std::vector<int>> A(dimension, std::vector<int>(dimension));
//}
//

Solver::~Solver()
{
	delete mycase;
	delete d2q5Constants;
	delete d2q9Constants;
}

