#include "InputManager.h"


InputManager::InputManager(void)
{
}


InputManager::~InputManager(void)
{
}

string InputManager::GetStringFromUser()
{
	string input = "";
	getline(cin, input);
	return input;
}


int InputManager::GetPortNumFromUser()
{
	string input = "";
	int UserValue = 0;
	bool WaitingForInput = true;

	while (WaitingForInput) 
	{
		getline(cin, input);

		stringstream myStream(input);

		//>> overload returns true if sucessful
		if (myStream >> UserValue)
		{
			//Check if valid port
			if(UserValue >= 1024 && UserValue <= 65535)
			{
				WaitingForInput =false;
			}
		}
		else
		{
			cout << "\nInvalid number, please try again, makes sure to specify a value in the range 1024 - 65535: \n" << endl;
		}
	}
	return UserValue;
}


bool InputManager::GetYesOrNoFromUser()
{
	
	string input = "";
	bool WaitingForInput = true;
	bool ReturnValue;

	while (WaitingForInput) 
	{
		getline(cin, input);

		if (input.length() == 1) 
		{
			//Check to see if y or n
			if(input[0] == 'y'|| input[0] == 'Y')
			{
				ReturnValue = true;
				WaitingForInput = false;
			}
			else if( input[0] == 'n'|| input[0] == 'N')
			{
				ReturnValue = false;
				WaitingForInput = false;
			}
		}
		else
		{
			cout << "\nInvalid character, please try again\n" << endl;
		}
	}
	return ReturnValue;
}
