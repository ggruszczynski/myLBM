#pragma once

#include "PressureOutlet.h"
#include "VelocityInlet.h"
#include "Wall.h"

#include "MeshBuilder.h"
#include "LidCaseBuilder.h"
#include "MovingWall.h"

class LidMeshBuilder : public MeshBuilder
{
private:
	LidCaseBuilder caseBuilder;

public:
	virtual ~LidMeshBuilder()  // TODO;  destructor hides a non virtual function from class
	{
	}

	CaseBuilder* GetCaseBuilder()override { return &caseBuilder; }

	void SetTop()override
	{
		for (unsigned i = 0; i < mesh.size(); ++i) 	
			mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(case_->bcValues_.uLid, 0));
	};

	void SetBottom()override
	{
		for (unsigned i = 0; i < mesh.size(); ++i) 
			mesh[i][0] = std::move(std::make_shared<Wall>());
	};

	void SetLeft()override
	{
		for (unsigned i = 0; i < mesh[0].size(); ++i) 
			mesh[0][i] = std::move(std::make_shared<Wall>());
	};

	void SetRight()override
	{
		for (unsigned i = 0; i < mesh[0].size(); ++i)
			mesh[mesh.size() - 1][i] = std::move(std::make_shared<Wall>());

	};

	void SetObstacle() override{}; //no obstacles
	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override{}; // at rest
};

inline void LidMeshBuilder::SetPassiveScalarBlobb()
{
	auto blob = case_->passive_scalar_blobb_;
	for (unsigned x = 0; x < mesh.size(); ++x) {
		for (unsigned y = 0; y < mesh[x].size(); ++y) {
			if ((x - blob.x)*(x - blob.x) + (y - blob.y)*(y - blob.y) <= blob.r*blob.r)
			{
				mesh[x][y]->T = blob.T;
				for (auto& Tin_ : mesh[x][y]->TIn)
					Tin_ = Tin_ * mesh[x][y]->T;
			}
		}
	}
}