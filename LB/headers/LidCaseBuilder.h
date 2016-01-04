#pragma once

#include "CaseBuilder.h"

class LidCaseBuilder : public CaseBuilder
{
public:

	LidCaseBuilder() {};

	void SetBlockGeom()override
	{
		case_->meshGeom_.x = 200;
		case_->meshGeom_.y = 200;
		case_->meshGeom_.numberOfNodes = case_->meshGeom_.x * case_->meshGeom_.y;
	};

	void SetObstacle() override
	{
		case_->obstacle_.y = NULL; 
		case_->obstacle_.x = NULL; 
		case_->obstacle_.r = NULL; 
	};

	void SetPassiveScalarBlobb()override
	{
		case_->passive_scalar_blobb_.T = 1500;
		case_->passive_scalar_blobb_.K = 0.25;

		case_->passive_scalar_blobb_.x = case_->meshGeom_.x / 2;
		case_->passive_scalar_blobb_.y = case_->meshGeom_.y / 2;
		case_->passive_scalar_blobb_.r = 15;
	};

	void SetBCValues() override
	{
		case_->bcValues_.uLid = 0.5;
		case_->bcValues_.uInlet = NULL;
		case_->bcValues_.nu = 1./6.;

		// double  Re = 100;
		// bcValues_.nu = bcValues_.uInlet * 2 * obstacle_.r / bcValues_.Re;  // kinematic viscosity
		// bcValues_.nu = 1. / 6.;
	}

	void SetTimer() override
	{
		case_->timer_.totalTime = 10; // number of timeSteps
		case_->timer_.timeToSaveVTK = 1; // after timeSave amount of steps -> save
	};

	virtual ~LidCaseBuilder() {};
};

