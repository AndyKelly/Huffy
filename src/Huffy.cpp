/*
 * Huffy.cpp
 *
 *      Author: Andy Kelly
 */

#include <cstdlib>
#include "InputManager.h"
#include "OutputManager.h"
#include "IDGenerator.h"
#include "HuffyConstants.h"
#include "HuffyInt.h"
#include "HuffyFloat.h"
#include "HuffyBool.h"
#include "HuffyManager.h"
#include <iostream>
using namespace std;

void UnitTest();

int main()
{
	OutputManager Output;
	Output.PrintTitle();
	UnitTest();
	cout << "\nExiting\n";
	return 0;
}

void UnitTest()
{
	InputManager Input;
	OutputManager Output;
	///Am I a client or a server?
	cout << "Is this instance a server? y/n: ";
	bool Server = Input.GetYesOrNoFromUser();
	if(Server)
	{		

		//Create a few huffy types
		HuffyInt FirstInt(rand() % 100, IDGenerator::CreateHuffyIDByType(e_HuffyInt));
		HuffyManager::RegisterHuffyIntObject(FirstInt.GetID(),&FirstInt);
		HuffyInt SecondInt(rand() % 100, IDGenerator::CreateHuffyIDByType(e_HuffyInt));
		HuffyManager::RegisterHuffyIntObject(SecondInt.GetID(),&SecondInt);
		HuffyInt ThirdInt(rand() % 100, IDGenerator::CreateHuffyIDByType(e_HuffyInt));
		HuffyManager::RegisterHuffyIntObject(ThirdInt.GetID(),&ThirdInt);
		HuffyInt FourthInt(rand() % 100, IDGenerator::CreateHuffyIDByType(e_HuffyInt));
		HuffyManager::RegisterHuffyIntObject(FourthInt.GetID(),&FourthInt);

		HuffyFloat FirstFloat(float(rand() % 100), IDGenerator::CreateHuffyIDByType(e_HuffyFloat));
		HuffyManager::RegisterHuffyFloatObject(FirstFloat.GetID(),&FirstFloat);
		HuffyFloat SecondFloat(float(rand() % 100), IDGenerator::CreateHuffyIDByType(e_HuffyFloat));
		HuffyManager::RegisterHuffyFloatObject(SecondFloat.GetID(),&SecondFloat);
		HuffyFloat ThirdFloat(float(rand() % 100), IDGenerator::CreateHuffyIDByType(e_HuffyFloat));
		HuffyManager::RegisterHuffyFloatObject(ThirdFloat.GetID(),&ThirdFloat);

		HuffyBool FirstBool(true, IDGenerator::CreateHuffyIDByType(e_HuffyBool));
		HuffyManager::RegisterHuffyBoolObject(FirstBool.GetID(),&FirstBool);
		HuffyBool SecondBool(false, IDGenerator::CreateHuffyIDByType(e_HuffyBool));
		HuffyManager::RegisterHuffyBoolObject(SecondBool.GetID(),&SecondBool);
		HuffyBool ThirdBool(true, IDGenerator::CreateHuffyIDByType(e_HuffyBool));
		HuffyManager::RegisterHuffyBoolObject(ThirdBool.GetID(),&ThirdBool);
		//Calculate sum of types
		float sum = 0;
		sum += float(FirstInt.GetValue());
		sum += float(SecondInt.GetValue());
		sum += float(ThirdInt.GetValue());
		sum += float(FirstFloat.GetValue());
		sum += float(SecondFloat.GetValue());
		sum += float(ThirdFloat.GetValue());

		if(FirstBool.GetValue())
		{
			sum++;
		}
		if(SecondBool.GetValue())
		{
			sum++;
		}
		if(ThirdBool.GetValue())
		{
			sum++;
		}


		cout << "\nSum of all Huffy types is:";
		Output.PrintFloat(sum);
		//Send an update

		cout << "\nInitalising server\n";
		HuffyManager::Initalise(Server, "");
		bool Continue = true;
		HuffyManager::Update();
		cout<< "\nUpdate sent";



	}
	else
	{
		//Get address
		cout << "\nOk, setting up a client, please enter server address i.e. localhost: \n";
		std::string IPAddress =  Input.GetStringFromUser();
		//Create a few huffy types
		//Create a few huffy types
		HuffyInt FirstInt(0, IDGenerator::CreateHuffyIDByType(e_HuffyInt));
		HuffyManager::RegisterHuffyIntObject(FirstInt.GetID(),&FirstInt);
		HuffyInt SecondInt(0, IDGenerator::CreateHuffyIDByType(e_HuffyInt));
		HuffyManager::RegisterHuffyIntObject(SecondInt.GetID(),&SecondInt);
		HuffyInt ThirdInt(0, IDGenerator::CreateHuffyIDByType(e_HuffyInt));
		HuffyManager::RegisterHuffyIntObject(ThirdInt.GetID(),&ThirdInt);

		HuffyFloat FirstFloat(0, IDGenerator::CreateHuffyIDByType(e_HuffyFloat));
		HuffyManager::RegisterHuffyFloatObject(FirstFloat.GetID(),&FirstFloat);
		HuffyFloat SecondFloat(0, IDGenerator::CreateHuffyIDByType(e_HuffyFloat));
		HuffyManager::RegisterHuffyFloatObject(SecondFloat.GetID(),&SecondFloat);
		HuffyFloat ThirdFloat(0, IDGenerator::CreateHuffyIDByType(e_HuffyFloat));
		HuffyManager::RegisterHuffyFloatObject(ThirdFloat.GetID(),&ThirdFloat);

		HuffyBool FirstBool(false, IDGenerator::CreateHuffyIDByType(e_HuffyBool));
		HuffyManager::RegisterHuffyBoolObject(FirstBool.GetID(),&FirstBool);
		HuffyBool SecondBool(false, IDGenerator::CreateHuffyIDByType(e_HuffyBool));
		HuffyManager::RegisterHuffyBoolObject(SecondBool.GetID(),&SecondBool);
		HuffyBool ThirdBool(false, IDGenerator::CreateHuffyIDByType(e_HuffyBool));
		HuffyManager::RegisterHuffyBoolObject(ThirdBool.GetID(),&ThirdBool);
		
		//Calculate sum of types
		float sum = 0;
		sum += float(FirstInt.GetValue());
		sum += float(SecondInt.GetValue());
		sum += float(ThirdInt.GetValue());
		sum += float(FirstFloat.GetValue());
		sum += float(SecondFloat.GetValue());
		sum += float(ThirdFloat.GetValue());

		if(FirstBool.GetValue())
		{
			sum++;
		}
		if(SecondBool.GetValue())
		{
			sum++;
		}
		if(ThirdBool.GetValue())
		{
			sum++;
		}
		//Output sum of types
		cout << "\nSum of all Huffy types before update is:\n";
		Output.PrintFloat(sum);
		//Await an update
		HuffyManager::Initalise(Server, IPAddress);
		HuffyManager::Update();
		cout << "\n\n\nSum of all types after update is:\n";
		Output.PrintFloat(sum);

	}

}
