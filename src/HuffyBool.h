#pragma once
#include <string>
#include "HuffyBaseType.h"

class HuffyBool : HuffyBaseType
{
	
private:
	bool m_Value;
	bool m_Sendable;
	std::string m_UniqueID;
	std::string m_HuffyID;

	//Member functions
	void UpdateHuffyManagaer(void);

public:
	HuffyBool();
	HuffyBool(bool Value);
	HuffyBool(bool Value, std::string UniqueID);
	~HuffyBool(void);

	//Virtual overrides
	int GetType(void) const;

	//Getter functions
	bool GetValue_C(void)const;
	//Todo Is this function ever used?
	bool GetValue(void);
	bool isBeingSent(void);
	//Operator Overloads
    HuffyBool operator=(const HuffyBool& other);
	bool operator==(const HuffyBool& other);
	bool operator!=(const HuffyBool& other);

    HuffyBool operator=(const bool& other);
	bool operator==(const bool& other);
	bool operator!=(const bool& other);
};
