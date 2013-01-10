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
    cout << ValueToBePrinted << endl;
}

void OutputManager::PrintFloat(float ValueToBePrinted)
{
	 cout << ValueToBePrinted << endl;
}
