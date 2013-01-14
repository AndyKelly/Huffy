#pragma once
#define BufferLimit 256
#include <string>
#include <list>
#include <bitset>
#include <map>
#include <math.h>
#include <string>
#include "ServerSocket.h"
#include "SocketException.h"
#include "HuffyConstants.h"
#include "HuffyPacker.h"
#include "TreeUtility.h"
#include "ClientSocket.h"
#include "HuffyTreeManager.h"
class HuffyCompressor
{
	
public:
	HuffyCompressor(void);
	~HuffyCompressor(void);
	static bool Initalise(std::string, int, bool);
	static std::string GetUpdate();
	static void ApplyUpdate(std::map<std::string, const HuffyBaseType* >,
			std::map<std::string, HuffyInt* >,
			std::map<std::string, HuffyFloat* >,
			std::map<std::string, HuffyBool* >,
			std::string);
	static void Adapt(void);
	static int HowManyBitsToStoreThis(int);
	static int HowManyBitsToStoreThis(float);
	static void CompressHuffyBaseType(const HuffyBaseType*);
	static void AddHuffyTypeToBitSet(int);
	static void PassPointersToHuffyTreeRootNodes(TypeQueueElement*,IDQueueElement* ,IDQueueElement* ,IDQueueElement*,BitsUsedQueueElement* );

	static std::string ConstructUpdateFromIDList(
			std::list<std::string>,
			std::map<std::string, HuffyInt* >,
			std::map<std::string, HuffyFloat* >,
			std::map<std::string, HuffyBool* >,
			std::map<std::string, e_HuffyTypes>
			);
	
private:
	//Member variables 
	static HuffyTreeManager m_TreeManager;
	static bool m_Adapted;
	static HuffyPacker m_Packer;
	static void AddIntToUpdate(std::string,int);
	static void AddFloatToUpdate(std::string,float);
	static void AddBoolToUpdate(std::string, bool);
	static void WriteValueToBitset(int);
	static std::string TrimStringToIndex_Inclusive(std::string,int);


};
