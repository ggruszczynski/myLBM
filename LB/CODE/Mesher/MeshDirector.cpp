#include "MeshDirector.h"



//
//vector<vector<shared_ptr<Node>>> MeshDirector::MakeLidDrivenCavityMesh()
//{
//	vector<vector<shared_ptr<Node>>> mesh;
//
//	//auto bcValues = someCase.bcValues_;
//	//auto obstacle = someCase.obstacle_;
//	//auto passiveScalarBlobb = someCase.passive_scalar_blobb_;
//
//	 // (set_y); how to add in place instead of after the last element... why pushback doesnt work?
//
//	this->ReserveMeshBlock(mesh);
//
//	for (unsigned i = 0; i < mesh.size(); ++i) // top/bottom
//	{
//		mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(someCase->bcValues_.uLid,0));
//		mesh[i][0] = std::move(std::make_shared<Wall>());
//	}
//
//	for (unsigned i = 0; i < mesh[0].size(); ++i) // sides
//	{
//		mesh[0][i] = std::move(std::make_shared<Wall>());
//		mesh[mesh.size() - 1][i] = std::move(std::make_shared<Wall>());
//	}
//
//	//---------------------initialize Temp----------------------
//	for (unsigned x = 0; x < mesh.size(); ++x) {
//		for (unsigned y = 0; y < mesh[x].size(); ++y) {
//			if ((x - someCase->passive_scalar_blobb_.x)*(x - someCase->passive_scalar_blobb_.x) + (y - someCase ->passive_scalar_blobb_.y)*(y - someCase->passive_scalar_blobb_.y) <= someCase->passive_scalar_blobb_.r*someCase ->passive_scalar_blobb_.r)
//			{
//				mesh[x][y]->T = someCase->passive_scalar_blobb_.T;
//				for (auto& Tin : mesh[x][y]->TIn)
//					Tin = Tin * mesh[x][y]->T;
//			}
//		}
//	}
//
//	return mesh;
//}
