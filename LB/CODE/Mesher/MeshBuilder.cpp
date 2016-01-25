#include "MeshBuilder.h"

void MeshBuilder::ReserveMeshBlock()
{
	mesh.reserve(case_->meshGeom_.x);
	for (unsigned i = 0; i < case_->meshGeom_.x; ++i)// rectangular block
	{
		vector< shared_ptr <Node>>vec_pion;
		vec_pion.reserve(case_->meshGeom_.y);
		for (unsigned j = 0; j < case_->meshGeom_.y; ++j)
		{
			vec_pion.emplace_back(new Node);
		}
		mesh.emplace_back(vec_pion);
	}
}
