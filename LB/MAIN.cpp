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


using namespace std;

//#include <Eigen/Dense>
//using namespace Eigen;

void myfun(int x)
{
	cout << x << endl;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	const unsigned n_rows = 16;
	const unsigned n_col = 8;



	std::vector<shared_ptr <Node>> wallStuff;// (16);
	wallStuff.reserve(10);
	for (unsigned i = 0; i < 10; ++i)
		wallStuff.emplace_back(new Wall);


	std::vector<shared_ptr <Node>> nodeStuff(5);
	for (unsigned i = 0; i < 16; ++i)
		nodeStuff.emplace_back(new Node);

	cout << nodeStuff.size();

	vector< vector<shared_ptr <Node>> >  meshStuff(8);

	meshStuff.emplace_back(wallStuff);
	meshStuff.emplace_back(nodeStuff);

	meshStuff[8].emplace_back(new Node);
	 // check push_back vs emplace_back

	//meshStuff[9].push_back()push_back(new Node);

	cout << "meshStuff" << typeid(meshStuff[8][2]).name() << endl;

	std::vector<std::unique_ptr<int>> stuff;
	stuff.reserve(10);
	for (int i = 0; i < 10; ++i)
		stuff.emplace_back(new int(i)); 

	for (auto &element : stuff)
		cout << *element << endl;

	//for_each(stuff.begin(), stuff.end(), [](int ss) { cout << ss; });

	//vector<Wall*> walls;

	//vector<Node*> nodes;
	//vector< vector<Node*> >  mesh666;
	//mesh666.push_back(wallStuff);

	//nodes.push_back(new Wall);
	//mesh666.push_back(&walls);

	auto solver = new Solver(n_rows, n_col);


	Node node;// = new Node();



	solver->StreamToNeighbour(13, 5);
	solver->Update();

	auto nodzik = solver->GetNode(2, 4);
	auto nodzik2 = solver->GetNode(3, 4);
	nodzik = std::move(nodzik2);
	//nodzik = new Wall; //ERROR
	nodzik.reset(new Wall); //OK

	std::shared_ptr<Node> p1 = std::make_shared<Wall>();
	shared_ptr<Node> sth(new Wall);
	solver->ReplaceNode(2, 4, std::make_shared<Wall>());

	//std::shared_ptr<int> foo;
	//std::shared_ptr<int> bar(new int(10));
	//foo = bar;                          // copy
	//bar = std::make_shared<int>(20);   // move


	//cout << "mesh " << typeid(solver->GetNode(2,4)).name() << endl;
	//cout << "ee" <<node.d2q9Constants.cs2 << endl;//


    cout <<"-------------------------------------THE END---------------------------------\n"<<endl;
	system("PAUSE");
	return 0;
}
