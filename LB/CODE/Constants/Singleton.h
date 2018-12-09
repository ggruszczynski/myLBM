#pragma once

#include <iostream>
#include <vector>

#include <eigen3/Eigen/StdVector>

using namespace Eigen;
using namespace std;

struct lattice_vectors
{
    int x;
    int y;
};

template <class T> class Singleton
{
public:
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
