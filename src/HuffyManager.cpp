#include "HuffyManager.h"
#include "HuffyCompressor.h"
#include "HuffyFloat.h"
#include "HuffyBool.h"
#include <string>
#include <list>
#include <bitset>
#include <map>
using namespace std;

//Init static member variables
bool HuffyManager::m_Initalised = false;
bool HuffyManager::m_IsServer = false; 
std::map<std::string, const HuffyBaseType* > HuffyManager::HuffyPtrMap;
std::map<HuffyManager::e_HuffyTypes, long long > HuffyManager::UsedTypeFrequencyMap;
std::map<int, long long> HuffyManager::BitsUsedFrequencyMap;
std::map<std::string, long long > HuffyManager::IntIDFrequencyMap;
std::map<std::string, long long > HuffyManager::FloatIDFrequencyMap;
std::map<std::string, long long > HuffyManager::BoolIDFrequencyMap;

HuffyManager::HuffyManager(void)
{
}

HuffyManager::~HuffyManager(void)
{
}

void HuffyManager::Initalise(bool IsServer, string ClientAddress, int PortNumber)
{
	m_Initalised = true;
	ConstructHuffyTrees();
	if(IsServer)
	{
		m_IsServer = true;
		HuffyCompressor::Init(ClientAddress,PortNumber);
		SendPriorityQueues();
	}
	else
	{
		m_IsServer = false;
		//Todo in a loop?
		//HuffyCompressor::ListenOn(PortNumber);
	}
}

void HuffyManager::Update()
{
	if(m_Initalised)
	{
		if(m_IsServer)
		{
			//Send update to client
			HuffyCompressor::SendUpdate();

			//std::map<std::string, const HuffyBaseType* >::iterator itr;
			//for(itr = HuffyPtrMap.begin(); itr != HuffyPtrMap.end(); itr++)
			//{
			//	HuffyCompressor::CompressHuffyBaseType(itr->second);
			//}
		}
		else
		{
			//Apply recieved updates
			//If so apply it
		}
	}
}

void HuffyManager::SendPriorityQueues()
{
	HuffyCompressor::SendPriorityQueuesUpdate(GetHuffyTypesPriorityQueue(),
	GetIDPriorityQueueByType(e_HuffyInt),
	GetIDPriorityQueueByType(e_HuffyFloat),
	GetIDPriorityQueueByType(e_HuffyBool),
	GetBitsUsedPriorityQueue());
}

void HuffyManager::Adapt()
{
	//Create new Huffy tree's
	ConstructHuffyTrees();
	//Update the client
	SendPriorityQueues();
}

void HuffyManager::ConstructHuffyTrees(void)
{
	TypeQueueElement* TypeTreeRootNode = ConstructHuffyTypeTreeFromPriorityQueue(GetHuffyTypesPriorityQueue());
	IDQueueElement* IntIDTreeRootNode = ConstructHuffyIDTreeFromPriorityQueue(GetIDPriorityQueueByType(e_HuffyInt));
	IDQueueElement* FloatIDTreeRootNode = ConstructHuffyIDTreeFromPriorityQueue(GetIDPriorityQueueByType(e_HuffyFloat));
	IDQueueElement* BoolIDTreeRootNode = ConstructHuffyIDTreeFromPriorityQueue(GetIDPriorityQueueByType(e_HuffyBool));
	BitsUsedQueueElement* BitsUsedTreeRootNode = ConstructHuffyBitsUsedTreeFromPriorityQueue(GetBitsUsedPriorityQueue());

	//Pass pointers to HuffyCompressor
	HuffyCompressor::PassPointersToHuffyTreeRootNodes(TypeTreeRootNode,IntIDTreeRootNode,FloatIDTreeRootNode,BoolIDTreeRootNode,BitsUsedTreeRootNode);
}

//Construct priority queues

priority_queue<HuffyManager::TypeQueueElement, vector<HuffyManager::TypeQueueElement>,HuffyManager::CompareTypeElements> HuffyManager::GetHuffyTypesPriorityQueue()
{
	priority_queue<TypeQueueElement, vector<TypeQueueElement>,CompareTypeElements> TypesPQ;

	std::map<e_HuffyTypes, long long  >::iterator itr;

	for(itr = UsedTypeFrequencyMap.begin(); itr != UsedTypeFrequencyMap.end(); itr++)
	{
		TypesPQ.push(TypeQueueElement(itr->first, itr->second, NULL, NULL, NULL));
	}
	
	return TypesPQ;
}

priority_queue<HuffyManager::IDQueueElement, vector<HuffyManager::IDQueueElement>,HuffyManager::CompareIDElements> HuffyManager::GetIDPriorityQueueByType(e_HuffyTypes MapToUse)
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

priority_queue<HuffyManager::BitsUsedQueueElement, vector<HuffyManager::BitsUsedQueueElement>,HuffyManager::CompareBitsUsedElements> HuffyManager::GetBitsUsedPriorityQueue()
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

HuffyManager::TypeQueueElement* HuffyManager::ConstructHuffyTypeTreeFromPriorityQueue(priority_queue<HuffyManager::TypeQueueElement,
	vector<HuffyManager::TypeQueueElement>,HuffyManager::CompareTypeElements> Queue)
{
	if(Queue.size() <= 1)
	{
		return NULL;
	}
	//While there is more than one node in the queue:
	while(!Queue.size() > 1)
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

HuffyManager::IDQueueElement* HuffyManager::ConstructHuffyIDTreeFromPriorityQueue(priority_queue<HuffyManager::IDQueueElement,
	vector<HuffyManager::IDQueueElement>,HuffyManager::CompareIDElements> Queue)
{
	if(Queue.size() <= 1)
	{
		return NULL;
	}
	//While there is more than one node in the queue:
	while(!Queue.size() > 1)
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
		IDQueueElement Parent(NULL, (Left->m_Frequency +  Right->m_Frequency), Left, Right, NULL);
		Parent.m_LeftChild = Left;
		Parent.m_RightChild = Right;

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

HuffyManager::BitsUsedQueueElement* HuffyManager::ConstructHuffyBitsUsedTreeFromPriorityQueue(priority_queue<HuffyManager::BitsUsedQueueElement,
	vector<HuffyManager::BitsUsedQueueElement>,HuffyManager::CompareBitsUsedElements> Queue)
{
	if(Queue.size() <= 1)
	{
		return NULL;
	}
	//While there is more than one node in the queue:
	while(!Queue.size() > 1)
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
	Parent->m_LeftChild->m_Parent = Parent;
	Parent->m_RightChild->m_Parent = Parent;

	//Stop when a child is a leaf node
	if(Parent->m_LeftChild != NULL && Parent->m_RightChild != NULL)
	{
		AssignParentPointersToIDQueueElementTree(Parent->m_LeftChild);
		AssignParentPointersToIDQueueElementTree(Parent->m_RightChild);
	}
}

void HuffyManager::AssignParentPointersToBitsUsedQueueElementTree(BitsUsedQueueElement* Parent)
{
	Parent->m_LeftChild->m_Parent = Parent;
	Parent->m_RightChild->m_Parent = Parent;

	//Stop when a child is a leaf node
	if(Parent->m_LeftChild != NULL && Parent->m_RightChild != NULL)
	{
		AssignParentPointersToBitsUsedQueueElementTree(Parent->m_LeftChild);
		AssignParentPointersToBitsUsedQueueElementTree(Parent->m_RightChild);
	}
}

//Map manipulation

void HuffyManager::HuffyTypeModified(e_HuffyTypes e_Type, string ID)
{
	IncrementIDFrequencyMapByType(e_Type, ID);
	IncrementBitsUsedFrequencyMapByType(e_Type, ID);

	//Check if map entry exists, if not init, else increment
	if(UsedTypeFrequencyMap.find(e_Type) == UsedTypeFrequencyMap.end()) 
	{
		UsedTypeFrequencyMap[e_Type] = 0;
	}
	else 
	{
		UsedTypeFrequencyMap[e_Type]++;
	}

	//Ensure the modified object is sent over the network
	HuffyCompressor::AddToSendList(ID);
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
				const HuffyBool* HuffyBoolPointer = reinterpret_cast<const HuffyBool*>(TempBasePointer) ;
				BitsUsed = HuffyCompressor::HowManyBitsToStoreThis(HuffyBoolPointer->GetValue_C());
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

void HuffyManager::IncrementIDFrequencyMapByType(HuffyManager::e_HuffyTypes TypeToIncrement, string IDToIncrement)
{
	//Check if map entry exists, if not init, else increment
	switch (TypeToIncrement) 
	{
		case e_HuffyBool:
			if(BoolIDFrequencyMap.find(IDToIncrement) == BoolIDFrequencyMap.end()) 
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
	}
}

void HuffyManager::RegisterHuffyTypeObject(string m_HuffyID, const HuffyBaseType* SendableHuffyTypeObject)
{
	HuffyManager::HuffyPtrMap[m_HuffyID] = SendableHuffyTypeObject;
}
