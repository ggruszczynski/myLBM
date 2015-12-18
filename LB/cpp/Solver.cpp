/*
 * Solver.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#include "../headers/Solver.h"

void Solver::NaiveCollision()
{

	for ( auto& inner : mesh) {
		for ( auto& node : inner) {
			node->ComputeRho();
			node->ComputeU();
			node->ComputefEq();
			//ComputeNodeProperties(node);
			node->Collision();
			//for (int i = 0; i < node.fOut.size(); ++i)
			//{
			//	node.fOut[i] = (1. - omega)* node.fIn[i] + omega* node.fIn[i];
			//}
			//for_each(item.fOut.begin(), item.fOut.end(), )

		}
	}

}

void Solver::StreamToNeighbour(const int& x, const int& y)
{
	unsigned nextX, nextY;
	for (unsigned i = 0; i < d2q9Constants->e.size(); ++i)
	{
		nextX = x + d2q9Constants->e[i](0); 
		nextY = y + d2q9Constants->e[i](1);

		if (nextX >= 0  && nextX < mesh.size() && nextY >= 0 && nextY < mesh[x].size() ) 
			mesh[nextX][nextY]->fIn[i] = mesh[x][y]->fOut[i];

		//cout << d2q9Constants->e[i](0) << endl;
	}
}

void Solver::Update()
{ 
	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) {
			StreamToNeighbour(x, y);
		}
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

void Solver::MakeLidDrivenCavityMesh(const unsigned& set_n_rows, const unsigned& set_n_cols)
{
	vector< shared_ptr <Node>> bottomWall; // (set_n_cols); how to add in place instead of after the last element... why pushback doesnt work?
	vector< shared_ptr <Node>> lid;
	vcol.reserve(set_n_cols);
	for (unsigned i = 0; i < set_n_cols; ++i) {
		vcol.emplace_back(new Node);
		bottomWall.emplace_back(new Wall);
		lid.emplace_back(new MovingWall);
	}

	// TODO push_back vs emplace_back
	//shared_ptr <Wall> ptr(new Wall); OK
	//bottomWall.push_back(ptr); OK
	//bottomWall.push_back(new Wall); ERROR

	mesh.reserve(set_n_rows);
	mesh.emplace_back(bottomWall);
	for (unsigned i = 0; i < set_n_rows - 2; ++i)
		mesh.emplace_back(vcol);

	//mesh.push_back(bottomWall); //OK
	//mesh.emplace_back(bottomWall); //OK
	mesh.push_back(lid); //OK

	for (unsigned i = 1; i < mesh.size() - 1; ++i) // what about corners? lid ws wall? 
	{
		mesh[i][0] = std::move(std::make_shared<Wall>());
		mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());
	}


	//vector<Node> mojvec(set_n_cols); 
	//mesh666.push_back(mojvec);
	////vector< vector<int> > A;
	////std::vector<std::vector<int>> A(dimension, std::vector<int>(dimension));
}

//Solver::Solver() {
//	// TODO Auto-generated constructor stub
//
//}

Solver::~Solver() {
	// TODO Auto-generated destructor stub
}

