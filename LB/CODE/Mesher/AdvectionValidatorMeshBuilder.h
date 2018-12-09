#pragma once

#include "../Nodes/PressureOutlet.h"

#include "MeshBuilder.h"
#include "../Nodes/PeriodicNode.h"
#include "../Nodes/SymmetryNode.h"


using namespace std;

class AdvectionValidatorMeshBuilder : public MeshBuilder
{
private:

public:

	explicit AdvectionValidatorMeshBuilder(const string &caseName_) : MeshBuilder(caseName_) {};

	void SetTop()override;
	void SetBottom()override;
	void SetLeft()override;
	void SetRight()override;

	void SetObstacle() override {};
	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override;//poiseulle profile	
};
