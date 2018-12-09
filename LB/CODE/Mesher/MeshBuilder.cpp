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

MeshBuilder::MeshBuilder(const string &caseName_) {
	d2q9Constants = Singleton<D2Q9Constants>::get_instance();
	d2q5Constants = Singleton<D2Q5Constants>::get_instance();
	this->ReadCaseData(caseName_);
}

void MeshBuilder::ReadCaseData(const string &caseName_) {
	XMLParser xmlParser;
	case_ = std::make_shared<Case>(xmlParser.ReadXMLCase(caseName_));
}
