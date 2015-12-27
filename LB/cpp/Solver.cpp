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

			node->NodeCollisionFout(omega);
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

	const string fileName = "mojeLB";
	string outputDirectory = "output";
	writer->ClearDirectory(outputDirectory);
	//outputDirectory += "/" + nowAsString;

	unsigned t = 0;
	while (t < totalTime)
	{
	/*	if (t%50 == 0)
		cout << "time: " << t << endl;*/
		if (t%timeSave == 0)
		{
			cout << "Saved at time: " << t << endl;
			writer->writeVTK(mesh, t, outputDirectory, fileName);
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
		{
			vec_pion.emplace_back(new Node);
		}
		mesh.emplace_back(vec_pion);
	}


	for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
	{
		mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(uLid,0));
		mesh[i][0] = std::move(std::make_shared<Wall>());
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

	//--------------------obstacle-------------------------
	//unsigned height = (unsigned)mesh[0].size() / 4;
	//unsigned fromInlet = (unsigned)mesh.size() / 4;
	//for (unsigned i = 0; i < height; ++i) // sides
	//{
	//	mesh[fromInlet][i] = std::move(std::make_shared<Wall>());
	//}


	unsigned obst_x = set_x / 5 + 1;   // position of the cylinder; (exact
	unsigned	obst_y = set_y / 2 + 3;   // y - symmetry is avoided)
	unsigned obst_r = set_y / 10 + 1;  //radius of the cylinder

	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) {
			if ((x - obst_x)*(x - obst_x) + (y - obst_y)*(y - obst_y) <= obst_r*obst_r)
				mesh[x][y] = std::move(std::make_shared<Wall>());
		}
	}

	//---------------------initialize----------------------
	double eu; 
	vector<double> newFIn(9,0);
	double rho = 1;
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> u;
	u << uInlet, 0;
	double u2 = u.dot(u);
	for (unsigned i = 0; i < newFIn.size(); ++i)
	{
		eu = u.dot(d2q9Constants->e[i]);
		newFIn[i] = 1 + 3 * eu;
		newFIn[i] += 0.5 * eu*eu;
		newFIn[i] -= 1.5 * u2;
		newFIn[i] *= rho * d2q9Constants->w[i];

		//eu = u.dot(d2q9Constants->e[i]);
		//newFIn[i] = 1 + 3 * eu / c2;
		//newFIn[i] += 4.5 * eu*eu / c4;
		//newFIn[i] -= 1.5 * u2 / c2;
		//newFIn[i] *= rho * d2q9Constants->w[i];
	}

	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) {
			if (mesh[x][y]->nodeType == FluidType)
			{			
				mesh[x][y]->SetU(uInlet, 0);
				mesh[x][y]->SetFIn(newFIn);
			}
		}
	}

	double nu = uInlet * 2*obst_r / Re;  // kinematic viscosity
	omega = 1 / (3 * nu + 0.5);      // relaxation parameter


	 //---------------------initialize Temp----------------------

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

