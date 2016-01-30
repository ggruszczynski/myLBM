#pragma once

#include "../Nodes/PressureOutlet.h"

#include "MeshBuilder.h"
#include "../Nodes/PeriodicNode.h"
#include "../Nodes/SymmetryNode.h"

class AdvectionValidatorMeshBuilder : public MeshBuilder
{
private:

public:

	AdvectionValidatorMeshBuilder(const string &caseName_) : MeshBuilder(caseName_) {};

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
