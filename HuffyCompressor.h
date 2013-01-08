#pragma once
#define BufferLimit 256
class HuffyCompressor
{
	
public:
	HuffyCompressor(void);
	~HuffyCompressor(void);
	static void HuffyCompressor::Init(std::string, int);
	static void HuffyCompressor::AddToSendList(std::string);
	static void HuffyCompressor::SendUpdate();
	static int HuffyCompressor::HowManyBitsToStoreThis(int);
	static int HuffyCompressor::HowManyBitsToStoreThis(float);
	static void HuffyCompressor::PassPointersToHuffyTreeRootNodes(HuffyManager::TypeQueueElement*,HuffyManager::IDQueueElement* ,HuffyManager::IDQueueElement* ,HuffyManager::IDQueueElement*,HuffyManager::BitsUsedQueueElement* );
	static void HuffyCompressor::CompressHuffyBaseType(const HuffyBaseType*);
	static void HuffyCompressor::AddHuffyTypeToBitSet(int);
	
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
	static HuffyManager::TypeQueueElement* HuffyCompressor::GetPointerToTypeInTypeTreeByType(int, HuffyManager::TypeQueueElement*);
	static void HuffyCompressor::WriteIntToBuffer(int);
	static int HuffyCompressor::ReadIntFromBuffer(void);
	static void HuffyCompressor::writeInt(int,int);
	static int HuffyCompressor::readInt(int);
	//Delete Tree's
	static void HuffyCompressor::DeleteOldTrees();
	static void HuffyCompressor::DeleteTypeQueueElementTree(HuffyManager::TypeQueueElement*);
	static void HuffyCompressor::DeleteIDQueueElementTree(HuffyManager::IDQueueElement*);
	static void HuffyCompressor::DeleteBitsUsedQueueElementTree(HuffyManager::BitsUsedQueueElement*);
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