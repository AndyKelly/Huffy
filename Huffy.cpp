// Huffy.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "InputManager.h"
#include "OutputManager.h"
#include "HuffyInt.h"
#include "HuffyFloat.h"
#include "HuffyManager.h"
using namespace std;
void UnitTestHuffyInt();
void UnitTestHuffyFloat();
int _tmain(int argc, _TCHAR* argv[])
{
	
	OutputManager Output;
	Output.PrintTitle();

	cout << "Running unit test of Huffy Int type.";
	UnitTestHuffyInt();
	system("PAUSE");
	UnitTestHuffyFloat();
	HuffyManager::ConstructHuffyTrees();
	return 0;
}

void UnitTestHuffyInt()
{
	cout << "\nBegining test, please enter an int value\n";
	InputManager Input;
	OutputManager Output;
	int ValueToTest = Input.GetIntFromUser();
	HuffyInt HuffyIntToTest(ValueToTest, "TestINt");

	cout << "\nCreated an int with the value: \n";
	Output.PrintInt(HuffyIntToTest.GetValue());
	cout << "\n Running unit tests \n";
	system("PAUSE");


	HuffyIntToTest++;
	ValueToTest++;
	HuffyIntToTest--;
	ValueToTest--;
	HuffyIntToTest += 40;
	ValueToTest += 40;
	HuffyIntToTest -= 80;
	ValueToTest -= 80;
	HuffyIntToTest *= 4;
	ValueToTest *= 4;
	HuffyIntToTest /= 4;
	ValueToTest /= 4;

	HuffyIntToTest = HuffyIntToTest * 55;
	ValueToTest = ValueToTest * 55;
	HuffyIntToTest = HuffyIntToTest / 55;
	ValueToTest = ValueToTest / 55;

	if(HuffyIntToTest.GetValue() == ValueToTest)
	{
		cout << "\nTest Passed both values are equal\n";

		if(HuffyIntToTest.isBeingSent())
		{
			cout << "\nHuffy int is still being sent\n";
		}
		else 
		{
			cout << "\nHuffy int is not being sent\n";
		}

		cout << "\nHuffy Type value is:\n";
		Output.PrintInt(HuffyIntToTest.GetType());
	}
	else
	{
		cout << "\nTest failed\n";
		cout << "\nInt value is:\n";
		Output.PrintInt(ValueToTest);
		cout << "\nHuffyInt value is:\n";
		Output.PrintInt(HuffyIntToTest.GetValue());
	}
	system("PAUSE");

}


void UnitTestHuffyFloat()
{
	cout << "\nBegining test, please enter an Float value\n";
	InputManager Input;
	OutputManager Output;
	float ValueToTest = Input.GetFloatFromUser();
	HuffyFloat HuffyFloatToTest(ValueToTest, "TestFloat");

	cout << "\nCreated a Float with the value: \n";
	Output.PrintFloat(HuffyFloatToTest.GetValue());
	cout << "\n Running unit tests \n";
	system("PAUSE");


	HuffyFloatToTest++;
	ValueToTest++;
	HuffyFloatToTest--;
	ValueToTest--;
	HuffyFloatToTest += 40.4;
	ValueToTest += 40.4;
	HuffyFloatToTest -= 80;
	ValueToTest -= 80;
	HuffyFloatToTest *= 4;
	ValueToTest *= 4;
	HuffyFloatToTest /= 4;
	ValueToTest /= 4;

	HuffyFloatToTest = HuffyFloatToTest * 55;
	ValueToTest = ValueToTest * 55;
	HuffyFloatToTest = HuffyFloatToTest / 55;
	ValueToTest = ValueToTest / 55;

	if(HuffyFloatToTest.GetValue() == ValueToTest)
	{
		cout << "\nTest Passed both values are equal\n";

		if(HuffyFloatToTest.isBeingSent())
		{
			cout << "\nHuffy Float is still being sent\n";
		}
		else 
		{
			cout << "\nHuffy Float is not being sent\n";
		}

		cout << "\nHuffy Type value is:\n";
		Output.PrintInt(HuffyFloatToTest.GetType());
	}
	else
	{
		cout << "\nTest failed\n";
		cout << "\nFloat value is:\n";
		Output.PrintFloat(ValueToTest);
		cout << "\nHuffyFloat value is:\n";
		Output.PrintFloat(HuffyFloatToTest.GetValue());
	}
	system("PAUSE");

}

