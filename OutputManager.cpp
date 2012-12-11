#include "StdAfx.h"
#include "OutputManager.h"
#include <string>
#include <iostream>

using namespace std;

OutputManager::OutputManager(void)
{
}


OutputManager::~OutputManager(void)
{
}

void OutputManager::PrintTitle(void)
{
	cout << "//////////////////////////////////\n";
	cout << "               HUFFY\n";
	cout << "//////////////////////////////////\n";
}

void OutputManager::PrintInt(int ValueToBePrinted)
{
	//MSVC issue, have to cast to a larger type to use the to_string function as no overload for int exists
    cout << std::to_string(static_cast<long double>(ValueToBePrinted)) << endl;
}

//Todo Replace with template type and merge these functions??
void OutputManager::PrintFloat(float ValueToBePrinted)
{
	//MSVC issue, have to cast to a larger type to use the to_string function as no overload for int exists
    printf("%f",ValueToBePrinted);
}