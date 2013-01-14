/*
 * HuffyInt.cpp
 *
 *      Author: Andy Kelly
 */
#include "HuffyInt.h"
#include "IDGenerator.h"
#include "HuffyManager.h"
#include "HuffyConstants.h"

using namespace std;

HuffyInt::HuffyInt(void) 
{
	m_Value = 0;
}

HuffyInt::HuffyInt(int Value)
{
	m_Value = Value;
}

HuffyInt::HuffyInt(int Value, string UniqueID)
{
	m_Value = Value;
	m_Sendable = true;
	m_UniqueID = UniqueID;
	HuffyManager::RegisterHuffyTypeObject(m_UniqueID, this);
}

HuffyInt::~HuffyInt(void)
{
	HuffyManager::RemoveType(m_UniqueID, e_HuffyInt);
}

void HuffyInt::SetValue(int NewValue)
{
	UpdateHuffyManagaer();
	m_Value = NewValue;
}

int HuffyInt::GetType(void)const
{
	return e_HuffyInt;
}

std::string HuffyInt::GetID(void)
{
	return m_UniqueID;
}


//Gets
int HuffyInt::GetValue_C(void)const
{
	return m_Value;
}

int HuffyInt::GetValue(void)
{
	return m_Value;
}

bool HuffyInt::isBeingSent()
{
	return m_Sendable;
}

void HuffyInt::UpdateHuffyManagaer()
{

	if(m_Sendable)
	{
		HuffyManager::HuffyTypeModified(e_HuffyInt, m_UniqueID);
	}
}

//Operator overloads
	
#pragma region HuffyIntOverloads

HuffyInt HuffyInt::operator++(void)
{
	UpdateHuffyManagaer();
	m_Value++;
	return *this;
}

HuffyInt HuffyInt::operator--(void)
{
	UpdateHuffyManagaer();
	m_Value--;
	return *this;
}

HuffyInt HuffyInt::operator+(const HuffyInt&  other)
{
	return HuffyInt( m_Value + other.m_Value );
}

HuffyInt HuffyInt::operator-(const HuffyInt& other)
{
	return HuffyInt( m_Value - other.m_Value );
}

HuffyInt HuffyInt::operator/(const HuffyInt& other)
{
	return HuffyInt( m_Value / other.m_Value );
}

HuffyInt HuffyInt::operator*(const HuffyInt& other)
{
	return HuffyInt( m_Value * other.m_Value );
}

HuffyInt HuffyInt::operator=(const HuffyInt& other)
{
	UpdateHuffyManagaer();
	m_Value = other.m_Value;
	return *this;
}

HuffyInt HuffyInt::operator+=(const HuffyInt& other)
{
	UpdateHuffyManagaer();
	m_Value += other.m_Value;
	return *this;
}

HuffyInt HuffyInt::operator-=(const HuffyInt& other)
{
	UpdateHuffyManagaer();
	m_Value -= other.m_Value;
	return *this;
}

HuffyInt HuffyInt::operator/=(const HuffyInt& other)
{
	UpdateHuffyManagaer();
	m_Value /= other.m_Value;
	return *this;
}

HuffyInt HuffyInt::operator*=(const HuffyInt& other)
{
	UpdateHuffyManagaer();
	m_Value *= other.m_Value;
	return *this;
}

bool HuffyInt::operator==(const HuffyInt& other)
{
	return m_Value == other.m_Value;
}

bool HuffyInt::operator>=(const HuffyInt& other)
{
	return m_Value >= other.m_Value;
}

bool HuffyInt::operator<=(const HuffyInt& other)
{
	return m_Value >= other.m_Value;
}

bool HuffyInt::operator!=(const HuffyInt& other)
{
	return m_Value != other.m_Value;
}

bool HuffyInt::operator>(const HuffyInt& other)
{
	return m_Value > other.m_Value;
}

bool HuffyInt::operator<(const HuffyInt& other)
{
	return m_Value < other.m_Value;
}

#pragma endregion

#pragma region IntegerOverloads

HuffyInt HuffyInt::operator+(const int&  other)
{
	return HuffyInt( m_Value + other );
}

HuffyInt HuffyInt::operator-(const int& other)
{
	return HuffyInt( m_Value - other );
}

HuffyInt HuffyInt::operator/(const int& other)
{
	return HuffyInt( m_Value / other );
}

HuffyInt HuffyInt::operator*(const int& other)
{
	return HuffyInt( m_Value * other );
}

HuffyInt HuffyInt::operator=(const int& other)
{
	UpdateHuffyManagaer();
	m_Value = other;
	return *this;
}

HuffyInt HuffyInt::operator+=(const int& other)
{
	UpdateHuffyManagaer();
	m_Value += other;
	return *this;
}

HuffyInt HuffyInt::operator-=(const int& other)
{
	UpdateHuffyManagaer();
	m_Value -= other;
	return *this;
}

HuffyInt HuffyInt::operator/=(const int& other)
{
	UpdateHuffyManagaer();
	m_Value /= other;
	return *this;
}

HuffyInt HuffyInt::operator*=(const int& other)
{
	UpdateHuffyManagaer();
	m_Value *= other;
	return *this;
}

bool HuffyInt::operator==(const int& other)
{
	return m_Value == other;
}

bool HuffyInt::operator>=(const int& other)
{
	return m_Value >= other;
}

bool HuffyInt::operator<=(const int& other)
{
	return m_Value >= other;
}

bool HuffyInt::operator!=(const int& other)
{
	return m_Value != other;
}

bool HuffyInt::operator>(const int& other)
{
	return m_Value > other;
}

bool HuffyInt::operator<(const int& other)
{
	return m_Value < other;
}

#pragma endregion
