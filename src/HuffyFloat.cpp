/*
 * HuffyFloat.cpp
 *
 *      Author: Andy Kelly
 */
#include "HuffyFloat.h"
#include "IDGenerator.h"
#include "HuffyManager.h"
#include "HuffyConstants.h"

using namespace std;

HuffyFloat::HuffyFloat(void) 
{
	m_Value = 0;
}

HuffyFloat::HuffyFloat(float Value)
{
	m_Value = Value;
}

HuffyFloat::HuffyFloat(float Value, string UniqueID)
{
	m_Value = Value;
	m_Sendable = true;
	m_UniqueID = UniqueID;
	HuffyManager::RegisterHuffyTypeObject(m_UniqueID, this);
}

HuffyFloat::~HuffyFloat(void)
{
	HuffyManager::RemoveType(m_UniqueID, e_HuffyFloat);
}

void HuffyFloat::SetValue(float NewValue)
{
	UpdateHuffyManagaer();
	m_Value = NewValue;
}

int HuffyFloat::GetType(void) const
{
	return e_HuffyFloat;
}

//Gets
std::string HuffyFloat::GetID(void)
{
	return m_UniqueID;
}

float HuffyFloat::GetValue_C(void)const
{
	return m_Value;
}

float HuffyFloat::GetValue(void)
{
	return m_Value;
}

bool HuffyFloat::isBeingSent()
{
	return m_Sendable;
}

void HuffyFloat::UpdateHuffyManagaer()
{

	if(m_Sendable)
	{
		HuffyManager::HuffyTypeModified(e_HuffyFloat, m_UniqueID);
	}
}

//Operator overloads
	
#pragma region HuffyFloatOverloads

HuffyFloat HuffyFloat::operator++(void)
{
	UpdateHuffyManagaer();
	m_Value++;
	return *this;
}

HuffyFloat HuffyFloat::operator--(void)
{
	UpdateHuffyManagaer();
	m_Value--;
	return *this;
}

HuffyFloat HuffyFloat::operator+(const HuffyFloat&  other)
{
	return HuffyFloat( m_Value + other.m_Value );
}

HuffyFloat HuffyFloat::operator-(const HuffyFloat& other)
{
	return HuffyFloat( m_Value - other.m_Value );
}

HuffyFloat HuffyFloat::operator/(const HuffyFloat& other)
{
	return HuffyFloat( m_Value / other.m_Value );
}

HuffyFloat HuffyFloat::operator*(const HuffyFloat& other)
{
	return HuffyFloat( m_Value * other.m_Value );
}

HuffyFloat HuffyFloat::operator=(const HuffyFloat& other)
{
	UpdateHuffyManagaer();
	m_Value = other.m_Value;
	return *this;
}

HuffyFloat HuffyFloat::operator+=(const HuffyFloat& other)
{
	UpdateHuffyManagaer();
	m_Value += other.m_Value;
	return *this;
}

HuffyFloat HuffyFloat::operator-=(const HuffyFloat& other)
{
	UpdateHuffyManagaer();
	m_Value -= other.m_Value;
	return *this;
}

HuffyFloat HuffyFloat::operator/=(const HuffyFloat& other)
{
	UpdateHuffyManagaer();
	m_Value /= other.m_Value;
	return *this;
}

HuffyFloat HuffyFloat::operator*=(const HuffyFloat& other)
{
	UpdateHuffyManagaer();
	m_Value *= other.m_Value;
	return *this;
}

bool HuffyFloat::operator==(const HuffyFloat& other)
{
	return m_Value == other.m_Value;
}

bool HuffyFloat::operator>=(const HuffyFloat& other)
{
	return m_Value >= other.m_Value;
}

bool HuffyFloat::operator<=(const HuffyFloat& other)
{
	return m_Value >= other.m_Value;
}

bool HuffyFloat::operator!=(const HuffyFloat& other)
{
	return m_Value != other.m_Value;
}

bool HuffyFloat::operator>(const HuffyFloat& other)
{
	return m_Value > other.m_Value;
}

bool HuffyFloat::operator<(const HuffyFloat& other)
{
	return m_Value < other.m_Value;
}

#pragma endregion

#pragma region floatOverloads

HuffyFloat HuffyFloat::operator+(const float&  other)
{
	return HuffyFloat( m_Value + other );
}

HuffyFloat HuffyFloat::operator-(const float& other)
{
	return HuffyFloat( m_Value - other );
}

HuffyFloat HuffyFloat::operator/(const float& other)
{
	return HuffyFloat( m_Value / other );
}

HuffyFloat HuffyFloat::operator*(const float& other)
{
	return HuffyFloat( m_Value * other );
}

HuffyFloat HuffyFloat::operator=(const float& other)
{
	UpdateHuffyManagaer();
	m_Value = other;
	return *this;
}

HuffyFloat HuffyFloat::operator+=(const float& other)
{
	UpdateHuffyManagaer();
	m_Value += other;
	return *this;
}

HuffyFloat HuffyFloat::operator-=(const float& other)
{
	UpdateHuffyManagaer();
	m_Value -= other;
	return *this;
}

HuffyFloat HuffyFloat::operator/=(const float& other)
{
	UpdateHuffyManagaer();
	m_Value /= other;
	return *this;
}

HuffyFloat HuffyFloat::operator*=(const float& other)
{
	UpdateHuffyManagaer();
	m_Value *= other;
	return *this;
}

bool HuffyFloat::operator==(const float& other)
{
	return m_Value == other;
}

bool HuffyFloat::operator>=(const float& other)
{
	return m_Value >= other;
}

bool HuffyFloat::operator<=(const float& other)
{
	return m_Value >= other;
}

bool HuffyFloat::operator!=(const float& other)
{
	return m_Value != other;
}

bool HuffyFloat::operator>(const float& other)
{
	return m_Value > other;
}

bool HuffyFloat::operator<(const float& other)
{
	return m_Value < other;
}

#pragma endregion
