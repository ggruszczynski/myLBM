#pragma once

#include "PressureOutlet.h"
#include "ChannelCaseBuilder.h"
#include "MeshBuilder.h"
#include "PeriodicNode.h"
#include "SymmetryNode.h"

class AdvectionValidatorMeshBuilder : public MeshBuilder
{
private:
	ChannelCaseBuilder channelCaseBuilder;

public:

	CaseBuilder* GetCaseBuilder()override { return &channelCaseBuilder; }

	void SetTop()override
	{
		for (unsigned i = 0; i < mesh.size(); ++i) 	
			mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<SymmetryNode>());
			//mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());
	};

	void SetBottom()override
	{
		for (unsigned i = 0; i < mesh.size(); ++i) 
			mesh[i][0] = std::move(std::make_shared<SymmetryNode>());
			//mesh[i][0] = std::move(std::make_shared<Wall>());
	};

	void SetLeft()override
	{
		for (unsigned i = 1; i < mesh[0].size() - 1 ; ++i) 
			mesh[0][i] = std::move(std::make_shared<PeriodicNode>());		
	};

	void SetRight()override
	{
		for (unsigned i = 1; i < mesh[0].size() - 1 ; ++i)
			mesh[mesh.size() - 1][i] = std::move(std::make_shared<PeriodicNode>());

	};

	void SetObstacle() override {};
	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override;//poiseulle profile	
};
