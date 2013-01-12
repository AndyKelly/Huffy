#pragma once

class HuffyBaseType
{
public:
	HuffyBaseType(void);
	virtual ~HuffyBaseType(void);
	virtual int GetType(void) const = 0;
private:
};

