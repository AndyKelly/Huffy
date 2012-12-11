#pragma once
#include <string>
#include "HuffyInt.h"
#include "HuffyBaseType.h"
#include "HuffyCompressor.h"
#include "PriorityQueueUtility.h"
#include <list>
#include <vector>
#include <map>
#include <queue>

class HuffyManager
{
public:
	//Todo, Consider replacing this, see: GetHuffyTypesPriorityQueue()
	static enum e_HuffyTypes 
	{
		e_HuffyInt = 0,
		e_HuffyFloat,
		e_HuffyVec2D,
		e_HuffyVec3D,
		e_HuffyString,
		e_HuffyBool,
		e_HuffyNonLeaf,
		e_MAX
	};

	//Todo m_TypeValue should be a generic T 
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

	class CompareElements 
	{
		public:
		bool operator()(TypeQueueElement& Q1, TypeQueueElement& Q2)
		{
			if (Q1.m_Frequency > Q2.m_Frequency) return true;
			return false;
		};
	};
	
	
	~HuffyManager(void);
	static void HuffyTypeModified(std::string, e_HuffyTypes);
	static void HuffyManager::RegisterHuffyIntAsSendable(std::string, const HuffyInt *);
	static std::priority_queue<TypeQueueElement, std::vector<TypeQueueElement>,CompareElements> HuffyManager::GetHuffyTypesPriorityQueue(void);
	static TypeQueueElement* HuffyManager::ConstructHuffyTypeTreeFromPriorityQueue(std::priority_queue<TypeQueueElement, std::vector<TypeQueueElement>,CompareElements>);
	static void HuffyManager::AssignParentPointersToTypeQueueElementTree(TypeQueueElement*);
	static void HuffyManager::ConstructHuffyTrees(void);
private:
	static void IncrementIDFrequencyMapByType(e_HuffyTypes, std::string);
	static std::map<std::string, const HuffyInt* > HuffyIntPtrMap;
	static std::map<e_HuffyTypes, long long > UsedTypeFrequencyMap;
	//Todo consider using smaller types?
	static std::map<std::string, long long > IntIDFrequencyMap;
	static std::map<std::string, long long > FloatIDFrequencyMap;
	static std::map<std::string, long long > StringIDFrequencyMap;
	static std::map<std::string, long long > BoolIDFrequencyMap;
	static std::map<std::string, long long > Vector2DIDFrequencyMap;
	static std::map<std::string, long long > Vector3DIDFrequencyMap;
	static std::map<int, int> BitsUsedFrequencyMap;
	static void HuffyManager::AddHuffyIntByIDToCompressor(std::string);
	HuffyManager(void);
};
