/*
 * HuffyTreeManager.cpp
 *
 *      Author: Andy Kelly
 */

#include "HuffyTreeManager.h"
#include "TreeUtility.h"
#include <iostream>
#include <deque>
#ifndef NULL
#define NULL   ((void *) 0)
#endif

HuffyTreeManager::HuffyTreeManager()
{
	TypeQueueElement* m_TypeTreeRootNode = NULL;
	IDQueueElement* m_IntIDTreeRootNode = NULL;
	IDQueueElement* m_FloatIDTreeRootNode = NULL;
	IDQueueElement* m_BoolIDTreeRootNode = NULL;
	BitsUsedQueueElement* m_BitsUsedTreeRootNode = NULL;
}


HuffyTreeManager::~HuffyTreeManager()
{
	DeleteOldTrees();
}


BitString HuffyTreeManager::GetBitStringForType(e_HuffyTypes TypeToLookFor)
{
	TypeQueueElement* NodePosition = GetPointerToNodeInTypeTreeByType(TypeToLookFor);
	BitString ReturnBitString;
	TypeQueueElement* TempNode;
	while(NodePosition->m_Parent!= NULL)
	{
		TempNode = NodePosition->m_Parent;
		if(TempNode->m_LeftChild == NodePosition)
		{
			ReturnBitString.WriteOne();
		}
		else
		{
			ReturnBitString.WriteZero();
		}
		NodePosition = TempNode;
	}
	//Were traveling up the tree so we should reverse the string
	ReturnBitString.Reverse();
	return ReturnBitString;
}

BitString HuffyTreeManager::GetBitStringForID(std::string IDtoLookFor, e_HuffyTypes IDType)
{
	IDQueueElement* NodePosition = GetPointerToNodeInIDTreeByIDAndType(IDtoLookFor, IDType);
	BitString ReturnBitString;
	IDQueueElement* TempNode;
	while(NodePosition->m_Parent!= NULL)
	{
		TempNode = NodePosition->m_Parent;
		if(TempNode->m_LeftChild == NodePosition)
		{
			ReturnBitString.WriteOne();
		}
		else
		{
			ReturnBitString.WriteZero();
		}
		NodePosition = TempNode;
	}

	//Were traveling up the tree so we should reverse the string
	ReturnBitString.Reverse();

	return ReturnBitString;
}

BitString HuffyTreeManager::GetBitStringForBitsUsed(int ValueToLookFor)
{
	BitsUsedQueueElement* NodePosition = GetPointerToNodeInBitsUsedTreeByValue(ValueToLookFor);
	BitString ReturnBitString;
	BitsUsedQueueElement* TempNode;
	while(NodePosition->m_Parent!= NULL)
	{
		TempNode = NodePosition->m_Parent;
		if(TempNode->m_LeftChild == NodePosition)
		{
			ReturnBitString.WriteOne();
		}
		else
		{
			ReturnBitString.WriteZero();
		}
		NodePosition = TempNode;
	}

	//Were traveling up the tree so we should reverse the string
	ReturnBitString.Reverse();

	return ReturnBitString;
}


void HuffyTreeManager::PassPointersToHuffyTreeRootNodes(TypeQueueElement* NewTypeTree,
	IDQueueElement* NewIntIdTree,
	IDQueueElement* NewFloatIDTree,
	IDQueueElement* NewBoolIDTree,
	BitsUsedQueueElement* NewBitsUsedIDTree )
{
	DeleteOldTrees();

	m_TypeTreeRootNode = NewTypeTree;
	m_IntIDTreeRootNode = NewIntIdTree;
	m_FloatIDTreeRootNode = NewFloatIDTree;
	m_BoolIDTreeRootNode = NewBoolIDTree;
	m_BitsUsedTreeRootNode = NewBitsUsedIDTree;
}

e_HuffyTypes HuffyTreeManager::GetTypeFromString(std::string TreeDirections)
{
	int StringCounter = 0;
	TypeQueueElement* CurrentNode = m_TypeTreeRootNode;
	e_HuffyTypes SeenType = e_HuffyNonLeaf;
	while(SeenType == e_HuffyNonLeaf)
	{
		SeenType = CurrentNode->m_TypeValue;
		if(TreeDirections[StringCounter] == '1')
		{
			CurrentNode = CurrentNode->m_LeftChild;
		}
		else if(TreeDirections[StringCounter] == '0')
		{
			CurrentNode = CurrentNode->m_RightChild;
		}
		StringCounter++;
	}
	return SeenType;
}

int HuffyTreeManager::GetBitsUsedFromString(std::string TreeDirections)
{
	int StringCounter = 0;
	BitsUsedQueueElement* CurrentNode = m_BitsUsedTreeRootNode;
	int BitsUsed = 0;
	while(BitsUsed == 0)
	{
		BitsUsed = CurrentNode->m_BitsUsed;
		if(TreeDirections[StringCounter] == '1')
		{
			CurrentNode = CurrentNode->m_LeftChild;
		}
		else if(TreeDirections[StringCounter] == '0')
		{
			CurrentNode = CurrentNode->m_RightChild;
		}
		StringCounter++;
	}
	return BitsUsed;
}

std::string HuffyTreeManager::GetIDFromStringByType(std::string TreeDirections, e_HuffyTypes Type)
{
	std::string ID = "";
	switch(Type)
	{
		case(e_HuffyInt):
		{
			ID = GetIDFromString(TreeDirections, m_IntIDTreeRootNode);
			break;
		}
		case(e_HuffyFloat):
		{
			ID = GetIDFromString(TreeDirections, m_FloatIDTreeRootNode);
			break;
		}
		case(e_HuffyBool):
		{
			ID = GetIDFromString(TreeDirections, m_BoolIDTreeRootNode);
			break;
		}
	}
	return ID;
}

std::string HuffyTreeManager::GetIDFromString(std::string TreeDirections, IDQueueElement* TreeToUse)
{
	int StringCounter = 0;
	IDQueueElement* CurrentNode = TreeToUse;
	std::string SeenID = "";
	while(SeenID == "")
	{
		SeenID = CurrentNode->m_ID;
		if(TreeDirections[StringCounter] == '1')
		{
			CurrentNode = CurrentNode->m_LeftChild;
		}
		else if(TreeDirections[StringCounter] == '0')
		{
			CurrentNode = CurrentNode->m_RightChild;
		}
		StringCounter++;
	}
	return SeenID;
}

//Delete huffy tree's recursivly
void HuffyTreeManager::DeleteOldTrees()
{
	DeleteTypeQueueElementTree(m_TypeTreeRootNode);
	DeleteIDQueueElementTree(m_IntIDTreeRootNode);
	DeleteIDQueueElementTree(m_FloatIDTreeRootNode);
	DeleteIDQueueElementTree(m_BoolIDTreeRootNode);
	DeleteBitsUsedQueueElementTree(m_BitsUsedTreeRootNode);
}

void HuffyTreeManager::DeleteTypeQueueElementTree(TypeQueueElement* Parent)
{
	if(Parent != NULL)
	{
		if(Parent->m_RightChild != NULL)
		{
			DeleteTypeQueueElementTree(Parent->m_RightChild);
		}
		if(Parent->m_LeftChild != NULL)
		{
			DeleteTypeQueueElementTree(Parent->m_LeftChild);
		}

		delete Parent;
	}
}

void HuffyTreeManager::DeleteIDQueueElementTree(IDQueueElement* Parent)
{
	if(Parent != NULL)
	{
		if(Parent->m_RightChild != NULL)
		{
			DeleteIDQueueElementTree(Parent->m_RightChild);
		}
		if(Parent->m_LeftChild != NULL)
		{
			DeleteIDQueueElementTree(Parent->m_LeftChild);
		}

		delete Parent;
	}
}

void HuffyTreeManager::DeleteBitsUsedQueueElementTree(BitsUsedQueueElement* Parent)
{
	if(Parent != NULL)
	{
		if(Parent->m_RightChild != NULL)
		{
			DeleteBitsUsedQueueElementTree(Parent->m_RightChild);
		}
		if(Parent->m_LeftChild != NULL)
		{
			DeleteBitsUsedQueueElementTree(Parent->m_LeftChild);
		}

		delete Parent;
	}
}


TypeQueueElement* HuffyTreeManager::GetPointerToNodeInTypeTreeByType(e_HuffyTypes PassedValue)
{
	std::deque<TypeQueueElement *> NodeQueue;
	NodeQueue.push_back(m_TypeTreeRootNode);
	while (NodeQueue.size() != 0)
	{
		TypeQueueElement *next = NodeQueue.front();
		if(next->m_TypeValue == PassedValue)
		{
			return next;
		}
		NodeQueue.pop_front();
		if (next->m_LeftChild)
		{
			NodeQueue.push_back(next->m_LeftChild);
		}
		if (next->m_RightChild)
		{
			NodeQueue.push_back(next->m_RightChild);
		}
	}

	//We should be returning something sensible here or surfacing this error somehow
	//todo Fix in next iteration
	return m_TypeTreeRootNode;
}

IDQueueElement* HuffyTreeManager::GetPointerToNodeInIDTreeByIDAndType(std::string ID, e_HuffyTypes Type)
{
	IDQueueElement* ReturnNode;
	switch(Type)
	{
		case(e_HuffyInt):
		{
			ReturnNode = GetPointerToNodeInIntIDTreeByID(ID);
			break;
		}
		case(e_HuffyFloat):
		{
			ReturnNode = GetPointerToNodeInFloatIDTreeByID(ID);
			break;
		}
		case(e_HuffyBool):
		{
			ReturnNode = GetPointerToNodeInBoolIDTreeByID(ID);
			break;
		}
	}
	//Todo, theres always a chance of returning a null pointer here, fix in next revision
	return ReturnNode;
}

IDQueueElement* HuffyTreeManager::GetPointerToNodeInIntIDTreeByID(std::string IntID)
{
	std::deque<IDQueueElement *> NodeQueue;
	NodeQueue.push_back(m_IntIDTreeRootNode);
	while (NodeQueue.size() != 0)
	{
		IDQueueElement *next = NodeQueue.front();
		if(next->m_ID == IntID)
		{
			return next;
		}
		NodeQueue.pop_front();
		if (next->m_LeftChild)
		{
			NodeQueue.push_back(next->m_LeftChild);
		}
		if (next->m_RightChild)
		{
			NodeQueue.push_back(next->m_RightChild);
		}
	}

	//We should be returning something sensible here or surfacing this error somehow
	//todo Fix in next iteration
	return m_IntIDTreeRootNode;
}

IDQueueElement* HuffyTreeManager::GetPointerToNodeInFloatIDTreeByID(std::string FloatID)
{
	std::deque<IDQueueElement *> NodeQueue;
	NodeQueue.push_back(m_FloatIDTreeRootNode);
	while (NodeQueue.size() != 0)
	{
		IDQueueElement *next = NodeQueue.front();
		if(next->m_ID == FloatID)
		{
			return next;
		}
		NodeQueue.pop_front();
		if (next->m_LeftChild)
		{
			NodeQueue.push_back(next->m_LeftChild);
		}
		if (next->m_RightChild)
		{
			NodeQueue.push_back(next->m_RightChild);
		}
	}

	//We should be returning something sensible here or surfacing this error somehow
	//todo Fix in next iteration
	return m_FloatIDTreeRootNode;
}

IDQueueElement* HuffyTreeManager::GetPointerToNodeInBoolIDTreeByID(std::string BoolID)
{
	std::deque<IDQueueElement *> NodeQueue;
	NodeQueue.push_back(m_BoolIDTreeRootNode);
	while (NodeQueue.size() != 0)
	{
		IDQueueElement *next = NodeQueue.front();
		if(next->m_ID == BoolID)
		{
			return next;
		}
		NodeQueue.pop_front();
		if (next->m_LeftChild)
		{
			NodeQueue.push_back(next->m_LeftChild);
		}
		if (next->m_RightChild)
		{
			NodeQueue.push_back(next->m_RightChild);
		}
	}

	//We should be returning something sensible here or surfacing this error somehow
	//todo Fix in next iteration
	return m_BoolIDTreeRootNode;
}

BitsUsedQueueElement* HuffyTreeManager::GetPointerToNodeInBitsUsedTreeByValue(int BitsUsedValue)
{
	std::deque<BitsUsedQueueElement *> NodeQueue;
	NodeQueue.push_back(m_BitsUsedTreeRootNode);
	while (NodeQueue.size() != 0)
	{
		BitsUsedQueueElement *next = NodeQueue.front();
		if(next->m_BitsUsed== BitsUsedValue)
		{
			return next;
		}
		NodeQueue.pop_front();
		if (next->m_LeftChild)
		{
			NodeQueue.push_back(next->m_LeftChild);
		}
		if (next->m_RightChild)
		{
			NodeQueue.push_back(next->m_RightChild);
		}
	}

	//We should be returning something sensible here or surfacing this error somehow
	//todo Fix in next iteration
	return m_BitsUsedTreeRootNode;
}

