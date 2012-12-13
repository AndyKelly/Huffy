#pragma once
#define BufferLimit 256
class HuffyCompressor
{
	
public:
	HuffyCompressor(void);
	~HuffyCompressor(void);
	static void HuffyCompressor::AddIntToOutStream(int);
	static int HuffyCompressor::HowManyBitsToStoreThis(int);
	static int HuffyCompressor::HowManyBitsToStoreThis(float);
	static void HuffyCompressor::PassPointersToHuffyTreeRootNodes(HuffyManager::TypeQueueElement*,HuffyManager::IDQueueElement* ,HuffyManager::IDQueueElement* ,HuffyManager::IDQueueElement*,HuffyManager::BitsUsedQueueElement* );
private:
	static void HuffyCompressor::WriteIntToBuffer(int);
	static int HuffyCompressor::ReadIntFromBuffer(void);
	static void HuffyCompressor::writeInt(int,int);
	static int HuffyCompressor::readInt(int);
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