#pragma once

#include<math.h>

#include "../Nodes/PressureOutlet.h"
#include "../Nodes/VelocityInlet.h"
#include "../Nodes/Wall.h"

#include "MeshBuilder.h"
#include "../Nodes/MovingWall.h"


using namespace std;

class LidMeshBuilder : public MeshBuilder
{
private:

public:
    explicit LidMeshBuilder(const string &caseName_);

	~LidMeshBuilder() = default;

	vector<double> GaussianDistribution( int domainLength, double mean, double Sig) const;

	void SetTop()override;;

	void SetBottom()override;;

	void SetLeft()override;
	void SetRight()override;
	void SetObstacle() override {}; //no obstacles

	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override{}; // at rest
};

