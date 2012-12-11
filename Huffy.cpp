// Huffy.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "InputManager.h"
#include "OutputManager.h"
#include "HuffyInt.h"
using namespace std;
void UnitTestHuffyInt();

int _tmain(int argc, _TCHAR* argv[])
{
	
	OutputManager Output;
	Output.PrintTitle();

	cout << "Running unit test of Huffy Int type.";
	UnitTestHuffyInt();
	system("PAUSE");


	return 0;
}

void UnitTestHuffyInt()
{
	cout << "Begining test, please enter an int value";
	InputManager Input;
	OutputManager Output;
	int ValueToTest = Input.GetIntFromUser();
	HuffyInt HuffyIntToTest(ValueToTest, "TestINt");

	cout << "Created an int with the value: ";
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
		cout << "Test Passed both values are equal\n";

		if(HuffyIntToTest.isBeingSent())
		{
			cout << "Huffy int is still being sent";
		}
		else 
		{
			cout << "Huffy int is not being sent";
		}
	}
	else
	{
		cout << "Test failed\n";
		cout << "Int value is:\n";
		Output.PrintInt(ValueToTest);
		cout << "HuffyInt value is:\n";
		Output.PrintInt(HuffyIntToTest.GetValue());
	}
	system("PAUSE");

}

