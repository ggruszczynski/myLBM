#pragma once

#include "../Nodes/PressureOutlet.h"
#include "../Nodes/VelocityInlet.h"
#include "../Nodes/Wall.h"

#include "MeshBuilder.h"

using namespace std;

class DiffusionValidatorMeshBuilder : public MeshBuilder
{
public:
	DiffusionValidatorMeshBuilder(const string &caseName_) : MeshBuilder(caseName_) {};

	void SetTop()override;
	void SetBottom()override;
	void SetLeft()override;
	void SetRight()override;

	void SetObstacle() override {}; // no obstacles
	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override {};// at rest
};

