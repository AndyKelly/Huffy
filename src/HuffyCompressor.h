#pragma once
#define BufferLimit 256
#include <string>
#include <list>
#include <bitset>
#include <map>
#include <math.h>
class HuffyCompressor
{
	
public:
	HuffyCompressor(void);
	~HuffyCompressor(void);
	static void Init(std::string, int);
	static void AddToSendList(std::string);
	static void SendUpdate();
	static int HowManyBitsToStoreThis(int);
	static int HowManyBitsToStoreThis(float);
	static void SendPriorityQueuesUpdate(std::priority_queue<HuffyManager::TypeQueueElement, std::vector<HuffyManager::TypeQueueElement>,HuffyManager::CompareTypeElements>,
			std::priority_queue<HuffyManager::IDQueueElement, std::vector<HuffyManager::IDQueueElement>,HuffyManager::CompareIDElements> ,
			std::priority_queue<HuffyManager::IDQueueElement, std::vector<HuffyManager::IDQueueElement>,HuffyManager::CompareIDElements> ,
			std::priority_queue<HuffyManager::IDQueueElement, std::vector<HuffyManager::IDQueueElement>,HuffyManager::CompareIDElements> ,
			std::priority_queue<HuffyManager::BitsUsedQueueElement, std::vector<HuffyManager::BitsUsedQueueElement>,HuffyManager::CompareBitsUsedElements>);
	static void PassPointersToHuffyTreeRootNodes(HuffyManager::TypeQueueElement*,HuffyManager::IDQueueElement* ,HuffyManager::IDQueueElement* ,HuffyManager::IDQueueElement*,HuffyManager::BitsUsedQueueElement* );
	static void CompressHuffyBaseType(const HuffyBaseType*);
	static void AddHuffyTypeToBitSet(int);
	
private:
	//Member variables 
	static std::string m_ClientAddress;
	static int m_PortNum;
	static bool m_InitalisedAsServer;

	enum e_BitSetValue 
	{
		e_ZERO = 0,
		e_ONE = 1
	};
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
	static int CurrentBit;
	static int CurrentByte;
	static int CurrentReadBit;
	static int CurrentReadByte;
	static unsigned char Buffer[BufferLimit]; 
};
