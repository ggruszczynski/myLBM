
#include "LidMeshBuilder.h"


void LidMeshBuilder::SetRight() {
	for (unsigned i = 0; i < mesh[0].size(); ++i)
		mesh[mesh.size() - 1][i] = std::move(std::make_shared<Wall>());

}

void LidMeshBuilder::SetLeft() {
    for (unsigned i = 0; i < mesh[0].size(); ++i)
        mesh[0][i] = move(make_shared<Wall>());
}

void LidMeshBuilder::SetPassiveScalarBlobb()
{
    auto blob = case_->passive_scalar_blobb_;

    for (unsigned x = 0; x < mesh.size(); ++x) {
        for (unsigned y = 0; y < mesh[x].size(); ++y) {
            if ((x - blob.x)*(x - blob.x) + (y - blob.y)*(y - blob.y) <= blob.r*blob.r)
            {
                mesh[x][y]->T = blob.T;
                for (auto& Tin_ : mesh[x][y]->TIn)
                    Tin_ = Tin_ * mesh[x][y]->T;
            }
        }
    }

    ///test - everywhere the same
    //for (unsigned x = 0; x < mesh.size() ; ++x) // skip walls
    //{
    //	for (unsigned y = 0; y < mesh[x].size() ; ++y) // skip walls
    //	{
    //		mesh[x][y]->T = blob.T;
    //		for (auto& Tin : mesh[x][y]->TIn)
    //			Tin = Tin * mesh[x][y]->T;
    //	}
    //}
}

void LidMeshBuilder::SetBottom() {
    for (unsigned i = 0; i < mesh.size(); ++i)
        mesh[i][0] = move(make_shared<Wall>());
}

void LidMeshBuilder::SetTop() {
    for (unsigned i = 0; i < mesh.size(); ++i)
        mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(case_->bcValues_.uLid, 0));

    //lets add some wall at the top and a Gaussian velocity distribution...
    //double wallFactor = 0.1; // amount of wall at each side

    //for (unsigned i = 0; i < mesh.size()*wallFactor; ++i)
    //	mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());

    //int movingWallLength = mesh.size()*(1-2*wallFactor);
    //double Sigma = 20;
    //vector<double> uGaussian = GaussianDistribution(movingWallLength, movingWallLength / 2, Sigma);
    //double uYScale = case_->bcValues_.uLid;

    //int i2 = 0;
    //for (unsigned i = mesh.size() *wallFactor; i < mesh.size() *(1 - wallFactor); ++i, ++i2) {
    //	//mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(case_->bcValues_.uLid, 0));
    //	mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<MovingWall>(uYScale*uGaussian[i2], 0));
    //}


    //for (unsigned i = mesh.size() *(1-wallFactor) ; i < mesh.size(); ++i)
    //	mesh[i][mesh[i].size() - 1] = std::move(std::make_shared<Wall>());
}

vector<double> LidMeshBuilder::GaussianDistribution(int domainLength, double mean, double Sig) const {
    vector<double> normalDistribution(domainLength,0);
    for (int x = 0; x < domainLength; ++x)
    {
        normalDistribution[x] = 1/(Sig*sqrt(2* M_PI));
        normalDistribution[x] *= exp(-(x - mean)*(x - mean)/(2*Sig*Sig));
    }
    return normalDistribution;
}

LidMeshBuilder::LidMeshBuilder(const string &caseName_) : MeshBuilder(caseName_){}
