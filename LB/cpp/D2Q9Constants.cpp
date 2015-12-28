/*
 * D2Q9Constants.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: muaddieb
 */

#include "../headers/D2Q9Constants.h"
#include <Eigen/StdVector>


//bool D2Q9Constants::instanceFlag = false;
//D2Q9Constants* D2Q9Constants::single = NULL;
//
//
//D2Q9Constants* D2Q9Constants::GetInstance()
//{
//	if (!instanceFlag)
//	{
//		single = new D2Q9Constants();
//		instanceFlag = true;
//		return single;
//	}
//	else
//	{
//		return single;
//	}
//}

//const double  D2Q9Constants :: cs2 = 1 / 3;
////double  D2Q9Constants :: omegaNS; // these are not pointers, thus const double = double const
//
//vector <double>  D2Q9Constants:: w = [] {
//	vector <double> tempVec;
//
//	tempVec.reserve(9);
//	tempVec.push_back(4. / 9);
//
//	tempVec.push_back(1. / 9);
//	tempVec.push_back(1. / 9);
//	tempVec.push_back(1. / 9);
//	tempVec.push_back(1. / 9);
//
//	tempVec.push_back(1. / 36);
//	tempVec.push_back(1. / 36);
//	tempVec.push_back(1. / 36);
//	tempVec.push_back(1. / 36);
//
//	return tempVec;
//}();
//
//
//vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d> >  D2Q9Constants:: e  = [] {
//
//	vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d>> tempVec;
//	//std::vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d> > tempVec;
//	tempVec.reserve(9);
//
//	tempVec.push_back(Eigen::Vector2d(0, 0));
//
//	tempVec.push_back(Eigen::Vector2d(1, 0));
//	tempVec.push_back(Eigen::Vector2d(0, 1));
//	tempVec.push_back(Eigen::Vector2d(-1, 0));
//	tempVec.push_back(Eigen::Vector2d(0, -1));
//
//	tempVec.push_back(Eigen::Vector2d(1, 1));
//	tempVec.push_back(Eigen::Vector2d(-1, 1));
//	tempVec.push_back(Eigen::Vector2d(-1, -1));
//	tempVec.push_back(Eigen::Vector2d(1, -1));
//
//	return tempVec;
//}();
