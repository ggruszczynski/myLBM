#pragma once

#include <iostream>
#include <vector>

//#include <Eigen/StdVector>
#include <eigen3/Eigen/StdVector>
//#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

template <class T> class Singleton
{

public:
	vector<Vector2d, Eigen::aligned_allocator<Eigen::Vector2d> > ee; // velocities directions

	double CSmag2 = 0.0009; // = CSmag * CSmag;


	template <typename... Args>	static T* get_instance(Args... args)
	{
		if (!instance_)
		{
			instance_ = new T(std::forward<Args>(args)...);
		}
		return instance_;
	}

	static
		void destroy_instance()
	{
		delete instance_;
		instance_ = nullptr;
	}

private:
	static T* instance_;
};

template <class T> T*  Singleton<T>::instance_ = nullptr;
