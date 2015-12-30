#pragma once

#include "CaseBuilder.h"
class CaseDirector
{
private:
	CaseBuilder* caseBuilder;

public:
	CaseDirector() { caseBuilder = nullptr; };

	void setBuilder(CaseBuilder *newBuilder)
	{
		caseBuilder = newBuilder;
	}

	Case* GetCase() const
	{ // order is important: first createNewCase -> SetBlockGeom -> ...
		caseBuilder->createNewCase();
		caseBuilder->SetBlockGeom();
		caseBuilder->SetTimer();
		caseBuilder->SetBCValues();
		caseBuilder->SetObstacle();
		caseBuilder->SetPassiveScalarBlobb();

		return caseBuilder->getCase();
	}

	//~CaseDirector() { delete caseBuilder; };
};

