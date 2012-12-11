#include "StdAfx.h"
#include "HuffyInt.h"
#include "IDGenerator.h"
#include "HuffyManager.h"

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
	m_HuffyID = IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyInt);
	HuffyManager::RegisterHuffyTypeAsSendable(m_HuffyID, this);
}

HuffyInt::~HuffyInt(void)
{
	//Todo Alert HuffyManager that this object is destroyed
}

int HuffyInt::GetType(void) const
{
	return HuffyManager::e_HuffyInt;
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
		HuffyManager::HuffyTypeModified(m_HuffyID, HuffyManager::e_HuffyInt);
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

HuffyInt HuffyInt::operator==(const HuffyInt& other)
{
	return m_Value == other.m_Value;
}

HuffyInt HuffyInt::operator>=(const HuffyInt& other)
{
	return m_Value >= other.m_Value;
}

HuffyInt HuffyInt::operator<=(const HuffyInt& other)
{
	return m_Value >= other.m_Value;
}

HuffyInt HuffyInt::operator!=(const HuffyInt& other)
{
	return m_Value >= other.m_Value;
}

HuffyInt HuffyInt::operator>(const HuffyInt& other)
{
	return m_Value > other.m_Value;
}

HuffyInt HuffyInt::operator<(const HuffyInt& other)
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

HuffyInt HuffyInt::operator==(const int& other)
{
	return m_Value == other;
}

HuffyInt HuffyInt::operator>=(const int& other)
{
	return m_Value >= other;
}

HuffyInt HuffyInt::operator<=(const int& other)
{
	return m_Value >= other;
}

HuffyInt HuffyInt::operator!=(const int& other)
{
	return m_Value >= other;
}

HuffyInt HuffyInt::operator>(const int& other)
{
	return m_Value > other;
}

HuffyInt HuffyInt::operator<(const int& other)
{
	return m_Value < other;
}

#pragma endregion