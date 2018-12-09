
#include "DiffusionValidatorMeshBuilder.h"

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

void DiffusionValidatorMeshBuilder::SetTop() {
    for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
        mesh[i][mesh[i].size() - 1] = move(make_shared<Wall>());
}

void DiffusionValidatorMeshBuilder::SetLeft() {
    for (unsigned i = 0; i < mesh[0].size(); ++i) // sides
        mesh[0][i] = move(make_shared<Wall>());
}

void DiffusionValidatorMeshBuilder::SetRight() {
    for (unsigned i = 0; i < mesh[0].size(); ++i)
        mesh[mesh.size() - 1][i] = move(make_shared<Wall>());
}

void DiffusionValidatorMeshBuilder::SetBottom() {
    for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
        mesh[i][0] = move(make_shared<Wall>());
}
