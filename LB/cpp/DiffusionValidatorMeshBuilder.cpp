
#include "../stdafx.h"
#include "../headers/DiffusionValidatorMeshBuilder.h"


void DiffusionValidatorMeshBuilder::SetPassiveScalarBlobb()
{
	auto passiveScalarBlobb = case_->passive_scalar_blobb_;

	for (unsigned x = mesh.size() / 2; x < mesh.size() - 1; ++x) // skip walls
	{
		for (unsigned y = 1; y < mesh[x].size() -1; ++y) // skip walls
		{
				mesh[x][y]->T = passiveScalarBlobb.T;
				for (auto& Tin : mesh[x][y]->TIn)
					Tin = Tin * mesh[x][y]->T;
		}
	}
}
