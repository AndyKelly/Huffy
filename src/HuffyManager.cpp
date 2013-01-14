/*
 * HuffyManager.cpp
 *
 *      Author: Andy Kelly
 */
#include "HuffyManager.h"
#include "HuffyCompressor.h"
#include "HuffyConstants.h"
#include "HuffyFloat.h"
#include "HuffyBool.h"
#include "HuffyPacker.h"
#include <list>
#include <iostream>
#include <string>
#include <list>
#include <bitset>
#include <map>
using namespace std;

//Init static member variables

HuffyClient HuffyManager::m_HuffyClient;
HuffyServer HuffyManager::m_HuffyServer;
bool HuffyManager::m_Initalised = false;
bool HuffyManager::m_IsServer = false; 
std::map<std::string, e_HuffyTypes > HuffyManager::m_ID_TypeMap;
std::map<std::string, const HuffyBaseType* > HuffyManager::HuffyPtrMap;
std::map<std::string, HuffyInt* > HuffyManager::HuffyIntPtrMap;
std::map<std::string, HuffyFloat* > HuffyManager::HuffyFloatPtrMap;
std::map<std::string, HuffyBool* > HuffyManager::HuffyBoolPtrMap;
std::map<e_HuffyTypes, long long > HuffyManager::UsedTypeFrequencyMap;
std::map<int, long long> HuffyManager::BitsUsedFrequencyMap;
std::map<std::string, long long > HuffyManager::IntIDFrequencyMap;
std::map<std::string, long long > HuffyManager::FloatIDFrequencyMap;
std::map<std::string, long long > HuffyManager::BoolIDFrequencyMap;
std::list<std::string> HuffyManager::m_ModifiedTypes;

HuffyManager::HuffyManager(void)
{
	//Todo, should be in a function.
	UsedTypeFrequencyMap[e_EndOfMessage] = 10;
	UsedTypeFrequencyMap[e_AdaptRequest] = 10;
	UsedTypeFrequencyMap[e_HuffyInt] = 10;
	UsedTypeFrequencyMap[e_HuffyFloat] = 10;
	UsedTypeFrequencyMap[e_HuffyBool] = 10;
	UsedTypeFrequencyMap[e_EndOfMessage] = 10;
	UsedTypeFrequencyMap[e_AdaptRequest] = 10;

	//Todo Needed?
	UsedTypeFrequencyMap[e_HuffyNonLeaf] = 1;
}

HuffyManager::~HuffyManager(void)
{
}

bool HuffyManager::Initalise(bool IsServer, string ServerAddress)
{

	ConstructHuffyTrees();
	if(IsServer)
	{
		m_IsServer = IsServer;
		if(m_HuffyServer.Initalise())
		{
			std::cout<< "\n\Server initalised\n";
			m_Initalised = true;
		}
	}
	else
	{
		m_IsServer = false;
		if(m_HuffyClient.Initalise(ServerAddress))
		{
			std::cout<< "\n\Client initalised\n";
			m_Initalised = true;
		}
	}
	return m_Initalised;
}

void HuffyManager::Update()
{
	UsedTypeFrequencyMap[e_EndOfMessage] += 1;
	if(m_Initalised)
	{
		if(m_IsServer)
		{
			//Send update to client
			std::cout << "\nConstructing and assigning update\n";
			m_HuffyServer.AssignUpdate(ConstructUpdate());
			m_HuffyServer.ServerWaitForClientToRequestUpdate();
		}
		else
		{
			std::cout << "\nRetriveing Update From Server";
			std::string Update = m_HuffyClient.RequestUpdate();
			std::cout << "\nRecieved update string:" << Update;
			ApplyUpdate(Update);
		}
	}
}

void HuffyManager::Adapt()
{
	UsedTypeFrequencyMap[e_AdaptRequest] += 1;
	ConstructHuffyTrees();
	HuffyCompressor::Adapt();
}

void HuffyManager::ApplyUpdate(std::string UpdateToApply)
{
	HuffyCompressor::ApplyUpdate(HuffyPtrMap,HuffyIntPtrMap,HuffyFloatPtrMap,HuffyBoolPtrMap, UpdateToApply);
}

std::string HuffyManager::ConstructUpdate()
{
	std::string Update = HuffyCompressor::ConstructUpdateFromIDList(m_ModifiedTypes,HuffyIntPtrMap,HuffyFloatPtrMap,HuffyBoolPtrMap,m_ID_TypeMap);
	//Wipe list for next update
	m_ModifiedTypes.clear();
	std::cout << "\nUpdate constructed:\n";

	return Update;
}

//Todo, How can we removed from the BitsUsed map correctly when a Types value is liable to change
//Figure this out for the next revision, for now lets just remove the pointer to the object and it's ID from the Map
void HuffyManager::RemoveType(std::string ID, e_HuffyTypes Type)
{
	UsedTypeFrequencyMap[Type] --;

	HuffyPtrMap.erase(ID);
	//Need a smart way of changing this, could be worth unit testing a few different approaches for performance
	//BitsUsedFrequencyMap;
	switch(Type)
	{
		case(e_HuffyInt):
		{
			IntIDFrequencyMap.erase(ID);
			break;
		}
		case(e_HuffyFloat):
		{
			FloatIDFrequencyMap.erase(ID);
			break;
		}
		case(e_HuffyBool):
		{
			BoolIDFrequencyMap.erase(ID);
			break;
		}

	}
}


void HuffyManager::ConstructHuffyTrees(void)
{
	std::cout<< "\nConstructing Huffy trees\n";
	TypeQueueElement* TypeTreeRootNode = ConstructHuffyTypeTreeFromPriorityQueue(GetHuffyTypesPriorityQueue());
	IDQueueElement* IntIDTreeRootNode = ConstructHuffyIDTreeFromPriorityQueue(GetIDPriorityQueueByType(e_HuffyInt));
	IDQueueElement* FloatIDTreeRootNode = ConstructHuffyIDTreeFromPriorityQueue(GetIDPriorityQueueByType(e_HuffyFloat));
	IDQueueElement* BoolIDTreeRootNode = ConstructHuffyIDTreeFromPriorityQueue(GetIDPriorityQueueByType(e_HuffyBool));
	BitsUsedQueueElement* BitsUsedTreeRootNode = ConstructHuffyBitsUsedTreeFromPriorityQueue(GetBitsUsedPriorityQueue());
	std::cout<< "\nPassing pointers to Huffy compressor\n";
	//Pass pointers to HuffyCompressor
	HuffyCompressor::PassPointersToHuffyTreeRootNodes(TypeTreeRootNode,IntIDTreeRootNode,FloatIDTreeRootNode,BoolIDTreeRootNode,BitsUsedTreeRootNode);
}

//Construct priority queues

priority_queue<TypeQueueElement, vector<TypeQueueElement>,CompareTypeElements> HuffyManager::GetHuffyTypesPriorityQueue()
{
	priority_queue<TypeQueueElement, vector<TypeQueueElement>,CompareTypeElements> TypesPQ;

	std::map<e_HuffyTypes, long long  >::iterator itr;

	for(itr = UsedTypeFrequencyMap.begin(); itr != UsedTypeFrequencyMap.end(); itr++)
	{
		TypesPQ.push(TypeQueueElement(itr->first, itr->second, NULL, NULL, NULL));
	}

	return TypesPQ;
}

priority_queue<IDQueueElement, vector<IDQueueElement>,CompareIDElements> HuffyManager::GetIDPriorityQueueByType(e_HuffyTypes MapToUse)
{
	priority_queue<IDQueueElement, vector<IDQueueElement>,CompareIDElements> IDPQ;
	std::map<std::string, long long >::iterator itr;

	switch(MapToUse)
	{
		case e_HuffyInt:
		{
			for(itr = IntIDFrequencyMap.begin(); itr != IntIDFrequencyMap.end(); itr++)
			{
				IDPQ.push(IDQueueElement(itr->first, itr->second, NULL, NULL, NULL));
			}
			break;
		}
		case e_HuffyFloat:
		{
			for(itr = FloatIDFrequencyMap.begin(); itr != FloatIDFrequencyMap.end(); itr++)
			{
				IDPQ.push(IDQueueElement(itr->first, itr->second, NULL, NULL, NULL));
			}
			break;
		}
		case e_HuffyBool:
		{
			for(itr = BoolIDFrequencyMap.begin(); itr != BoolIDFrequencyMap.end(); itr++)
			{
				IDPQ.push(IDQueueElement(itr->first, itr->second, NULL, NULL, NULL));
			}
			break;
		}
		default:
		{
			break;
		}

	}

	return IDPQ;
}

priority_queue<BitsUsedQueueElement, vector<BitsUsedQueueElement>,CompareBitsUsedElements> HuffyManager::GetBitsUsedPriorityQueue()
{
	priority_queue<BitsUsedQueueElement, vector<BitsUsedQueueElement>,CompareBitsUsedElements> BitsUsedPQ;
	std::map<int, long long>::iterator itr;

	for(itr = BitsUsedFrequencyMap.begin(); itr != BitsUsedFrequencyMap.end(); itr++)
	{
		BitsUsedPQ.push(BitsUsedQueueElement(itr->first, itr->second, NULL, NULL, NULL));
	}

	return BitsUsedPQ;
}

//Construct Huffy Trees

TypeQueueElement* HuffyManager::ConstructHuffyTypeTreeFromPriorityQueue(priority_queue<TypeQueueElement,
	vector<TypeQueueElement>,CompareTypeElements> Queue)
{
	if(Queue.size() <= 1)
	{
		std::cout<< "\nHuffyType tree is empty\n";
		return NULL;
	}
	//While there is more than one node in the queue:
	while(Queue.size() >= 2)
	{
		//Remove the two nodes of highest priority (lowest probability) from the queue
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

IDQueueElement* HuffyManager::ConstructHuffyIDTreeFromPriorityQueue(priority_queue<IDQueueElement,
	vector<IDQueueElement>,CompareIDElements> Queue)
{
	if(Queue.size() <= 1)
	{
		std::cout<< "\HuffyType tree is empty\n";
		return NULL;
	}
	//While there is more than one node in the queue:

	while(Queue.size() >= 2)
	{

		//Remove the two nodes of highest priority (lowest probability) from the queue
		IDQueueElement *Left = new IDQueueElement(
			Queue.top().m_ID,
			Queue.top().m_Frequency,
			Queue.top().m_LeftChild,
			Queue.top().m_RightChild,
			NULL);
		Queue.pop();



		IDQueueElement *Right = new IDQueueElement(
			Queue.top().m_ID,
			Queue.top().m_Frequency,
			Queue.top().m_LeftChild,
			Queue.top().m_RightChild,
			NULL);
		Queue.pop();


		//Create a new internal node with these two nodes as children and with probability equal to the sum of the two nodes' probabilities.
		//Note (Parents pointers are initalised as NULL)
		IDQueueElement Parent("", (Left->m_Frequency +  Right->m_Frequency), Left, Right, NULL);
		//Add the new node to the queue.
		Queue.push(Parent);


	}
	//The remaining node is the root node and the tree is complete.
	IDQueueElement *RootNode = new IDQueueElement(
		Queue.top().m_ID,
		Queue.top().m_Frequency,
		Queue.top().m_LeftChild,
		Queue.top().m_RightChild,
		NULL);
	Queue.pop();

	//Asign parent pointers
	AssignParentPointersToIDQueueElementTree(RootNode);
	return RootNode;
}

BitsUsedQueueElement* HuffyManager::ConstructHuffyBitsUsedTreeFromPriorityQueue(priority_queue<BitsUsedQueueElement,
	vector<BitsUsedQueueElement>,CompareBitsUsedElements> Queue)
{
	if(Queue.size() <= 1)
	{
		return NULL;
	}
	//While there is more than one node in the queue:
	while(Queue.size()  >= 2)
	{
		//Remove the two nodes of highest priority (lowest probability) from the queue
		BitsUsedQueueElement *Left = new BitsUsedQueueElement(
			Queue.top().m_BitsUsed,
			Queue.top().m_Frequency,
			Queue.top().m_LeftChild,
			Queue.top().m_RightChild,
			NULL);
		Queue.pop();
		BitsUsedQueueElement *Right = new BitsUsedQueueElement(
			Queue.top().m_BitsUsed,
			Queue.top().m_Frequency,
			Queue.top().m_LeftChild,
			Queue.top().m_RightChild,
			NULL);
		Queue.pop();

		//Create a new internal node with these two nodes as children and with probability equal to the sum of the two nodes' probabilities.
		//Note (Parents pointers are initalised as NULL)
		BitsUsedQueueElement Parent(NULL, (Left->m_Frequency +  Right->m_Frequency), Left, Right, NULL);
		Parent.m_LeftChild = Left;
		Parent.m_RightChild = Right;
		//Add the new node to the queue.
		Queue.push(Parent);
	}
	//The remaining node is the root node and the tree is complete.
	BitsUsedQueueElement *RootNode = new BitsUsedQueueElement(
		Queue.top().m_BitsUsed,
		Queue.top().m_Frequency,
		Queue.top().m_LeftChild,
		Queue.top().m_RightChild,
		NULL);
	Queue.pop();

	//Asign parent pointers
	AssignParentPointersToBitsUsedQueueElementTree(RootNode);
	return RootNode;
}

//Assign parent pointers to a huffy tree

void HuffyManager::AssignParentPointersToTypeQueueElementTree(TypeQueueElement* Parent)
{
	//Stop when a child is a leaf node
	if(Parent->m_LeftChild != NULL && Parent->m_RightChild != NULL)
	{
		Parent->m_LeftChild->m_Parent = Parent;
		Parent->m_RightChild->m_Parent = Parent;
		AssignParentPointersToTypeQueueElementTree(Parent->m_LeftChild);
		AssignParentPointersToTypeQueueElementTree(Parent->m_RightChild);
	}
}

void HuffyManager::AssignParentPointersToIDQueueElementTree(IDQueueElement* Parent)
{
	//Stop when a child is a leaf node
	if(Parent->m_LeftChild != NULL && Parent->m_RightChild != NULL)
	{
		Parent->m_LeftChild->m_Parent = Parent;
		Parent->m_RightChild->m_Parent = Parent;
		AssignParentPointersToIDQueueElementTree(Parent->m_LeftChild);
		AssignParentPointersToIDQueueElementTree(Parent->m_RightChild);
	}

}

void HuffyManager::AssignParentPointersToBitsUsedQueueElementTree(BitsUsedQueueElement* Parent)
{

	//Stop when a child is a leaf node
	if(Parent->m_LeftChild != NULL && Parent->m_RightChild != NULL)
	{
		Parent->m_LeftChild->m_Parent = Parent;
		Parent->m_RightChild->m_Parent = Parent;
		AssignParentPointersToBitsUsedQueueElementTree(Parent->m_LeftChild);
		AssignParentPointersToBitsUsedQueueElementTree(Parent->m_RightChild);
	}
}

//Map manipulation

void HuffyManager::HuffyTypeModified(e_HuffyTypes e_Type, string ID)
{
	IncrementIDFrequencyMapByType(e_Type, ID);
	IncrementBitsUsedFrequencyMapByType(e_Type, ID);

	m_ModifiedTypes.push_front(ID);
	m_ID_TypeMap[ID] = e_Type;

	//Check if map entry exists, if not init, else increment
	if(UsedTypeFrequencyMap.find(e_Type) == UsedTypeFrequencyMap.end())
	{
		UsedTypeFrequencyMap[e_Type] = 0;
	}
	else
	{
		UsedTypeFrequencyMap[e_Type]++;
	}

}

void HuffyManager::IncrementBitsUsedFrequencyMapByType(e_HuffyTypes e_Type, string ID)
{

	int BitsUsed = 0;
	const HuffyBaseType* TempBasePointer = HuffyPtrMap[ID];

	try
	{
		switch(e_Type)
		{
			case e_HuffyInt:
			{
				const HuffyInt* HuffyIntPointer = reinterpret_cast<const HuffyInt*>(TempBasePointer) ;
				BitsUsed = HuffyCompressor::HowManyBitsToStoreThis(HuffyIntPointer->GetValue_C());
				break;
			}
			case e_HuffyFloat:
			{
				const HuffyFloat* HuffyFloatPointer = reinterpret_cast<const HuffyFloat*>(TempBasePointer) ;
				BitsUsed = HuffyCompressor::HowManyBitsToStoreThis(HuffyFloatPointer->GetValue_C());
				break;
			}
			case e_HuffyBool:
			{
				//Only takes one bit to store a bool
				BitsUsed = 1;
				break;
			}
		}

	}
    catch (...)
    {
		//Todo some way of logging this error
    }

	//Check if map entry exists, if not init, else increment
	if(BitsUsedFrequencyMap.find(BitsUsed) == BitsUsedFrequencyMap.end())
	{
		BitsUsedFrequencyMap[BitsUsed] = 0;
	}
	else
	{
		BitsUsedFrequencyMap[BitsUsed]++;
	}
}

void HuffyManager::IncrementIDFrequencyMapByType(e_HuffyTypes TypeToIncrement, std::string IDToIncrement)
{
	//Check if map entry exists, if not init, else increment
	switch (TypeToIncrement)
	{
		case e_HuffyBool:
		{
			if(BoolIDFrequencyMap.find(IDToIncrement) == BoolIDFrequencyMap.end())
			{
				BoolIDFrequencyMap[IDToIncrement] = (long long)10;

			}
			else
			{
				BoolIDFrequencyMap[IDToIncrement]++;
			}
			break;
		}
		case e_HuffyInt:
			if(IntIDFrequencyMap.find(IDToIncrement) == IntIDFrequencyMap.end())
			{

				IntIDFrequencyMap[IDToIncrement] = (long long)10;
			}
			else
			{
				IntIDFrequencyMap[IDToIncrement]+=1;
			}
			break;
		case e_HuffyFloat:
			if(FloatIDFrequencyMap.find(IDToIncrement) == FloatIDFrequencyMap.end())
			{
				FloatIDFrequencyMap[IDToIncrement] = (long long)10;
			}
			else
			{
				FloatIDFrequencyMap[IDToIncrement]++;
			}
			break;
	}
}

void HuffyManager::RegisterHuffyTypeObject(string m_HuffyID, const HuffyBaseType* SendableHuffyTypeObject)
{
	HuffyManager::HuffyPtrMap[m_HuffyID] = SendableHuffyTypeObject;
	//m_ModifiedTypes.push_front(m_HuffyID);
}

void HuffyManager::RegisterHuffyIntObject(string m_HuffyID, HuffyInt* SendableHuffyTypeObject)
{
	HuffyTypeModified(e_HuffyInt, m_HuffyID);
	HuffyManager::HuffyIntPtrMap[m_HuffyID] = SendableHuffyTypeObject;
}

void HuffyManager::RegisterHuffyFloatObject(string m_HuffyID, HuffyFloat* SendableHuffyTypeObject)
{
	HuffyTypeModified(e_HuffyFloat, m_HuffyID);
	HuffyManager::HuffyFloatPtrMap[m_HuffyID] = SendableHuffyTypeObject;
}

void HuffyManager::RegisterHuffyBoolObject(string m_HuffyID, HuffyBool* SendableHuffyTypeObject)
{
	HuffyTypeModified(e_HuffyBool, m_HuffyID);
	HuffyManager::HuffyBoolPtrMap[m_HuffyID] = SendableHuffyTypeObject;
}
