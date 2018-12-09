#include "WallForceValidatorMeshBuilder.h"

void WallForceValidatorMeshBuilder::SetPassiveScalarBlobb()
{
	auto blob = case_->passive_scalar_blobb_;

	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) {
			if ((x - blob.x)*(x - blob.x) + (y - blob.y)*(y - blob.y) <= blob.r*blob.r)
			{
				mesh[x][y]->T = blob.T;
				for (auto& Tin_ : mesh[x][y]->TIn)
					Tin_ = Tin_ * mesh[x][y]->T;
			}
		}
	}

	///test - everywhere the same
	//for (unsigned x = 0; x < mesh.size(); ++x) // skip walls
	//{
	//	for (unsigned y = 0; y < mesh[x].size(); ++y) // skip walls
	//	{
	//		mesh[x][y]->T = blob.T;
	//		for (auto& Tin : mesh[x][y]->TIn)
	//			Tin = Tin * mesh[x][y]->T;
	//	}
	//}
}

void WallForceValidatorMeshBuilder::InitializeVelocity()
{
	//Eigen::Matrix<double, 2, 1, Eigen::DontAlign> u;
	//vector<double> newFIn(9, 0);
	//double rho = 1;
	//double R = (case_->meshGeom_.y / 2) - 1; // -2: subtract top/bottom wall thickness
	//double uInProfile, eu, u2;// , yPhys;
	//for (unsigned x = 0; x < mesh.size(); ++x) {
	//	for (unsigned y = 0; y < mesh[x].size(); ++y) // from 1 (skip bottom wall)
	//	{

	//		//if(typeid(*mesh[x][y]) != typeid(Wall))
	//		if (mesh[x][y]->nodeType == FluidType || mesh[x][y]->nodeType == VelocityInletType || mesh[x][y]->nodeType == PeriodicType || mesh[x][y]->nodeType == SymmetryType)
	//		{
	//			//string s = typeid(*mesh[x][y]).name();

	//			//uInProfile = case_->bcValues_.uInlet *(2 * y* R - y*y) / (R*R); //poiseulle profile
	//			uInProfile = case_->bcValues_.uInlet; // uniform profile
	//			u << uInProfile, 0;
	//			u2 = u.dot(u);
	//			for (unsigned i = 0; i < newFIn.size(); ++i)
	//			{
	//				eu = u.dot(d2q9Constants->ee[i]);
	//				newFIn[i] = 1 + 3 * eu;
	//				newFIn[i] += 4.5 * eu*eu;
	//				newFIn[i] -= 1.5 * u2;
	//				newFIn[i] *= rho * d2q9Constants->vw[i];
	//			}

	//			mesh[x][y]->SetU(uInProfile, 0);
	//			mesh[x][y]->SetFIn(newFIn);
	//		}
	//	}
	//}
}

void WallForceValidatorMeshBuilder::SetTop() {
	for (unsigned i = 0; i < mesh.size(); ++i) {
		mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(case_->bcValues_.uLid, 0));
	}
}

void WallForceValidatorMeshBuilder::SetBottom() {
	for (unsigned i = 0; i < mesh.size(); ++i)
		mesh[i][0] = std::move(std::make_shared<Wall>());
}

void WallForceValidatorMeshBuilder::SetLeft() {
	for (unsigned i = 1; i < mesh[0].size() - 1; ++i)
		mesh[0][i] = std::move(std::make_shared<PeriodicNode>());
}

void WallForceValidatorMeshBuilder::SetRight() {
	for (unsigned i = 1; i < mesh[0].size() - 1; ++i)
		mesh[mesh.size() - 1][i] = std::move(std::make_shared<PeriodicNode>());

}
