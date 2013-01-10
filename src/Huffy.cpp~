// Huffy.cpp : Defines the entry point for the console application.

#include <cstdlib>
#include "InputManager.h"
#include "OutputManager.h"
#include "IDGenerator.h"
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

	cout << "Running unit test's.";
	UnitTest();
	cout << "\nExiting\n";
	return 0;
}

void UnitTest()
{
	InputManager Input;
	OutputManager Output;
	///Am I a client or a server?
	cout << "Is this instance a server? y/n";
	bool Server = Input.GetYesOrNoFromUser();

	if(Server)
	{		
		//Get address
		cout << "\nOk, setting up a server, please enter an address to send to: \n";
		std::string IPAddress =  Input.GetStringFromUser(); 
		cout << "\nPlease enter a port to send to, between 1024 & 65535: \n";
		int PortNum = Input.GetPortNumFromUser();

		//Create a few huffy types
		HuffyInt FirstInt(rand() % 100, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyInt));
		HuffyInt SecondInt(rand() % 100, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyInt));
		HuffyInt ThirdInt(rand() % 100, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyInt));

		HuffyFloat FirstFloat(float(rand() % 100), IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyFloat));
		HuffyFloat SecondFloat(float(rand() % 100), IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyFloat));
		HuffyFloat ThirdFloat(float(rand() % 100), IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyFloat));

		HuffyBool FirstBool(true, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyBool));
		HuffyBool SecondBool(false, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyBool));
		HuffyBool ThirdBool(true, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyBool));
		
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

		//Send an update
		HuffyManager::Initalise(Server, IPAddress, PortNum);
		HuffyManager::Update();

		cout << "Sum of all sent types is:\n";
		Output.PrintFloat(sum);

	}
	else
	{
		//get port 
		cout << "Ok, setting up a client, please enter a port to listen on, between 1024 & 65535";
		int PortNum = Input.GetPortNumFromUser();

		//Create a few huffy types
		//Create a few huffy types
		HuffyInt FirstInt(0, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyInt));
		HuffyInt SecondInt(0, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyInt));
		HuffyInt ThirdInt(0, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyInt));

		HuffyFloat FirstFloat(0, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyFloat));
		HuffyFloat SecondFloat(0, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyFloat));
		HuffyFloat ThirdFloat(0, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyFloat));

		HuffyBool FirstBool(false, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyBool));
		HuffyBool SecondBool(false, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyBool));
		HuffyBool ThirdBool(false, IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyBool));
		
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

		//Await an update
		HuffyManager::Initalise(Server, "", PortNum);
		HuffyManager::Update();

		//Output sum of types
		cout << "Sum of all sent types is:\n";
		Output.PrintFloat(sum);
	}

}
