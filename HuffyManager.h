#pragma once
#include <string>
#include "HuffyInt.h"
#include "HuffyBaseType.h"
#include <list>
#include <vector>
#include <map>
#include <queue>

class HuffyManager
{
public:
	
	enum e_HuffyTypes 
	{
		e_HuffyNonLeaf = NULL,
		e_HuffyInt,
		e_HuffyFloat,
		e_HuffyBool,
	};
	struct TypeQueueElement
	{
		TypeQueueElement(e_HuffyTypes TypeValue,
			int Frequency,
			TypeQueueElement* LeftChild,
			TypeQueueElement* RightChild,
			TypeQueueElement* Parent)
		{
			m_TypeValue = TypeValue;
			m_Frequency = Frequency;
			m_LeftChild = LeftChild;
			m_RightChild = RightChild;
			m_Parent = Parent;
		}

		e_HuffyTypes m_TypeValue;
		int m_Frequency;
		TypeQueueElement* m_LeftChild;
		TypeQueueElement* m_RightChild;
		TypeQueueElement* m_Parent;
	};
	struct IDQueueElement
	{
		IDQueueElement(std::string ID,
			int Frequency,
			IDQueueElement* LeftChild,
			IDQueueElement* RightChild,
			IDQueueElement* Parent)
		{
			m_ID = ID;
			m_Frequency = Frequency;
			m_LeftChild = LeftChild;
			m_RightChild = RightChild;
			m_Parent = Parent;
		}

		std::string m_ID;
		int m_Frequency;
		IDQueueElement* m_LeftChild;
		IDQueueElement* m_RightChild;
		IDQueueElement* m_Parent;
	};
	struct BitsUsedQueueElement
	{
		BitsUsedQueueElement(int BitsUsed,
			int Frequency,
			BitsUsedQueueElement* LeftChild,
			BitsUsedQueueElement* RightChild,
			BitsUsedQueueElement* Parent)
		{
			m_BitsUsed = BitsUsed;
			m_Frequency = Frequency;
			m_LeftChild = LeftChild;
			m_RightChild = RightChild;
			m_Parent = Parent;
		}

		int m_BitsUsed;
		int m_Frequency;
		BitsUsedQueueElement* m_LeftChild;
		BitsUsedQueueElement* m_RightChild;
		BitsUsedQueueElement* m_Parent;
	};

	

	static void Initalise(bool, std::string, int);
	static void Adapt();
	static void Update();

	~HuffyManager(void);
	static void HuffyTypeModified(e_HuffyTypes, std::string);
	static void HuffyManager::RegisterHuffyTypeObject(std::string, const HuffyBaseType *);
private:

	class CompareTypeElements 
	{
		public:
		bool operator()(TypeQueueElement& Q1, TypeQueueElement& Q2)
		{
			if (Q1.m_Frequency > Q2.m_Frequency) return true;
			return false;
		};
	};
	class CompareIDElements 
	{
		public:
		bool operator()(IDQueueElement& Q1, IDQueueElement& Q2)
		{
			if (Q1.m_Frequency > Q2.m_Frequency) return true;
			return false;
		};
	};
	class CompareBitsUsedElements 
	{
		public:
		bool operator()(BitsUsedQueueElement& Q1, BitsUsedQueueElement& Q2)
		{
			if (Q1.m_Frequency > Q2.m_Frequency) return true;
			return false;
		};
	};

	static bool m_Initalised;
	static bool m_IsServer; 
	
	static void SendPriorityQueues();

	
	//Construct Huffman trees, send them to the compressor
	static void HuffyManager::ConstructHuffyTrees(void);

	//Map manipulation
	static void IncrementIDFrequencyMapByType(e_HuffyTypes, std::string);
	static void IncrementBitsUsedFrequencyMapByType(e_HuffyTypes, std::string);

	//Huffy types base class pointer map
	static std::map<std::string, const HuffyBaseType* > HuffyPtrMap;
	
	//Frequency maps
	static std::map<e_HuffyTypes, long long > UsedTypeFrequencyMap;
	static std::map<std::string, long long > IntIDFrequencyMap;
	static std::map<std::string, long long > FloatIDFrequencyMap;
	static std::map<std::string, long long > BoolIDFrequencyMap;
	static std::map<int, long long> BitsUsedFrequencyMap;

	//PriorityQueue Constructors
	static std::priority_queue<TypeQueueElement, std::vector<TypeQueueElement>,CompareTypeElements> HuffyManager::GetHuffyTypesPriorityQueue(void);
	static std::priority_queue<IDQueueElement, std::vector<IDQueueElement>,CompareIDElements> HuffyManager::GetIDPriorityQueueByType(e_HuffyTypes);
	static std::priority_queue<BitsUsedQueueElement, std::vector<BitsUsedQueueElement>,CompareBitsUsedElements> HuffyManager::GetBitsUsedPriorityQueue(void);

	//HuffyTree Constructors
	static TypeQueueElement* HuffyManager::ConstructHuffyTypeTreeFromPriorityQueue(std::priority_queue<TypeQueueElement, std::vector<TypeQueueElement>,CompareTypeElements>);
	static IDQueueElement* HuffyManager::ConstructHuffyIDTreeFromPriorityQueue(std::priority_queue<IDQueueElement, std::vector<IDQueueElement>,CompareIDElements>);
	static BitsUsedQueueElement* HuffyManager::ConstructHuffyBitsUsedTreeFromPriorityQueue(std::priority_queue<BitsUsedQueueElement, std::vector<BitsUsedQueueElement>,CompareBitsUsedElements>);
	
	//Backwards link Huffy trees
	static void HuffyManager::AssignParentPointersToTypeQueueElementTree(TypeQueueElement*);
	static void HuffyManager::AssignParentPointersToIDQueueElementTree(IDQueueElement*);
	static void HuffyManager::AssignParentPointersToBitsUsedQueueElementTree(BitsUsedQueueElement*);
	
	static void HuffyManager::AddToCompressorSendList(std::string);
	HuffyManager(void);
};
