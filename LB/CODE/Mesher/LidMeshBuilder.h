#pragma once

#include<math.h>

#include "../Nodes/PressureOutlet.h"
#include "../Nodes/VelocityInlet.h"
#include "../Nodes/Wall.h"

#include "MeshBuilder.h"
#include "../Cases/LidCaseBuilder.h"
#include "../Nodes/MovingWall.h"



class LidMeshBuilder : public MeshBuilder
{
private:
	LidCaseBuilder caseBuilder;
	Case caseVal_;
	Case* casePtr_;
	shared_ptr<Case> caseSPtr;
public:
	virtual ~LidMeshBuilder() {} // TODO;  destructor hides a non virtual function from class

	void ReadCase(const string &caseName_ = "LidDrivenCavity.xml") override
	{
		auto  temp = xmlParser.ReadXMLCase(caseName_);
		caseVal_ = temp;
		caseSPtr = std::make_shared<Case>(temp);
		casePtr_ = &temp;
		//*case_2 = temp;
	}


	CaseBuilder* GetCaseBuilder()override { return &caseBuilder; }

	vector<double> GaussianDistribution( int domainLength, double mean, double Sig) const
	{
		vector<double> normalDistribution(domainLength,0);
		for (int x = 0; x < domainLength; ++x)
		{
			normalDistribution[x] = 1/(Sig*sqrt(2* M_PI));
			normalDistribution[x] *= exp(-(x - mean)*(x - mean)/(2*Sig*Sig));
		}
		return normalDistribution;
	}

	void SetTop()override
	{		
		
		
		//for (unsigned i = 0; i < mesh.size(); ++i) 	
		//	mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(case_->bcValues_.uLid, 0));

	//lets add some wall at the top and a Gaussian velocity distribution...
		double wallFactor = 0.1; // amount of wall at each side

		for (unsigned i = 0; i < mesh.size()*wallFactor; ++i)
			mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());

		int movingWallLength = mesh.size()*(1-2*wallFactor);
		double Sigma = 20;
		vector<double> uGaussian = GaussianDistribution(movingWallLength, movingWallLength / 2, Sigma);
		double uYScale = case_->bcValues_.uLid;

		int i2 = 0;
		for (unsigned i = mesh.size() *wallFactor; i < mesh.size() *(1 - wallFactor); ++i, ++i2) {
			//mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(case_->bcValues_.uLid, 0));
			mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(uYScale*uGaussian[i2], 0));
		}


		for (unsigned i = mesh.size() *(1-wallFactor) ; i < mesh.size(); ++i)
			mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());


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

	void SetObstacle() override //no obstacles
	{
		//int y;
		//for (unsigned x = mesh.size()/4. ; x < 2./4.* mesh.size(); ++x) {
		//	y = mesh[x].size() / 3.;
		//	mesh[x][y] = std::move(std::make_shared<Wall>());
		//}	
	}; 


	void SetPassiveScalarBlobb() override;
	void InitializeVelocity() override{}; // at rest
};

inline void LidMeshBuilder::SetPassiveScalarBlobb()
{
	auto blob = case_->passive_scalar_blobb_;

	//for (unsigned x = 0; x < mesh.size(); ++x) {
	//	for (unsigned y = 0; y < mesh[x].size(); ++y) {
	//		if ((x - blob.x)*(x - blob.x) + (y - blob.y)*(y - blob.y) <= blob.r*blob.r)
	//		{
	//			mesh[x][y]->T = blob.T;
	//			for (auto& Tin_ : mesh[x][y]->TIn)
	//				Tin_ = Tin_ * mesh[x][y]->T;
	//		}
	//	}
	//}

	///test - everywhere the same
	for (unsigned x = 0; x < mesh.size() ; ++x) // skip walls
	{
		for (unsigned y = 0; y < mesh[x].size() ; ++y) // skip walls
		{
			mesh[x][y]->T = blob.T;
			for (auto& Tin : mesh[x][y]->TIn)
				Tin = Tin * mesh[x][y]->T;
		}
	}
}