#pragma once
#include "Node.h"
#include <memory>
#include "Case.h"

#include "VelocityInlet.h"
#include "PressureOutlet.h"
#include "Wall.h"
#include "Enums.h"

class Mesher
{
private:
	Singleton<D2Q9Constants>*d2q9Constants;
	Singleton<D2Q5Constants>*d2q5Constants;
public:

	vector< vector<shared_ptr<Node>> > MakeChannelMesh(const unsigned& set_x, const unsigned& set_y, const Case & somecase);
	vector<vector<shared_ptr<Node>>> MakeLidDrivenCavityMesh(const unsigned& set_x, const unsigned& set_y, const Case& somecase);

	//void InitializeChannelMesh(vector< vector<shared_ptr<Node>> > mesh, const BCValues & bcValues );

	Mesher()
	{
		d2q9Constants = Singleton<D2Q9Constants>::get_instance();
		d2q5Constants = Singleton<D2Q5Constants>::get_instance();
	};


	~Mesher(){};
};

