#include <cConfigReader.h>

bool cConfigReader::ParseDefinition(rapidxml::xml_node<>* valueIn, sProjectileDef& valueOut)
{
	if (!valueIn)
	{
		return false;
	}
	bool result = true;

	result &= SetValue(valueIn->first_attribute("Name1"), valueOut.name1);
	result &= SetValue(valueIn->first_attribute("Mass1"), valueOut.mass1);
	result &= SetValue(valueIn->first_attribute("Radius1"), valueOut.radius1);

	result &= SetValue(valueIn->first_attribute("Name2"), valueOut.name2);
	result &= SetValue(valueIn->first_attribute("Mass2"), valueOut.mass2);
	result &= SetValue(valueIn->first_attribute("Radius2"), valueOut.radius2);

	result &= SetValue(valueIn->first_attribute("Name3"), valueOut.name3);
	result &= SetValue(valueIn->first_attribute("Mass3"), valueOut.mass3);
	result &= SetValue(valueIn->first_attribute("Radius3"), valueOut.radius3);

	return result;

}

bool cConfigReader::ParseConfig(rapidxml::xml_node<>* valueIn, sConfiguration& valueOut)
{
	if (!valueIn)
	{
		return false;
	}
	bool result = true;
	result &= ParseDefinition(valueIn->first_node("Projectiles"), valueOut.projectiles);
	return result;
}
bool cConfigReader::ReadConfigFromXML(const std::string& filePath, sConfiguration& configOut)
{
	std::ifstream i(filePath);

	using namespace rapidxml;
	
	//load the file
	file<>* xmlFile = new file<>(i);

	xml_document<>* doc = new xml_document<>;    // character type defaults to char
	doc->parse<0>(xmlFile->data());// 0 means default parse flags

	bool result = ParseConfig(doc->first_node("Config"), configOut);

	delete xmlFile;
	delete doc;

	return result;
}

//SetValue for strings
bool cConfigReader::SetValue(rapidxml::xml_attribute<>* valueIn, std::string& valueOut)
{
	if (!valueIn)
	{
		return false;
	}
	valueOut = valueIn->value();
	return true;
}
//SetValue for floats
bool cConfigReader::SetValue(rapidxml::xml_attribute<>* valueIn, float& valueOut)
{
	if (!valueIn)
	{
		return false;
	}
	valueOut = std::stof(valueIn->value());
	return true;
}