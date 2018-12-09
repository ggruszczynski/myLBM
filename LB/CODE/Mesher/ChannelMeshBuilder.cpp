
#include "ChannelMeshBuider.h"

void ChannelMeshBuilder::SetObstacle()
{
	auto obstacle = case_->obstacle_;

	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) {
			if ((x - obstacle.x)*(x - obstacle.x) + (y - obstacle.y)*(y - obstacle.y) <= obstacle.r*obstacle.r)
				mesh[x][y] = std::move(std::make_shared<Wall>());
		}
	}
}

void ChannelMeshBuilder::SetPassiveScalarBlobb()
{
	auto passiveScalarBlobb = case_->passive_scalar_blobb_;

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
}

void ChannelMeshBuilder::InitializeVelocity()
{
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> u;
	double newFIn[9];
	double rho = 1;
	double R = (case_->meshGeom_.y / 2) - 1; // -2: subtract top/bottom wall thickness
	double uInProfile, eu, u2;// , yPhys;
	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size()  - 1 ; ++y) // from 1 (skip bottom wall)
		{

			//if(typeid(*mesh[x][y]) != typeid(Wall))
			if (mesh[x][y]->nodeType == FluidType || mesh[x][y]->nodeType == VelocityInletType)
			{
				//string s = typeid(*mesh[x][y]).name();

				uInProfile = case_->bcValues_.uInlet *(2 * y* R - y*y) / (R*R); //poiseulle profile
																				//uInProfile = bcValues_.uInlet; // uniform profile
				u << uInProfile, 0;
				u2 = u.dot(u);
				for (unsigned i = 0; i < sizeof(newFIn)/ sizeof(double); ++i)
				{
					eu = u.dot(d2q9Constants->ee[i]);
					newFIn[i] = 1 + 3 * eu;
					newFIn[i] += 4.5 * eu*eu;
					newFIn[i] -= 1.5 * u2;
					newFIn[i] *= rho * d2q9Constants->w[i];
				}

				mesh[x][y]->SetU(uInProfile, 0);
				mesh[x][y]->SetFIn(newFIn);
			}
		}
	}
}

void ChannelMeshBuilder::SetTop() {
    for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
        mesh[i][mesh[i].size() - 1] = move(make_shared<Wall>());
}

void ChannelMeshBuilder::SetBottom() {
    for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
        mesh[i][0] = move(make_shared<Wall>());
}

void ChannelMeshBuilder::SetLeft() {
    for (unsigned i = 0; i < mesh[0].size(); ++i) // sides
        mesh[0][i] = move(make_shared<VelocityInlet>(0, 0)); // std::move(std::make_shared<VelocityInlet>(case_->bcValues_.uInlet, 0));
}

void ChannelMeshBuilder::SetRight() {
    for (unsigned i = 0; i < mesh[0].size(); ++i)
        mesh[mesh.size() - 1][i] = move(make_shared<PressureOutlet>());
}
