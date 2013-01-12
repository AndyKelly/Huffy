#pragma once
#define BufferLimit 256
#include <string>
#include <list>
#include <bitset>
#include <map>
#include <math.h>
#include "ServerSocket.h"
#include "SocketException.h"
#include "ClientSocket.h"
class HuffyCompressor
{
	
public:
	HuffyCompressor(void);
	~HuffyCompressor(void);
	static bool Initalise(std::string, int, bool);
	static std::string GetUpdate();
	static int HowManyBitsToStoreThis(int);
	static int HowManyBitsToStoreThis(float);
	static void PassPointersToHuffyTreeRootNodes(HuffyManager::TypeQueueElement*,HuffyManager::IDQueueElement* ,HuffyManager::IDQueueElement* ,HuffyManager::IDQueueElement*,HuffyManager::BitsUsedQueueElement* );
	static void CompressHuffyBaseType(const HuffyBaseType*);
	static void AddHuffyTypeToBitSet(int);
	static void ConstructUpdateFromIDList(
			std::list<std::string>,
			std::map<std::string, const HuffyBaseType* >,
			std::map<std::string, HuffyManager::e_HuffyTypes>
	);
	
private:
	//Member variables 

	enum e_BitSetValue 
	{
		e_ZERO = 0,
		e_ONE = 1
	};
	static void AddIntToUpdate(std::string, int,int);
	static void AddFloatToUpdate(std::string, int,float);
	static void AddBoolToUpdate(std::string, int,bool);
	static void WriteValueToBitset(int);

	static HuffyManager::TypeQueueElement* GetPointerToTypeInTypeTreeByType(int, HuffyManager::TypeQueueElement*);
	static void WriteIntToBuffer(int);
	static int ReadIntFromBuffer(void);
	static void writeInt(int,int);
	static int readInt(int);

	//Delete Tree's
	static void DeleteOldTrees();
	static void DeleteTypeQueueElementTree(HuffyManager::TypeQueueElement*);
	static void DeleteIDQueueElementTree(HuffyManager::IDQueueElement*);
	static void DeleteBitsUsedQueueElementTree(HuffyManager::BitsUsedQueueElement*);
	static HuffyManager::TypeQueueElement* m_TypeTreeRootNode;
	static HuffyManager::IDQueueElement* m_IntIDTreeRootNode;
	static HuffyManager::IDQueueElement* m_FloatIDTreeRootNode;
	static HuffyManager::IDQueueElement* m_BoolIDTreeRootNode;
	static HuffyManager::BitsUsedQueueElement* m_BitsUsedTreeRootNode;

};
