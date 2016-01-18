#pragma once
#include "Node.h"
#include <memory>
#include "Case.h"
#include "CaseBuilder.h"


class MeshBuilder
{
protected:
	Case* case_;
	CaseBuilder* caseBuilder;
	Singleton<D2Q9Constants>*d2q9Constants;
	Singleton<D2Q5Constants>*d2q5Constants;

	vector<vector<shared_ptr<Node>>> mesh;
public:

	MeshBuilder()
	{
		d2q9Constants = Singleton<D2Q9Constants>::get_instance();
		d2q5Constants = Singleton<D2Q5Constants>::get_instance();
	}

	virtual void SetCase(Case *newCase)	{case_ = newCase;}

	virtual CaseBuilder* GetCaseBuilder() = 0; // const { return  caseBuilder; }

	vector<vector<shared_ptr<Node>>> GetMesh() const	{return mesh;}


	virtual void SetTop() = 0;
	virtual void SetBottom() = 0;
	virtual void SetLeft() = 0;
	virtual void SetRight() = 0;

	virtual void SetObstacle() = 0;
	virtual void SetPassiveScalarBlobb() = 0;

	virtual void InitializeVelocity() = 0;


	void ReserveMeshBlock();


	virtual ~MeshBuilder(){};
};

