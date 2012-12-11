#include "StdAfx.h"
#include "InputManager.h"
#include <conio.h>


InputManager::InputManager(void)
{
}


InputManager::~InputManager(void)
{
}
//Todo, might be worth re wording a lot of this
string InputManager::GetStringFromUser()
{
	string input = "";
	cout << "Please enter a valid string:\n>";
	getline(cin, input);
	//Todo should we bother outputting this?
	cout << "You entered: " << input << endl << endl;
	return input;
}
float InputManager::GetFloatFromUser()
{
	string input = "";
	float myNumber = 0;//Todo rename
	bool WaitingForInput = true;

	while (WaitingForInput) 
	{
		cout << "Please enter a valid float: ";
		getline(cin, input);

		stringstream myStream(input);

		//>> overload returns true if sucessful
		if (myStream >> myNumber)
		{
			WaitingForInput =false;
		}
		else
		{
			cout << "Invalid number, please try again" << endl;
		}
	}
	//Todo should we bother outputting this?
	cout << "You entered: " << myNumber << endl << endl;
	return myNumber;
}

int InputManager::GetIntFromUser()
{
	string input = "";
	int myNumber = 0;//Todo rename
	bool WaitingForInput = true;

	while (WaitingForInput) 
	{
		cout << "Please enter a valid int: ";
		getline(cin, input);

		stringstream myStream(input);

		//>> overload returns true if sucessful
		if (myStream >> myNumber)
		{
			WaitingForInput =false;
		}
		else
		{
			cout << "Invalid number, please try again" << endl;
		}
	}
	//Todo should we bother outputting this?
	cout << "You entered: " << myNumber << endl << endl;
	return myNumber;
}

char InputManager::GetCharFromUser()
{
	
	string input = "";
	char ReturnChar  = {0};
	bool WaitingForInput = true;

	while (WaitingForInput) 
	{
		cout << "Please enter 1 char: ";
		getline(cin, input);

		if (input.length() == 1) 
		{
			ReturnChar = input[0];
			WaitingForInput = false;
		}
		else
		{
			cout << "Invalid character, please try again" << endl;
		}
	}
	//Todo should we bother outputting this?
	cout << "You entered: " << ReturnChar << endl << endl;
	return ReturnChar;
}

void InputManager::PressAnyKeyToContine()
{
	cout << "Press any key to contine..."<< endl << endl;
	_getch();
}