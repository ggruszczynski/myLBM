#pragma once
#include "Node.h"
#include <memory>
#include "Case.h"

#include "MeshBuilder.h"
#include "CaseDirector.h"

class MeshDirector
{
private:

	//shared_ptr<Case> someCase;
	Case *someCase;
	MeshBuilder *meshBuilder;
	CaseDirector caseDirector;
public:

	void SetBuilder(MeshBuilder *newBuilder)
	{
		meshBuilder = newBuilder;
		caseDirector.setBuilder(meshBuilder->GetCaseBuilder());
	}


	Case* GetCase()
	{
		if (!someCase)
		{
			someCase = caseDirector.GetCase();
		}
		return someCase;
	}

	vector<vector<shared_ptr<Node>>> MakeMesh()
	{
		meshBuilder->SetCase( this->GetCase() );

		meshBuilder->ReserveMeshBlock();
		meshBuilder->SetTop();
		meshBuilder->SetBottom();
		meshBuilder->SetLeft();
		meshBuilder->SetRight();

		meshBuilder->SetObstacle();
		meshBuilder->SetPassiveScalarBlobb();
			
		meshBuilder->InitializeVelocity();

		return meshBuilder->GetMesh();
	}

	MeshDirector(){};


	~MeshDirector(){};
};

