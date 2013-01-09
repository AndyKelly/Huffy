#include "IDGenerator.h"
#include "HuffyManager.h"
#include <sstream>

using namespace std;

//Initalise static members
long long IDGenerator::IntsCreated = 1;
long long IDGenerator::BoolsCreated = 1;
long long IDGenerator::FloatsCreated = 1;
long long IDGenerator::Vector2DsCreated = 1;
long long IDGenerator::Vector3DsCreated = 1;
long long IDGenerator::StringsCreated = 1;

//Todo should be singleton
IDGenerator::IDGenerator(void)
{
}


IDGenerator::~IDGenerator(void)
{
}

string IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyTypes TypeToUse)
{
	IncrementTypeSpecificCounterByTypeEnum(TypeToUse);

	std::string ID;
	std::stringstream strstream;
	strstream << TypeToUse;
	strstream << IntsCreated;
	strstream >> ID;
	return ID;
}

void IDGenerator::IncrementTypeSpecificCounterByTypeEnum(HuffyManager::e_HuffyTypes TypeToIncrement)
{
	switch (TypeToIncrement) 
	{
		case HuffyManager::e_HuffyBool:
			BoolsCreated++;
			break;
		case HuffyManager::e_HuffyInt:
			IntsCreated++;
			break;
		case HuffyManager::e_HuffyFloat:
			FloatsCreated++;
			break;
	}
		
}
