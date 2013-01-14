/*
 * HuffyInt.h
 *
 *      Author: Andy Kelly
 */
#pragma once
#include <string>
#include "HuffyBaseType.h"

class HuffyInt : HuffyBaseType
{
	
private:
	int m_Value;
	bool m_Sendable;
	std::string m_UniqueID;

	//Member functions
	void UpdateHuffyManagaer(void);

public:
	HuffyInt();
	HuffyInt(int Value);
	HuffyInt(int Value, std::string UniqueID);
	~HuffyInt(void);

	//Virtual overrides
	int GetType(void) const;

	//Setter
	void SetValue(int);
	//Getter functions

	std::string GetID(void);
	int GetValue_C(void) const;
	int GetValue(void);
	bool isBeingSent(void);
	//Operator Overloads
	HuffyInt operator++(void);
	HuffyInt operator--(void);
	HuffyInt operator+(const HuffyInt& other);
	HuffyInt operator-(const HuffyInt& other);
	HuffyInt operator/(const HuffyInt& other);
	HuffyInt operator*(const HuffyInt& other);
    HuffyInt operator=(const HuffyInt& other);
	HuffyInt operator+=(const HuffyInt& other);
	HuffyInt operator-=(const HuffyInt& other);
	HuffyInt operator/=(const HuffyInt& other);
	HuffyInt operator*=(const HuffyInt& other);
	bool operator==(const HuffyInt& other);
	bool operator>=(const HuffyInt& other);
	bool operator<=(const HuffyInt& other);
	bool operator!=(const HuffyInt& other);
	bool operator>(const HuffyInt& other);
	bool operator<(const HuffyInt& other);

	HuffyInt operator+(const int& other);
	HuffyInt operator-(const int& other);
	HuffyInt operator/(const int& other);
	HuffyInt operator*(const int& other);
    HuffyInt operator=(const int& other);
	HuffyInt operator+=(const int& other);
	HuffyInt operator-=(const int& other);
	HuffyInt operator/=(const int& other);
	HuffyInt operator*=(const int& other);
	bool operator==(const int& other);
	bool operator>=(const int& other);
	bool operator<=(const int& other);
	bool operator!=(const int& other);
	bool operator>(const int& other);
	bool operator<(const int& other);
};

