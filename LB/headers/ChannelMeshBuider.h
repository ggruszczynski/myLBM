#pragma once



#include "PressureOutlet.h"
#include "VelocityInlet.h"
#include "Wall.h"
#include "ChannelCaseBuilder.h"
#include "MeshBuilder.h"

class ChannelMeshBuilder : public MeshBuilder
{
private:
	ChannelCaseBuilder channelCaseBuilder;

public:

	CaseBuilder* GetCaseBuilder()override { return &channelCaseBuilder; }

	void SetTop()override
	{
		for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom		
			mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());
	};

	void SetBottom()override
	{
		for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
			mesh[i][0] = std::move(std::make_shared<Wall>());
	};

	void SetLeft()override
	{
		for (unsigned i = 0; i < mesh[0].size(); ++i) // sides
			mesh[0][i] = std::move(std::make_shared<VelocityInlet>(case_->bcValues_.uInlet, 0));
	};

	void SetRight()override
	{
		for (unsigned i = 0; i < mesh[0].size(); ++i) 
			mesh[mesh.size() - 1][i] = std::move(std::make_shared<PressureOutlet>());
	};

	void SetObstacle() override;;
	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override;//poiseulle profile	
};

