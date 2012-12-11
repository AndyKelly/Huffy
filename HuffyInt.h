#pragma once
#include <string>
class HuffyInt
{
	
private:
	int m_Value;
	bool m_Sendable;
	std::string m_UniqueID;
	std::string m_HuffyID;

	//Member functions
	void UpdateHuffyManagaer(void);

public:
	HuffyInt();
	HuffyInt(int Value);
	HuffyInt(int Value, std::string UniqueID);
	~HuffyInt(void);

	//Getter functions
	int GetValue_C(void)const;
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
	HuffyInt operator==(const HuffyInt& other);
	HuffyInt operator>=(const HuffyInt& other);
	HuffyInt operator<=(const HuffyInt& other);
	HuffyInt operator!=(const HuffyInt& other);
	HuffyInt operator>(const HuffyInt& other);
	HuffyInt operator<(const HuffyInt& other);

	HuffyInt operator+(const int& other);
	HuffyInt operator-(const int& other);
	HuffyInt operator/(const int& other);
	HuffyInt operator*(const int& other);
    HuffyInt operator=(const int& other);
	HuffyInt operator+=(const int& other);
	HuffyInt operator-=(const int& other);
	HuffyInt operator/=(const int& other);
	HuffyInt operator*=(const int& other);
	HuffyInt operator==(const int& other);
	HuffyInt operator>=(const int& other);
	HuffyInt operator<=(const int& other);
	HuffyInt operator!=(const int& other);
	HuffyInt operator>(const int& other);
	HuffyInt operator<(const int& other);
};

