#include "StdAfx.h"
#include "HuffyFloat.h"
#include "IDGenerator.h"
#include "HuffyManager.h"

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
	m_HuffyID = IDGenerator::CreateHuffyIDByType(HuffyManager::e_HuffyFloat);
	HuffyManager::RegisterHuffyTypeAsSendable(m_HuffyID, this);
}

HuffyFloat::~HuffyFloat(void)
{
	//Todo Alert HuffyManager that this object is destroyed
}

int HuffyFloat::GetType(void) const
{
	return HuffyManager::e_HuffyFloat;
}

//Gets
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
		//Todo, Point of failure here if the type passed != to the actual type, fix this
		HuffyManager::HuffyTypeModified(HuffyManager::e_HuffyFloat, m_HuffyID);
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

HuffyFloat HuffyFloat::operator==(const HuffyFloat& other)
{
	return m_Value == other.m_Value;
}

HuffyFloat HuffyFloat::operator>=(const HuffyFloat& other)
{
	return m_Value >= other.m_Value;
}

HuffyFloat HuffyFloat::operator<=(const HuffyFloat& other)
{
	return m_Value >= other.m_Value;
}

HuffyFloat HuffyFloat::operator!=(const HuffyFloat& other)
{
	return m_Value >= other.m_Value;
}

HuffyFloat HuffyFloat::operator>(const HuffyFloat& other)
{
	return m_Value > other.m_Value;
}

HuffyFloat HuffyFloat::operator<(const HuffyFloat& other)
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

HuffyFloat HuffyFloat::operator==(const float& other)
{
	return m_Value == other;
}

HuffyFloat HuffyFloat::operator>=(const float& other)
{
	return m_Value >= other;
}

HuffyFloat HuffyFloat::operator<=(const float& other)
{
	return m_Value >= other;
}

HuffyFloat HuffyFloat::operator!=(const float& other)
{
	return m_Value >= other;
}

HuffyFloat HuffyFloat::operator>(const float& other)
{
	return m_Value > other;
}

HuffyFloat HuffyFloat::operator<(const float& other)
{
	return m_Value < other;
}

#pragma endregion