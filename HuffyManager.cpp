#include "StdAfx.h"
#include "HuffyManager.h"
#include "HuffyCompressor.h"
#include <string>
#include <list>
#include <map>
//Todo, do we need includes in header and source?
using namespace std;

//Init static member variables
std::map<std::string, const HuffyInt* > HuffyManager::HuffyIntPtrMap;//Todo should be pointers to a base class
std::map<HuffyManager::e_HuffyTypes, long long > HuffyManager::UsedTypeFrequencyMap;
std::map<int, int> HuffyManager::BitsUsedFrequencyMap;
std::map<std::string, long long > HuffyManager::IntIDFrequencyMap;
std::map<std::string, long long > HuffyManager::FloatIDFrequencyMap;
std::map<std::string, long long > HuffyManager::StringIDFrequencyMap;
std::map<std::string, long long > HuffyManager::BoolIDFrequencyMap;
std::map<std::string, long long > HuffyManager::Vector2DIDFrequencyMap;
std::map<std::string, long long > HuffyManager::Vector3DIDFrequencyMap;



//Todo, should be a singleton
HuffyManager::HuffyManager(void)
{
}


HuffyManager::~HuffyManager(void)
{
	//Todo correctly delete huffy trees
}

void HuffyManager::ConstructHuffyTrees(void)
{
	TypeQueueElement* RootNode = ConstructHuffyTypeTreeFromPriorityQueue(GetHuffyTypesPriorityQueue());
	if(RootNode != NULL)
	{

	}
}

priority_queue<HuffyManager::TypeQueueElement, vector<HuffyManager::TypeQueueElement>,HuffyManager::CompareElements> HuffyManager::GetHuffyTypesPriorityQueue()
{
	priority_queue<TypeQueueElement, vector<TypeQueueElement>,CompareElements> TypesPQ;

	//Todo, dont like this, depends on enum type starting with 0 and having an increment of 1. Consider rewriting this
	for(int i=0; i < e_HuffyTypes::e_MAX; i++)
	{
		e_HuffyTypes eCurrent = (HuffyManager::e_HuffyTypes) i;
		//Check to see if type has been used/is present in the frequency map, if so add to queue
		if(UsedTypeFrequencyMap.find(eCurrent) != UsedTypeFrequencyMap.end()) 
		{
			TypesPQ.push(TypeQueueElement(eCurrent , UsedTypeFrequencyMap[eCurrent], NULL, NULL, NULL));
		}
	}

	return TypesPQ;
}

HuffyManager::TypeQueueElement* HuffyManager::ConstructHuffyTypeTreeFromPriorityQueue(priority_queue<HuffyManager::TypeQueueElement,
	vector<HuffyManager::TypeQueueElement>,HuffyManager::CompareElements> Queue)
{
	//Todo, verify that a Queue has more than 1 element present
	if(Queue.size() < 2)
	{
		return NULL;
	}
	//While there is more than one node in the queue:
	while(!Queue.size() > 1)
	{
		//Remove the two nodes of highest priority (lowest probability) from the queue
		//Todo consider splitting up this line, is there much of an overhead for Queue.Top() ?
		TypeQueueElement *Left = new TypeQueueElement(
			Queue.top().m_TypeValue,
			Queue.top().m_Frequency,
			Queue.top().m_LeftChild,
			Queue.top().m_RightChild,
			NULL);
		Queue.pop();
		TypeQueueElement *Right = new TypeQueueElement(
			Queue.top().m_TypeValue,
			Queue.top().m_Frequency,
			Queue.top().m_LeftChild,
			Queue.top().m_RightChild,
			NULL);
		Queue.pop();

		//Create a new internal node with these two nodes as children and with probability equal to the sum of the two nodes' probabilities.
		//Note (Parents pointers are initalised as NULL)
		TypeQueueElement Parent(e_HuffyNonLeaf, (Left->m_Frequency +  Right->m_Frequency), Left, Right, NULL);
		Parent.m_LeftChild = Left;
		Parent.m_RightChild = Right;

		//Add the new node to the queue.
		Queue.push(Parent);
	}

	//The remaining node is the root node and the tree is complete.
	TypeQueueElement *RootNode = new TypeQueueElement(
		Queue.top().m_TypeValue,
		Queue.top().m_Frequency,
		Queue.top().m_LeftChild,
		Queue.top().m_RightChild,
		NULL);
	Queue.pop();

	//Asign parent pointers
	AssignParentPointersToTypeQueueElementTree(RootNode);

	return RootNode;
}

void HuffyManager::AssignParentPointersToTypeQueueElementTree(TypeQueueElement* Parent)
{
	Parent->m_LeftChild->m_Parent = Parent;
	Parent->m_RightChild->m_Parent = Parent;

	//Stop when a child is a leaf node
	//Todo, wont work when a node has only one child. Will this ever happen?
	if(Parent->m_LeftChild != NULL && Parent->m_RightChild != NULL)
	{
		AssignParentPointersToTypeQueueElementTree(Parent->m_LeftChild);
		AssignParentPointersToTypeQueueElementTree(Parent->m_RightChild);
	}
}

void HuffyManager::HuffyTypeModified(string ID, e_HuffyTypes e_Type)
{
	//Todo clean this up
	//Check if map entry exists, if not init, else increment
	IncrementIDFrequencyMapByType(e_Type, ID);

	//Check if map entry exists, if not init, else increment
	if(UsedTypeFrequencyMap.find(e_HuffyInt) == UsedTypeFrequencyMap.end()) 
	{
		UsedTypeFrequencyMap[e_HuffyInt] = 0;
	}
	else 
	{
		UsedTypeFrequencyMap[e_HuffyInt]++;
	}

	//Check if map entry exists, if not init, else increment
	////Ask compressor how many bits are used
	int BitsUsed = HuffyCompressor::HowManyBitsToStoreThis(HuffyManager::HuffyIntPtrMap[ID]->GetValue_C());
	if(BitsUsedFrequencyMap.find(BitsUsed) == BitsUsedFrequencyMap.end()) 
	{
		BitsUsedFrequencyMap[BitsUsed] = 0;
	}
	else 
	{
		BitsUsedFrequencyMap[BitsUsed]++;
	}

	AddHuffyIntByIDToCompressor(ID);

}

void HuffyManager::IncrementIDFrequencyMapByType(HuffyManager::e_HuffyTypes TypeToIncrement, string IDToIncrement)
{
	//Check if map entry exists, if not init, else increment
	//Todo, similar logic here, bad code smell, fix it
	switch (TypeToIncrement) 
	{
		case e_HuffyBool:
			if(BoolIDFrequencyMap.find(IDToIncrement) == IntIDFrequencyMap.end()) 
			{
				BoolIDFrequencyMap[IDToIncrement] = 0;
			}
			else 
			{
				BoolIDFrequencyMap[IDToIncrement]++;
			}
			break;
		case e_HuffyInt:
			if(IntIDFrequencyMap.find(IDToIncrement) == IntIDFrequencyMap.end()) 
			{
				IntIDFrequencyMap[IDToIncrement] = 0;
			}
			else 
			{
				IntIDFrequencyMap[IDToIncrement]++;
			}
			break;
		case e_HuffyFloat:
			if(FloatIDFrequencyMap.find(IDToIncrement) == FloatIDFrequencyMap.end()) 
			{
				FloatIDFrequencyMap[IDToIncrement] = 0;
			}
			else 
			{
				FloatIDFrequencyMap[IDToIncrement]++;
			}
			break;
		case e_HuffyVec2D:
			if(Vector2DIDFrequencyMap.find(IDToIncrement) == Vector2DIDFrequencyMap.end()) 
			{
				Vector2DIDFrequencyMap[IDToIncrement] = 0;
			}
			else 
			{
				Vector2DIDFrequencyMap[IDToIncrement]++;
			}
			break;
		case e_HuffyVec3D:
			if(Vector3DIDFrequencyMap.find(IDToIncrement) == Vector3DIDFrequencyMap.end()) 
			{
				Vector3DIDFrequencyMap[IDToIncrement] = 0;
			}
			else 
			{
				Vector3DIDFrequencyMap[IDToIncrement]++;
			}
			break;
		case e_HuffyString:
			if(StringIDFrequencyMap.find(IDToIncrement) == StringIDFrequencyMap.end()) 
			{
				StringIDFrequencyMap[IDToIncrement] = 0;
			}
			else 
			{
				StringIDFrequencyMap[IDToIncrement]++;
			}
			break;
	}
}

//Todo, refactor to use a common base class between types
void HuffyManager::RegisterHuffyIntAsSendable(string m_HuffyID, const HuffyInt* SendableHuffyInt)
{
	HuffyManager::HuffyIntPtrMap[m_HuffyID] = SendableHuffyInt;
}

//Todo refactor for each type using templates?
void HuffyManager::AddHuffyIntByIDToCompressor(string ID)
{
	//Figure out types here
	HuffyCompressor::AddIntToOutStream(HuffyManager::HuffyIntPtrMap[ID]->GetValue_C());
}