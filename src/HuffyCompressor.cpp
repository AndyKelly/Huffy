#include "HuffyManager.h"
#include "HuffyCompressor.h"
#include "HuffyBaseType.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <list>
#include <bitset>
#include <map>
#include <math.h>





	HuffyManager::TypeQueueElement* HuffyCompressor::m_TypeTreeRootNode = NULL;
	HuffyManager::IDQueueElement* HuffyCompressor::m_IntIDTreeRootNode = NULL;
	HuffyManager::IDQueueElement* HuffyCompressor::m_FloatIDTreeRootNode = NULL;
	HuffyManager::IDQueueElement* HuffyCompressor::m_BoolIDTreeRootNode = NULL;
	HuffyManager::BitsUsedQueueElement* HuffyCompressor::m_BitsUsedTreeRootNode = NULL;

HuffyCompressor::HuffyCompressor(void)
{
}

HuffyCompressor::~HuffyCompressor(void)
{
	DeleteOldTrees();
}

void ConstructUpdateFromIDList(std::list<std::string>)
{
	//Find ID in tree
}

std::string HuffyCompressor::GetUpdate()
{
	//todo impliment
	return "UPDATE";
}


//HuffyCompressor::ApplyUpdate(HuffyPtrMap, Update)
	//HuffyPacker::StringToBoolList()
	//Traverse type tree using bool list until found type, store
	//Traverse ID tree using bool list until found ID, store
	//if(!Bool)
		//Traverse BitsUsed tree using bool list until found BitsUsed, store
		//Construct value bool list
		//HuffyPtrMap[ID]->SetValue(HuffyCompressor::ConstructValByTypeFromBLIST(value bool list,BitsUsed, type))
	//else
		//HuffyPtrMap[ID]->SetValue((BOOLLIST.Next)

void HuffyCompressor::ConstructUpdateFromIDList(
		std::list<std::string> ID_List,
		std::map<std::string, const HuffyBaseType* > TypesMap,
		std::map<std::string, HuffyManager::e_HuffyTypes > ID_TpyeAssociationMap
		)
{
	while(!ID_List.empty())
	{
		std::string IDToAdd = ID_List.front();
		ID_List.pop_front();

		const HuffyBaseType* TempBasePointer = TypesMap[IDToAdd];

		try
		{
			switch(ID_TpyeAssociationMap[IDToAdd])
			{
				case HuffyManager::e_HuffyInt:
				{
					const HuffyInt* HuffyIntPointer = reinterpret_cast<const HuffyInt*>(TempBasePointer) ;
					AddIntToUpdate(IDToAdd,
							HuffyCompressor::HowManyBitsToStoreThis(HuffyIntPointer->GetValue_C()),
							HuffyIntPointer->GetValue_C());
					break;
				}
				case HuffyManager::e_HuffyFloat:
				{
					break;
				}
				case HuffyManager::e_HuffyBool:
				{
					break;
				}
			}

		}
	    catch (...)
	    {
			//Todo some way of logging this error
	    }
	    //////////////////////////////////
	    //Todo, retrieve string from HuffyPacker
	}
}

void HuffyCompressor::AddIntToUpdate(std::string IDToAdd,int NumberOfBitsUsed, int Value)
{
	//Todo impliment
	//Construct bool list ID
	//Huffy packer Add ID to m_update(BooList)
	//Construct bool list Bits used
	//Huffy packer Add bits used to m_update(BoolList)
	//Huffy packer Add int value to m_update(NumberOfBitsUsed, Value)
}

void HuffyCompressor::AddFloatToUpdate(std::string IDToAdd,int NumberOfBitsUsed, float Value)
{
	//Todo impliment
	//Construct bool list ID
	//Huffy packer Add ID to m_update(BooList)
	//Construct bool list Bits used
	//Huffy packer Add bits used to m_update(BoolList)
	//Huffy packer Add float value to m_update(NumberOfBitsUsed, Value)
}

void HuffyCompressor::AddBoolToUpdate(std::string IDToAdd,int NumberOfBitsUsed, bool Value)
{
	//Todo impliment
	//Construct bool list ID
	//Huffy packer Add ID to m_update(BooList)
	//Huffy packer Add bool value to m_update(true/false)
}


void HuffyCompressor::PassPointersToHuffyTreeRootNodes(HuffyManager::TypeQueueElement* NewTypeTree,
	HuffyManager::IDQueueElement* NewIntIdTree,
	HuffyManager::IDQueueElement* NewFloatIDTree,
	HuffyManager::IDQueueElement* NewBoolIDTree,
	HuffyManager::BitsUsedQueueElement* NewBitsUsedIDTree )
{
	DeleteOldTrees();

	m_TypeTreeRootNode = NewTypeTree;
	m_IntIDTreeRootNode = NewIntIdTree;
	m_FloatIDTreeRootNode = NewFloatIDTree;
	m_BoolIDTreeRootNode = NewBoolIDTree;
	m_BitsUsedTreeRootNode = NewBitsUsedIDTree;
}


//Delete huffy tree's recursivly
void HuffyCompressor::DeleteOldTrees()
{
	DeleteTypeQueueElementTree(m_TypeTreeRootNode);
	DeleteIDQueueElementTree(m_IntIDTreeRootNode);
	DeleteIDQueueElementTree(m_FloatIDTreeRootNode);
	DeleteIDQueueElementTree(m_BoolIDTreeRootNode);
	DeleteBitsUsedQueueElementTree(m_BitsUsedTreeRootNode);
}

void HuffyCompressor::DeleteTypeQueueElementTree(HuffyManager::TypeQueueElement* Parent)
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

void HuffyCompressor::DeleteIDQueueElementTree(HuffyManager::IDQueueElement* Parent)
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

void HuffyCompressor::DeleteBitsUsedQueueElementTree(HuffyManager::BitsUsedQueueElement* Parent)
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


HuffyManager::TypeQueueElement* HuffyCompressor::GetPointerToTypeInTypeTreeByType(int PassedValue, HuffyManager::TypeQueueElement* NodeToOperateOn)
{
	//Todo impliment//////////////////////////////////////////////////////////////////////////////////
	//algorithm Find-recursive(key, node):  // call initially with node = root
	 //   if node = Nil or node.key = key then
	 //       node
	 //   else if key < node.key then
	 //       Find-recursive(key, node.left)
	 //   else
	 //       Find-recursive(key, node.right)
	return NodeToOperateOn;
}


int HuffyCompressor::HowManyBitsToStoreThis(int )
{
	//Todo implement
	//HuffyPacker::HowBigIsThisInt?
	return 0;
}

int HuffyCompressor::HowManyBitsToStoreThis(float)
{
	//Todo implement
	//HuffyPacker::HowBigIsThisFloat?
	return 0;
}
