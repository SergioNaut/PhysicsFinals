#pragma once
#include <iostream>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

struct sProjectileDef
{
	std::string name1;
	float mass1;
	float radius1;

	std::string name2;
	float mass2;
	float radius2;

	std::string name3;
	float mass3;
	float radius3;
};

struct sConfiguration
{
	sProjectileDef projectiles;
};

class cConfigReader
{
public:
	
	bool ParseDefinition(rapidxml::xml_node<>* valueIn, sProjectileDef& valueOut);
	bool ParseConfig(rapidxml::xml_node<>* valueIn, sConfiguration& valueOut);
	bool ReadConfigFromXML(const std::string& filePath, sConfiguration& configOut);

	//SetValue for strings
	bool SetValue(rapidxml::xml_attribute<>* valueIn, std::string& valueOut);
	//SetValue for floats
	bool SetValue(rapidxml::xml_attribute<>* valueIn, float& valueOut);
};