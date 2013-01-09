#pragma once

class HuffyBaseType
{
public:
	HuffyBaseType(void);
	~HuffyBaseType(void);
	virtual int GetType(void) const = 0;
private:
};

