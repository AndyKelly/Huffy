#pragma once
#include <string>
#include "HuffyBaseType.h"

class HuffyFloat : HuffyBaseType
{
	
private:
	float m_Value;
	bool m_Sendable;
	std::string m_UniqueID;
	std::string m_HuffyID;

	//Member functions
	void UpdateHuffyManagaer(void);

public:
	HuffyFloat();
	HuffyFloat(float Value);
	HuffyFloat(float Value, std::string UniqueID);
	~HuffyFloat(void);

	//Virtual overrides
	int GetType(void);

	//Getter functions
	float GetValue_C(void)const;
	float GetValue(void);
	bool isBeingSent(void);
	//Operator Overloads
	HuffyFloat operator++(void);
	HuffyFloat operator--(void);
	HuffyFloat operator+(const HuffyFloat& other);
	HuffyFloat operator-(const HuffyFloat& other);
	HuffyFloat operator/(const HuffyFloat& other);
	HuffyFloat operator*(const HuffyFloat& other);
    HuffyFloat operator=(const HuffyFloat& other);
	HuffyFloat operator+=(const HuffyFloat& other);
	HuffyFloat operator-=(const HuffyFloat& other);
	HuffyFloat operator/=(const HuffyFloat& other);
	HuffyFloat operator*=(const HuffyFloat& other);
	HuffyFloat operator==(const HuffyFloat& other);
	HuffyFloat operator>=(const HuffyFloat& other);
	HuffyFloat operator<=(const HuffyFloat& other);
	HuffyFloat operator!=(const HuffyFloat& other);
	HuffyFloat operator>(const HuffyFloat& other);
	HuffyFloat operator<(const HuffyFloat& other);

	HuffyFloat operator+(const float& other);
	HuffyFloat operator-(const float& other);
	HuffyFloat operator/(const float& other);
	HuffyFloat operator*(const float& other);
    HuffyFloat operator=(const float& other);
	HuffyFloat operator+=(const float& other);
	HuffyFloat operator-=(const float& other);
	HuffyFloat operator/=(const float& other);
	HuffyFloat operator*=(const float& other);
	HuffyFloat operator==(const float& other);
	HuffyFloat operator>=(const float& other);
	HuffyFloat operator<=(const float& other);
	HuffyFloat operator!=(const float& other);
	HuffyFloat operator>(const float& other);
	HuffyFloat operator<(const float& other);
};

