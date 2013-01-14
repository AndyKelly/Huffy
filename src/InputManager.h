/*
 * InputManager.h
 *
 *      Author: Andy Kelly
 */
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
	int GetPortNumFromUser();
	bool GetYesOrNoFromUser();
	void PressAnyKeyToContine();
};

