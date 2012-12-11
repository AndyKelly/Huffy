#pragma once
#include <string>
#include "HuffyManager.h"
class IDGenerator
{
public:
	IDGenerator(void);
	~IDGenerator(void);
	static std::string CreateHuffyIDByType(HuffyManager::e_HuffyTypes);
private:
	static void IncrementTypeSpecificCounterByTypeEnum(HuffyManager::e_HuffyTypes);
	static long long IntsCreated;
	static long long BoolsCreated;
	static long long FloatsCreated;
	static long long Vector2DsCreated;
	static long long Vector3DsCreated;
	static long long StringsCreated;

};

