#pragma once

#include "../Nodes/PressureOutlet.h"
#include "../Nodes/VelocityInlet.h"
#include "../Nodes/Wall.h"

#include "../Mesher/MeshBuilder.h"
#include "../Nodes/PeriodicNode.h"
#include "../Nodes/MovingWall.h"

class WallForceValidatorMeshBuilder : public MeshBuilder
{
private:

public:
	WallForceValidatorMeshBuilder(const string &caseName_) : MeshBuilder(caseName_) {};

	void SetTop()override;
	void SetBottom()override;
	void SetLeft()override;
	void SetRight()override;

	void SetObstacle() override {}; // no obstacles
	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override;
};