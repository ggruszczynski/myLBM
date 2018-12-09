#pragma once

//#include <tchar.h>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include "../Cases/Case.h"

using namespace std;

class XMLParser
{
private:
	boost::property_tree::ptree ptree_;

public:
	void WriteCaseInfoXML(const string &directory_, const string &filename_) const;
	Case ReadXMLCase(const std::string &filename);

	XMLParser(){};
	~XMLParser(){};
};
