#pragma once

#include "Case.h"
#include <memory>

class CaseBuilder
{
protected:
	//std::unique_ptr<Case> case_;
	Case* case_;
public:
	// 0 = abstract. This is a pure virtual function. This means, that subclasses have to implement this function, otherwise they are abstract, meaning you cannot create objects of that class.

	virtual void SetBlockGeom() = 0;
	virtual void SetTimer() = 0;
	virtual void SetBCValues() = 0;
	virtual void SetObstacle() = 0;
	virtual void SetPassiveScalarBlobb() = 0;

	Case* getCase() const
	{
		return case_;
		//return case_.get();
	}

	void createNewCase()
	{
		case_ = new Case();
		//case_ = std::make_unique<Case>();
	}

	CaseBuilder(){};
	virtual ~CaseBuilder(){};
};

