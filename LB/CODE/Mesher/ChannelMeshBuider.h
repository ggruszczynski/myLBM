#pragma once

#include "../Nodes/PressureOutlet.h"
#include "../Nodes/VelocityInlet.h"
#include "../Nodes/Wall.h"

#include "MeshBuilder.h"

using namespace std;

class ChannelMeshBuilder : public MeshBuilder
{

public:
	explicit ChannelMeshBuilder(const string &caseName_) : MeshBuilder(caseName_) {};

	void SetTop()override;
	void SetBottom()override;
	void SetLeft()override;
	void SetRight()override;

	void SetObstacle() override;
	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override; // poiseulle profile
};

