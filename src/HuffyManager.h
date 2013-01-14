/*
 * HuffyManager.h
 *
 *      Author: Andy Kelly
 */
#pragma once
#include <string>
#include "HuffyInt.h"
#include "HuffyBaseType.h"
#include "HuffyServer.h"
#include "HuffyClient.h"
#include "HuffyConstants.h"
#include "TreeUtility.h"
#include "HuffyInt.h"
#include "HuffyFloat.h"
#include "HuffyBool.h"
#include <list>
#include <vector>
#include <map>
#include <queue>

class HuffyManager
{
public:
	static bool Initalise(bool, std::string);
	static void Adapt();
	static void Update();

	~HuffyManager(void);
	static void HuffyTypeModified(e_HuffyTypes, std::string);
	static void RegisterHuffyTypeObject(std::string, const HuffyBaseType *);
	static void RegisterHuffyIntObject(std::string , HuffyInt* );
	static void RegisterHuffyFloatObject(std::string , HuffyFloat*);
	static void RegisterHuffyBoolObject(std::string , HuffyBool*);
	static void RemoveType(std::string, e_HuffyTypes);
private:


	static bool m_Initalised;
	static bool m_IsServer; 
	static HuffyClient m_HuffyClient;
	static HuffyServer m_HuffyServer;
	//Modified types ID list
	static std::list<std::string> m_ModifiedTypes;

	static void ApplyUpdate(std::string);
	static std::string ConstructUpdate();
	
	//Construct Huffman trees, send them to the compressor
	static void ConstructHuffyTrees(void);

	//Map manipulation
	static void IncrementIDFrequencyMapByType(e_HuffyTypes, std::string);
	static void IncrementBitsUsedFrequencyMapByType(e_HuffyTypes, std::string);

	//Huffy types base class pointer map
	static std::map<std::string, const HuffyBaseType* > HuffyPtrMap;
	static std::map<std::string, HuffyInt* > HuffyIntPtrMap;
	static std::map<std::string, HuffyFloat* > HuffyFloatPtrMap;
	static std::map<std::string, HuffyBool* > HuffyBoolPtrMap;
	//Type association map
	static std::map<std::string,e_HuffyTypes > m_ID_TypeMap;

	//Frequency maps
	static std::map<e_HuffyTypes, long long > UsedTypeFrequencyMap;
	static std::map<std::string, long long > IntIDFrequencyMap;
	static std::map<std::string, long long > FloatIDFrequencyMap;
	static std::map<std::string, long long > BoolIDFrequencyMap;
	static std::map<int, long long> BitsUsedFrequencyMap;

	//PriorityQueue Constructors
	static std::priority_queue<TypeQueueElement, std::vector<TypeQueueElement>,CompareTypeElements> GetHuffyTypesPriorityQueue(void);
	static std::priority_queue<IDQueueElement, std::vector<IDQueueElement>,CompareIDElements> GetIDPriorityQueueByType(e_HuffyTypes);
	static std::priority_queue<BitsUsedQueueElement, std::vector<BitsUsedQueueElement>,CompareBitsUsedElements> GetBitsUsedPriorityQueue(void);

	//HuffyTree Constructors
	static TypeQueueElement* ConstructHuffyTypeTreeFromPriorityQueue(std::priority_queue<TypeQueueElement, std::vector<TypeQueueElement>,CompareTypeElements>);
	static IDQueueElement* ConstructHuffyIDTreeFromPriorityQueue(std::priority_queue<IDQueueElement, std::vector<IDQueueElement>,CompareIDElements>);
	static BitsUsedQueueElement* ConstructHuffyBitsUsedTreeFromPriorityQueue(std::priority_queue<BitsUsedQueueElement, std::vector<BitsUsedQueueElement>,CompareBitsUsedElements>);

	//Backwards link Huffy trees
	static void AssignParentPointersToTypeQueueElementTree(TypeQueueElement*);
	static void AssignParentPointersToIDQueueElementTree(IDQueueElement*);
	static void AssignParentPointersToBitsUsedQueueElementTree(BitsUsedQueueElement*);
	HuffyManager(void);
};
