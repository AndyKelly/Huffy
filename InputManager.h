#pragma once
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class InputManager
{
public:
	InputManager(void);
	~InputManager(void);
	string GetStringFromUser();
	int GetIntFromUser();
	float GetFloatFromUser();
	char GetCharFromUser();//YAGNIS
	void PressAnyKeyToContine();
};

