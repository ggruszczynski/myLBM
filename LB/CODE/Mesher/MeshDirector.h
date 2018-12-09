#pragma once
#include "../Nodes/Node.h"
#include <memory>
#include "../Cases/Case.h"

#include "MeshBuilder.h"
#include "../IO/XMLParser.h"

class MeshDirector
{
private:
	XMLParser xml_parser_;
	MeshBuilder *meshBuilder;
public:

	void SetBuilder(MeshBuilder *newBuilder){meshBuilder = newBuilder;}


	shared_ptr<Case> GetCase() const { return meshBuilder->GetCase();	}

	vector<vector<shared_ptr<Node>>> MakeMesh() const
	{
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

