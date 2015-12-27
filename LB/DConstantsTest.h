#pragma once
#include "headers/DdQqConstants.h"

class DConstantsTest : public DdQqConstants
{
public:
	DConstantsTest() : DdQqConstants()
	{
		cout << "DConstantsTest() : DdQqConstants()" << endl;
		wtest.reserve(9);
		wtest.push_back(123. / 9);

		wtest.push_back(1. / 9);
		wtest.push_back(1. / 9);
		wtest.push_back(1. / 9);
		wtest.push_back(1. / 9);

		wtest.push_back(1. / 36);
		wtest.push_back(1. / 36);
		wtest.push_back(1. / 36);
		wtest.push_back(1. / 36);

	};


	void  InitializeMe() override
	{
		cout << "DConstantsTest() : InitializeMe()" << endl;
		wtest.reserve(9);
		wtest.push_back(123. / 9);

		wtest.push_back(1. / 9);
		wtest.push_back(1. / 9);
		wtest.push_back(1. / 9);
		wtest.push_back(1. / 9);

		wtest.push_back(1. / 36);
		wtest.push_back(1. / 36);
		wtest.push_back(1. / 36);
		wtest.push_back(1. / 36);
	};

	~DConstantsTest();
};

