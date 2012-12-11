#include "StdAfx.h"
#include "IDGenerator.h"
#include "HuffyManager.h"

using namespace std;

//Initalise static members
long long IDGenerator::IntsCreated = 0;

//Todo should be singleton
IDGenerator::IDGenerator(void)
{
}


IDGenerator::~IDGenerator(void)
{
}

string IDGenerator::CreateHuffyIntID(void)
{
	IntsCreated++;
	//MSVC issue, have to cast to a larger type to use the to_string() function as no overload for int exists
	return(to_string(static_cast<long double>(HuffyManager::e_HuffyInt)) + to_string(IntsCreated));
}