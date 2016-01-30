#pragma once
#include "../Nodes/Node.h"
#include <memory>
#include "../Cases/Case.h"

#include "../IO/XMLParser.h"


class MeshBuilder
{
protected:
	Singleton<D2Q9Constants>*d2q9Constants;
	Singleton<D2Q5Constants>*d2q5Constants;

	shared_ptr<Case> case_;
	vector<vector<shared_ptr<Node>>> mesh;

	void ReadCaseData(const string &caseName_)
	{
		XMLParser xmlParser;
		case_ = std::make_shared<Case>(xmlParser.ReadXMLCase(caseName_));
	};

public:

	MeshBuilder(const string &caseName_)
	{
		d2q9Constants = Singleton<D2Q9Constants>::get_instance();
		d2q5Constants = Singleton<D2Q5Constants>::get_instance();
		this->ReadCaseData(caseName_);
	}

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

	virtual ~MeshBuilder() {};
};

