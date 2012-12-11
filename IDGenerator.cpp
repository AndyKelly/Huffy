#include "StdAfx.h"
#include "IDGenerator.h"
#include "HuffyManager.h"

using namespace std;

//Initalise static members
long long IDGenerator::IntsCreated = 0;
long long IDGenerator::BoolsCreated = 0;
long long IDGenerator::FloatsCreated = 0;
long long IDGenerator::Vector2DsCreated = 0;
long long IDGenerator::Vector3DsCreated = 0;
long long IDGenerator::StringsCreated = 0;

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
	//MSVC issue, have to cast to a larger type to use the to_string() function as no overload for int exists
	return(to_string(static_cast<long double>(TypeToUse)) + to_string(IntsCreated));
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
		case HuffyManager::e_HuffyVec2D:
			Vector2DsCreated++;
			break;
		case HuffyManager::e_HuffyVec3D:
			Vector3DsCreated++;
			break;
		case HuffyManager::e_HuffyString:
			StringsCreated++;
			break;
	}
		
}