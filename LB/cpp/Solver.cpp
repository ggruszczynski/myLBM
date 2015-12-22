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

			node->NodeCollision(omega);
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

void Solver::StreamToNeighbour(const int& x, const int& y)
{
	int nextX, nextY;
	for (unsigned i = 0; i < d2q9Constants->e.size(); ++i)
	{
		nextX = x + d2q9Constants->e[i](0); 
		nextY = y + d2q9Constants->e[i](1);

		if (nextX >= 0  && nextX < mesh.size() && nextY >= 0 && nextY < mesh[x].size() ) 
			mesh[nextX][nextY]->fIn[i] = mesh[x][y]->fOut[i];

		//cout << d2q9Constants->e[i](0) << endl;
	}
}



void Solver::Run()
{
	//mesh[5][5]-> u[0] = 4;
	//mesh[5][5]-> u[1] = 6;

	//cout << mesh[5][5]->u[0] << endl;
	//cout << mesh[6][5]->u[0] << endl;

	unsigned t = 0;
	while (t < totalTime)
	{
	/*	if (t%50 == 0)
		cout << "time: " << t << endl;*/
		if (t%timeSave == 0)
		{
			cout << "Saved at time: " << t << endl;
			writer->writeVTK(mesh, t, "output", "mojeLB");
		}
		this->Collisions();
		this->Stream();

		++t;
	}
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


void Solver::MakeLidDrivenCavityMesh(const unsigned& set_x, const unsigned& set_y)
{
	 // (set_y); how to add in place instead of after the last element... why pushback doesnt work?

	mesh.reserve(set_x);
	for (unsigned i = 0; i < set_x; ++i)
	{
			vector< shared_ptr <Node>>vec_pion;
			vec_pion.reserve(set_y);
			for (unsigned j = 0; j < set_y; ++j) 
				vec_pion.emplace_back(new Node);
			
		mesh.emplace_back(vec_pion);
	}

	for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
	{
		mesh[i][0] = std::move(std::make_shared<Wall>());
		mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(uLid,0));
	}

	for (unsigned i = 0; i < mesh[0].size(); ++i) // sides
	{
		mesh[0][i] = std::move(std::make_shared<Wall>());
		mesh[mesh.size() - 1][i] = std::move(std::make_shared<Wall>());
	}
}

void Solver::MakeChannelMesh(const unsigned& set_x, const unsigned& set_y)
{


	mesh.reserve(set_x);
	for (unsigned i = 0; i < set_x; ++i) 
	{
			vector< shared_ptr <Node>>vec_pion;
			vec_pion.reserve(set_y);
			for (unsigned j = 0; j < set_y; ++j)
			{
				vec_pion.emplace_back(new Node);
			}
		mesh.emplace_back(vec_pion);
	}

	for (unsigned i = 0; i < mesh[0].size(); ++i) // sides
	{
		mesh[0][i] = std::move(std::make_shared<VelocityInlet>(uInlet,0));
		mesh[mesh.size() - 1][i] = std::move(std::make_shared<PressureOutlet>());
	}

	for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
	{
		mesh[i][0] = std::move(std::make_shared<Wall>());
		mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());
	}

	//obstacle
	unsigned height = (unsigned)mesh[0].size() / 4;
	unsigned fromInlet = (unsigned)mesh.size() / 4;
	for (unsigned i = 0; i < height; ++i) // sides
	{
		mesh[fromInlet][i] = std::move(std::make_shared<Wall>());
	}

}

void Solver::MakeLidDrivenCavityMesh_old(const unsigned& set_x, const unsigned& set_y) //obsolete
{
	vector< shared_ptr <Node>>vec_pion;
	vector< shared_ptr <Node>> bottomWall; // (set_y); how to add in place instead of after the last element... why pushback doesnt work?
	vector< shared_ptr <Node>> lid;
	vec_pion.reserve(set_y);
	for (unsigned i = 0; i < set_y; ++i) {
		vec_pion.emplace_back(new Node);
		bottomWall.emplace_back(new Wall);
		lid.emplace_back(new MovingWall(uLid, 0));
	}

	// TODO push_back vs emplace_back
	//shared_ptr <Wall> ptr(new WallType); OK
	//bottomWall.push_back(ptr); OK
	//bottomWall.push_back(new Wall); ERROR

	mesh.reserve(set_x);
	mesh.emplace_back(bottomWall);
	for (unsigned i = 0; i < set_x - 2; ++i)
		mesh.emplace_back(vec_pion);

	//mesh.push_back(bottomWall); //OK
	//mesh.emplace_back(bottomWall); //OK
	mesh.push_back(lid); //OK

						 // transpozycje
						 //vector<vector<double>> outtrans(out[0].size(),	vector<double>(out.size()));
						 //for (size_t i = 0; i < out.size(); ++i)
						 //	for (size_t j = 0; j < out[0].size(); ++j)
						 //		outtrans[j][i] = out[i][j];


	for (unsigned i = 1; i < mesh.size() - 1; ++i) // TODO what about corners? lid ws wall? 
	{
		mesh[i][0] = std::move(std::make_shared<Wall>());
		mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());
	}


	//vector<Node> mojvec(set_y); 
	//mesh666.push_back(mojvec);
	////vector< vector<int> > A;
	////std::vector<std::vector<int>> A(dimension, std::vector<int>(dimension));
}


Solver::~Solver() {}

