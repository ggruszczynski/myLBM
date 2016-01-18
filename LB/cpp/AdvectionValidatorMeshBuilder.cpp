
#include "../stdafx.h"
#include "../headers/AdvectionValidatorMeshBuilder.h"



void AdvectionValidatorMeshBuilder::SetPassiveScalarBlobb()
{
	auto passiveScalarBlobb = case_->passive_scalar_blobb_;

	for (size_t x = mesh.size() * 1./8.; x < mesh.size() * 2. / 8.; ++x)
	{
		for (size_t y = 1; y < mesh[x].size() - 1; ++y) // skip walls
		{
			mesh[x][y]->T = passiveScalarBlobb.T;
			for (auto& Tin : mesh[x][y]->TIn)
				Tin = Tin * mesh[x][y]->T;
		}
	}

	for (size_t x = mesh.size() * 5. / 8. ; x < mesh.size() * 6. / 8.; ++x)
	{
		for (size_t y = 1; y < mesh[x].size() - 1; ++y) // skip walls
		{
			mesh[x][y]->T = passiveScalarBlobb.T;
			for (auto& Tin : mesh[x][y]->TIn)
				Tin = Tin * mesh[x][y]->T;
		}
	}

}

void AdvectionValidatorMeshBuilder::InitializeVelocity()
{
	Eigen::Matrix<double, 2, 1, Eigen::DontAlign> u;
	vector<double> newFIn(9, 0);
	double rho = 1;
	double R = (case_->meshGeom_.y / 2) - 1; // -2: subtract top/bottom wall thickness
	double uInProfile, eu, u2;// , yPhys;
	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) // from 1 (skip bottom wall)
		{

			//if(typeid(*mesh[x][y]) != typeid(Wall))
			if (mesh[x][y]->nodeType == FluidType || mesh[x][y]->nodeType == VelocityInletType || mesh[x][y]->nodeType == PeriodicType || mesh[x][y]->nodeType == SymmetryType )
			{
				//string s = typeid(*mesh[x][y]).name();

				//uInProfile = case_->bcValues_.uInlet *(2 * y* R - y*y) / (R*R); //poiseulle profile
				uInProfile = case_->bcValues_.uInlet; // uniform profile
				u << uInProfile, 0;
				u2 = u.dot(u);
				for (unsigned i = 0; i < newFIn.size(); ++i)
				{
					eu = u.dot(d2q9Constants->e[i]);
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
