#include "StdAfx.h"
#include "HuffyBool.h"
#include "IDGenerator.h"
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
	m_HuffyID = IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyBool);
	HuffyManager::RegisterHuffyTypeObject(m_HuffyID, this);
}

HuffyBool::~HuffyBool(void)
{
	//Todo Alert HuffyManager that this object is destroyed
}

int HuffyBool::GetType(void) const
{
	return HuffyManager::e_HuffyBool;
}

//Gets
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
		//Todo, Point of failure here if the type passed != to the actual type, fix this
		HuffyManager::HuffyTypeModified(HuffyManager::e_HuffyBool, m_HuffyID);
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