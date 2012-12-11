#pragma once


class HuffyBaseType
{
public:
	HuffyBaseType(void);
	~HuffyBaseType(void);
	virtual int GetType(void) = 0;
private:
};

