#pragma once
#include "../Nodes/Node.h"
#include <memory>
#include "../Cases/Case.h"

#include "../IO/XMLParser.h"


class MeshBuilder
{
protected:
	D2Q9Constants* d2q9Constants;
	D2Q5Constants* d2q5Constants;

	shared_ptr<Case> case_;
	vector<vector<shared_ptr<Node>>> mesh;

	void ReadCaseData(const string &caseName_);

public:

	MeshBuilder(const string &caseName_);

	shared_ptr<Case> GetCase() const { return case_; }
	vector<vector<shared_ptr<Node>>> GetMesh() const { return mesh; }

	void ReserveMeshBlock();

	virtual void SetTop() = 0;
	virtual void SetBottom() = 0;
	virtual void SetLeft() = 0;
	virtual void SetRight() = 0;

	virtual void SetObstacle() = 0;
	virtual void SetPassiveScalarBlobb() = 0;
	virtual void InitializeVelocity() = 0;

	virtual ~MeshBuilder() = default;
};

