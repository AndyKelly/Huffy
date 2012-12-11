#pragma once
#include <string>
class IDGenerator
{
public:
	IDGenerator(void);
	~IDGenerator(void);
	static std::string CreateHuffyIntID(void);
	static long long IntsCreated;

};

