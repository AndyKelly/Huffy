#include "StdAfx.h"
#include "HuffyManager.h"
#include "HuffyCompressor.h"
#include "HuffyFloat.h"
#include <string>
#include <list>
#include <map>
//Todo, do we need includes in header and source?
using namespace std;

//Init static member variables
std::map<std::string, const HuffyBaseType* > HuffyManager::HuffyPtrMap;
std::map<HuffyManager::e_HuffyTypes, long long > HuffyManager::UsedTypeFrequencyMap;
std::map<int, int> HuffyManager::BitsUsedFrequencyMap;
std::map<std::string, long long > HuffyManager::IntIDFrequencyMap;
std::map<std::string, long long > HuffyManager::FloatIDFrequencyMap;
std::map<std::string, long long > HuffyManager::BoolIDFrequencyMap;

//Todo should init all values of map to 1

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
	//Todo impliment
	TypeQueueElement* TypeTreeRootNode = ConstructHuffyTypeTreeFromPriorityQueue(GetHuffyTypesPriorityQueue());
	IDQueueElement* IntIDTreeRootNode = ConstructHuffyIDTreeFromPriorityQueue(GetIDPriorityQueueByType(e_HuffyInt));
	IDQueueElement* FloatIDTreeRootNode = ConstructHuffyIDTreeFromPriorityQueue(GetIDPriorityQueueByType(e_HuffyFloat));
	IDQueueElement* BoolIDTreeRootNode = ConstructHuffyIDTreeFromPriorityQueue(GetIDPriorityQueueByType(e_HuffyBool));
	BitsUsedQueueElement* BitsUsedTreeRootNode = ConstructHuffyBitsUsedTreeFromPriorityQueue(GetBitsUsedPriorityQueue());
	//Verify correct init
	//Leave pointers somewhere sensible
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
		}
		case e_HuffyFloat:
		{
			for(itr = FloatIDFrequencyMap.begin(); itr != FloatIDFrequencyMap.end(); itr++)
			{
				IDPQ.push(IDQueueElement(itr->first, itr->second, NULL, NULL, NULL));
			}
		}
		case e_HuffyBool:
		{
			for(itr = BoolIDFrequencyMap.begin(); itr != BoolIDFrequencyMap.end(); itr++)
			{
				IDPQ.push(IDQueueElement(itr->first, itr->second, NULL, NULL, NULL));
			}
		}
	}

	return IDPQ;
}

priority_queue<HuffyManager::BitsUsedQueueElement, vector<HuffyManager::BitsUsedQueueElement>,HuffyManager::CompareBitsUsedElements> HuffyManager::GetBitsUsedPriorityQueue()
{
	priority_queue<BitsUsedQueueElement, vector<BitsUsedQueueElement>,CompareBitsUsedElements> BitsUsedPQ;
	std::map<int, int>::iterator itr;

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

HuffyManager::IDQueueElement* HuffyManager::ConstructHuffyIDTreeFromPriorityQueue(priority_queue<HuffyManager::IDQueueElement,
	vector<HuffyManager::IDQueueElement>,HuffyManager::CompareIDElements> Queue)
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
		//Todo, rename this to something more appropriate. #define NotAnID = 'H' etc?
		IDQueueElement Parent("NAN", (Left->m_Frequency +  Right->m_Frequency), Left, Right, NULL);
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
	//AssignParentPointersToIDQueueElementTree(RootNode);

	return RootNode;
}

HuffyManager::BitsUsedQueueElement* HuffyManager::ConstructHuffyBitsUsedTreeFromPriorityQueue(priority_queue<HuffyManager::BitsUsedQueueElement,
	vector<HuffyManager::BitsUsedQueueElement>,HuffyManager::CompareBitsUsedElements> Queue)
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
		//Todo consBitsUseder splitting up this line, is there much of an overhead for Queue.Top() ?
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
		//Todo, is it ok to presume first arg as NULL?
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
	//AssignParentPointersToBitsUsedQueueElementTree(RootNode);

	return RootNode;
}

//Assign parent pointers to a huffy tree

void HuffyManager::AssignParentPointersToTypeQueueElementTree(TypeQueueElement* Parent)
{
	//Stop when a child is a leaf node
	//Todo, wont work when a node has only one child. Will this ever happen?
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
	//Todo, wont work when a node has only one child. Will this ever happen?
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
	//Todo, wont work when a node has only one child. Will this ever happen?
	if(Parent->m_LeftChild != NULL && Parent->m_RightChild != NULL)
	{
		AssignParentPointersToBitsUsedQueueElementTree(Parent->m_LeftChild);
		AssignParentPointersToBitsUsedQueueElementTree(Parent->m_RightChild);
	}
}

//Todo rename this
//Type specific stuff

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

	//Todo, should reword this, Marked as needing to be sent etc
	//SHould be marked as sendable, i.e. by sending its ID to the compressor, compressor will flush IDs when sent
	AddHuffyIntByIDToCompressor(ID);

}

void HuffyManager::IncrementBitsUsedFrequencyMapByType(e_HuffyTypes e_Type, string ID)
{

	int BitsUsed = 0;
	const HuffyBaseType* TempBasePointer = HuffyPtrMap[ID];

	//Todo, it;s probably a bad idea to use reinterpret_cast
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
					//Todo overload this function
					BitsUsed = HuffyCompressor::HowManyBitsToStoreThis(HuffyFloatPointer->GetValue_C());
					break;
				}
			case e_HuffyBool:
				//const HuffyBool* HuffyBoolPointer = reinterpret_cast<const HuffyBool*>(TempBasePointer) ;
				//BitsUsed = HuffyCompressor::HowManyBitsToStoreThis(HuffyBoolPointer->GetValue_C());
				break;
		}

	}
    catch (const std::bad_cast& e)
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

//Todo rename this to something more appropriate
void HuffyManager::RegisterHuffyTypeAsSendable(string m_HuffyID, const HuffyBaseType* SendableHuffyType)
{
	HuffyManager::HuffyPtrMap[m_HuffyID] = SendableHuffyType;
}

//Todo refactor for each type using templates?
void HuffyManager::AddHuffyIntByIDToCompressor(string ID)
{
	//To do, dynamic casts
	//Figure out types here
	//HuffyCompressor::AddIntToOutStream(HuffyManager::HuffyPtrMap[ID]->GetValue_C());
}