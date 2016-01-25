#pragma once



#include "../Nodes/PressureOutlet.h"
#include "../Nodes/VelocityInlet.h"
#include "../Nodes/Wall.h"
#include "../Cases/ChannelCaseBuilder.h"
#include "../Mesher/MeshBuilder.h"
#include "../Nodes/PeriodicNode.h"
#include "../Nodes/MovingWall.h"

class WallForceValidatorMeshBuilder : public MeshBuilder
{
private:
	ChannelCaseBuilder channelCaseBuilder;

public:

	CaseBuilder* GetCaseBuilder()override { return &channelCaseBuilder; }

	void SetTop()override
	{
		for (unsigned i = 0; i < mesh.size(); ++i) {
			mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(case_->bcValues_.uLid, 0));
		//	mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());
		}
	};

	void SetBottom()override
	{
		for (unsigned i = 0; i < mesh.size(); ++i)
			mesh[i][0] = std::move(std::make_shared<Wall>());
	};

	void SetLeft()override
	{
		for (unsigned i = 1; i < mesh[0].size() - 1; ++i)
			mesh[0][i] = std::move(std::make_shared<PeriodicNode>());
	};

	void SetRight()override
	{
		for (unsigned i = 1; i < mesh[0].size() - 1; ++i)
			mesh[mesh.size() - 1][i] = std::move(std::make_shared<PeriodicNode>());

	};

	void SetObstacle() override {}; // no obstacles
	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override;
};