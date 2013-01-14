#include "IDGenerator.h"
#include "HuffyManager.h"
#include "HuffyConstants.h"
#include <sstream>

using namespace std;

//Initalise static members
long long IDGenerator::IntsCreated = 0;
long long IDGenerator::BoolsCreated = 0;
long long IDGenerator::FloatsCreated = 0;
long long IDGenerator::Vector2DsCreated = 0;
long long IDGenerator::Vector3DsCreated = 0;
long long IDGenerator::StringsCreated = 0;

IDGenerator::IDGenerator(void)
{
}


IDGenerator::~IDGenerator(void)
{
}

string IDGenerator::CreateHuffyIDByType(e_HuffyTypes TypeToUse)
{
	IncrementTypeSpecificCounterByTypeEnum(TypeToUse);

	std::string ID = "";
	std::stringstream strstream;
	strstream << TypeToUse;
	switch (TypeToUse)
	{
		case e_HuffyBool:
			strstream << BoolsCreated;
			break;
		case e_HuffyInt:
			strstream << IntsCreated;
			break;
		case e_HuffyFloat:
			strstream << FloatsCreated;
			break;
	}

	strstream >> ID;
	return ID;
}

void IDGenerator::IncrementTypeSpecificCounterByTypeEnum(e_HuffyTypes TypeToIncrement)
{
	switch (TypeToIncrement) 
	{
		case e_HuffyBool:
			BoolsCreated++;
			break;
		case e_HuffyInt:
			IntsCreated++;
			break;
		case e_HuffyFloat:
			FloatsCreated++;
			break;
	}
		
}
