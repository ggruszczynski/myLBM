#include "../headers/Mesher.h"
#include "../headers/MovingWall.h"


vector<vector<shared_ptr<Node>>> Mesher::MakeChannelMesh(const unsigned& set_x, const unsigned& set_y, const Case & somecase)
{
	vector<vector<shared_ptr<Node>>> mesh;

	auto bcValues = somecase.bcValues;
	auto obstacle = somecase.obstacle_;
	auto passiveScalarBlobb = somecase.passive_scalar_blobb_;


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
			mesh[0][i] = std::move(std::make_shared<VelocityInlet>(bcValues.uInlet, 0));
			mesh[mesh.size() - 1][i] = std::move(std::make_shared<PressureOutlet>());
		}

		for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
		{
			mesh[i][0] = std::move(std::make_shared<Wall>());
			mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());
		}

		//--------------------obstacle-------------------------
		for (unsigned x = 0; x < mesh.size(); ++x) {
			for (unsigned y = 0; y < mesh[x].size(); ++y) {
				if ((x - obstacle.x)*(x - obstacle.x) + (y - obstacle.y)*(y - obstacle.y) <= obstacle.r*obstacle.r)
					mesh[x][y] = std::move(std::make_shared<Wall>());
			}
		}

		//---------------------initialize----------------------
		double eu;
		vector<double> newFIn(9, 0);
		double rho = 1;
		Eigen::Matrix<double, 2, 1, Eigen::DontAlign> u;
		u << bcValues.uInlet, 0;
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
					mesh[x][y]->SetU(bcValues.uInlet, 0);
					mesh[x][y]->SetFIn(newFIn);
				}
			}
		}



	 //---------------------initialize Temp----------------------
		for (unsigned x = 0; x < mesh.size(); ++x) {
			for (unsigned y = 0; y < mesh[x].size(); ++y) {
				if ((x - passiveScalarBlobb.x)*(x - passiveScalarBlobb.x) + (y - passiveScalarBlobb.y)*(y - passiveScalarBlobb.y) <= passiveScalarBlobb.r*passiveScalarBlobb.r)
				{
					mesh[x][y]->T = passiveScalarBlobb.T;
					for (auto& Tin : mesh[x][y]->TIn)
						Tin = Tin * mesh[x][y]->T;
				}
			}
		}
	
return mesh;
}



vector<vector<shared_ptr<Node>>> Mesher::MakeLidDrivenCavityMesh(const unsigned& set_x, const unsigned& set_y, const Case & somecase)
{
	vector<vector<shared_ptr<Node>>> mesh;

	auto bcValues = somecase.bcValues;
	auto obstacle = somecase.obstacle_;
	auto passiveScalarBlobb = somecase.passive_scalar_blobb_;

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
		mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(bcValues.uLid,0));
		mesh[i][0] = std::move(std::make_shared<Wall>());
	}

	for (unsigned i = 0; i < mesh[0].size(); ++i) // sides
	{
		mesh[0][i] = std::move(std::make_shared<Wall>());
		mesh[mesh.size() - 1][i] = std::move(std::make_shared<Wall>());
	}

	//---------------------initialize Temp----------------------
	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) {
			if ((x - passiveScalarBlobb.x)*(x - passiveScalarBlobb.x) + (y - passiveScalarBlobb.y)*(y - passiveScalarBlobb.y) <= passiveScalarBlobb.r*passiveScalarBlobb.r)
			{
				mesh[x][y]->T = passiveScalarBlobb.T;
				for (auto& Tin : mesh[x][y]->TIn)
					Tin = Tin * mesh[x][y]->T;
			}
		}
	}

	return mesh;
}