#include "XMLParser.h"


#include <boost/lexical_cast.hpp>


Case XMLParser::ReadXMLCase(const std::string& filename)
{
// http://www.technical-recipes.com/2014/using-boostproperty_tree/
	
	read_xml(filename, this->ptree_, boost::property_tree::xml_parser::trim_whitespace);

	Case case_; // make a struct case_ and read into it...
	try {
		case_.bcValues_.uLid = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.BCValues.uLid"));
		case_.bcValues_.uInlet = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.BCValues.uInlet"));
		case_.bcValues_.nu = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.BCValues.nu"));

		case_.obstacle_.x = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.Obstacle.x"));
		case_.obstacle_.y = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.Obstacle.y"));
		case_.obstacle_.r = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.Obstacle.r"));

		case_.passive_scalar_blobb_.T = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.PassiveScalarBlobb.T"));
		case_.passive_scalar_blobb_.K = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.PassiveScalarBlobb.K"));
		case_.passive_scalar_blobb_.x = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.PassiveScalarBlobb.x"));
		case_.passive_scalar_blobb_.y = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.PassiveScalarBlobb.y"));
		case_.passive_scalar_blobb_.r = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.PassiveScalarBlobb.r"));

		case_.timer_.totalTime = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.Timer.totalTime"));
		case_.timer_.timeToSaveVTK = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.Timer.timeToSaveVTK"));
		case_.timer_.timeToSavePointData = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.Timer.timeToSavePointData"));

		case_.meshGeom_.x = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.BlockGeom.x"));
		case_.meshGeom_.y = boost::lexical_cast<double>(this->ptree_.get<std::string>("case.BlockGeom.y"));
		case_.meshGeom_.numberOfNodes = case_.meshGeom_.x* case_.meshGeom_.y;

		///old fashion way
		//std::string pscT_s = pt.get<std::string>("case.PassiveScalarBlobb.T");
		//case_.passive_scalar_blobb_.T = boost::lexical_cast<double>(pscT_s);

		//string test_emptyx_s = pt.get<std::string>("case.PassiveScalarBlobb.x");
		//string test_emptyy_s = pt.get<std::string>("case.PassiveScalarBlobb.y");

		//double test_emptyx_d = boost::lexical_cast<double>(test_emptyx_s);
		//double test_emptyy_d = boost::lexical_cast<double>(test_emptyy_s);
	}
	catch (boost::bad_lexical_cast&) {
		cout << "bad_lexical_cast in:" << filename << endl;
	}

	return case_;
}


void XMLParser::WriteCaseInfoXML(const string &directory_,const string &filename_) const
{

	string filePath_and_Name = directory_ + "/" + filename_  + ".xml";

	//write the stuff back...
	if (!this->ptree_.empty())
		write_xml(filePath_and_Name, this->ptree_, std::locale(), boost::property_tree::xml_writer_make_settings<boost::property_tree::ptree::key_type>(' ', 1u));
	else
		cout << "XMLParser::WriteCaseInfoXML --> ptree_ is empty :(" << endl;
}
