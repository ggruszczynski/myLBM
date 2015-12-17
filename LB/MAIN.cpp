//============================================================================
// Name        : LB.cpp
// Author      : GG
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "headers/Node.h"
#include "headers/Solver.h"
#include "headers/D2Q9Constants.h"

#include <iostream>
#include <memory>
using namespace std;

//#include <Eigen/Dense>
//using namespace Eigen;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	const int n_rows = 16;
	const int n_col = 8;

	vector<Wall*> walls;

	vector<Node*> nodes;
	vector< vector<Node*> >  mesh;

	std::vector<unique_ptr<Wall>> wallStuff;// (16);
	wallStuff.reserve(10);
	for (int i = 0; i < 10; ++i)
		wallStuff.emplace_back(new Wall);


	std::vector<unique_ptr<Node>> NodeStuff(16);
	vector< vector<unique_ptr<Node>>  >  meshStuff(8);

	//mesh.push_back(wallStuff);

	nodes.push_back(new Wall);
	//mesh.push_back(&walls);

	auto solver = new Solver(n_rows, n_col);


	Node node;// = new Node();



	solver->StreamToNeighbour(13, 5);
	solver->Update();
	//cout << "ee" <<node.d2q9Constants.cs2 << endl;//




    cout <<"-------------------------------------THE END---------------------------------\n"<<endl;
	system("PAUSE");
	return 0;
}
