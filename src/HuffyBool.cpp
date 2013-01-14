/*
 * HuffyBool.cpp
 *
 *      Author: Andy Kelly
 */
#include "HuffyBool.h"
#include "HuffyConstants.h"
#include "HuffyManager.h"

using namespace std;

HuffyBool::HuffyBool(void) 
{
	m_Value = 0;
}

HuffyBool::HuffyBool(bool Value)
{
	m_Value = Value;
}

HuffyBool::HuffyBool(bool Value, string UniqueID)
{
	m_Value = Value;
	m_Sendable = true;
	m_UniqueID = UniqueID;
	HuffyManager::RegisterHuffyTypeObject(m_UniqueID, this);
}

HuffyBool::~HuffyBool(void)
{
	HuffyManager::RemoveType(m_UniqueID, e_HuffyBool);
}

int HuffyBool::GetType(void)const
{
	return e_HuffyBool;
}

void HuffyBool::SetValue(bool NewValue)
{
	UpdateHuffyManagaer();
	m_Value = NewValue;
}


//Gets
std::string HuffyBool::GetID(void)
{
	return m_UniqueID;
}

bool HuffyBool::GetValue_C(void)const
{
	return m_Value;
}

bool HuffyBool::GetValue(void)
{
	return m_Value;
}

bool HuffyBool::isBeingSent()
{
	return m_Sendable;
}

void HuffyBool::UpdateHuffyManagaer()
{
	if(m_Sendable)
	{
		HuffyManager::HuffyTypeModified(e_HuffyBool, m_UniqueID);
	}
}

//Operator overloads
	
#pragma region HuffyBoolOverloads


HuffyBool HuffyBool::operator=(const HuffyBool& other)
{
	UpdateHuffyManagaer();
	m_Value = other.m_Value;
	return *this;
}

bool HuffyBool::operator==(const HuffyBool& other)
{
	return m_Value == other.m_Value;
}

bool HuffyBool::operator!=(const HuffyBool& other)
{
	return m_Value != other.m_Value;
}

#pragma endregion

#pragma region BoolOverloads

HuffyBool HuffyBool::operator=(const bool& other)
{
	UpdateHuffyManagaer();
	m_Value = other;
	return *this;
}

bool HuffyBool::operator==(const bool& other)
{
	return m_Value == other;
}

bool HuffyBool::operator!=(const bool& other)
{
	return m_Value != other;
}

#pragma endregion
