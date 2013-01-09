#include "HuffyManager.h"
#include "HuffyCompressor.h"
#include "HuffyBaseType.h"

#include <math.h>

//Static init
	int HuffyCompressor::CurrentBit = 0;
	int HuffyCompressor::CurrentByte = 0;
	int HuffyCompressor::CurrentReadBit = 0;
	int HuffyCompressor::CurrentReadByte = 0;
	unsigned char HuffyCompressor::Buffer[BufferLimit];
	//Todo Find a way to zero the first element

	bool HuffyCompressor::m_InitalisedAsServer = false;
	std::string HuffyCompressor::m_ClientAddress = "NULL";
	int HuffyCompressor::m_PortNum = NULL;

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
}

void HuffyCompressor::Init(std::string ClientAddress, int PortNum)
{
	m_ClientAddress = ClientAddress;
	m_InitalisedAsServer = true;
	m_PortNum = PortNum;
}

void HuffyCompressor::SendUpdate()
{
	//Todo impliment
	if(m_InitalisedAsServer)
	{
		//Send Ostream
		//Wipe Ostream
	}
}


void HuffyCompressor::AddToSendList(std::string  ID)
{
	//Todo impliment
	//Todo Add type to Ostream
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

void HuffyCompressor::CompressHuffyBaseType(const HuffyBaseType* BaseTypeToCompress)
{
	AddHuffyTypeToBitSet(BaseTypeToCompress->GetType());
}

void HuffyCompressor::AddHuffyTypeToBitSet(int TypeToAdd)
{
	//Find type in huffy tree
	HuffyManager::TypeQueueElement* StartNode = GetPointerToTypeInTypeTreeByType(TypeToAdd, m_TypeTreeRootNode);

	while(StartNode->m_Parent != NULL)
	{
		HuffyManager::TypeQueueElement* PreviousNode = StartNode;
		StartNode = StartNode->m_Parent;
		//todo this is backwards
		//Todo impliment//////////////////////////////////////////////////////////////////////////////////
		if(StartNode->m_LeftChild == PreviousNode)
		{
			WriteValueToBitset(e_ONE);
		}
		else 
		{
			WriteValueToBitset(e_ZERO);
		}
	}
}

void HuffyCompressor::WriteValueToBitset(int ValueToWrite)
{
	//Todo impliment///////////////////////////////////////////////////////////////////////////////////
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

int HuffyCompressor::HowManyBitsToStoreThis(int)
{
	//Todo implement
	return 0;
}

int HuffyCompressor::HowManyBitsToStoreThis(float)
{
	//Todo implement
	return 0;
}

void HuffyCompressor::writeInt(int Value,int numBitsToWrite)
{     
	int bitsWritten = 0;
   while(bitsWritten <numBitsToWrite)
	{ 
		int bitToWrite = Value>>bitsWritten;
		WriteIntToBuffer(bitToWrite);
		bitsWritten++;    
	}      
}

int HuffyCompressor::readInt(int numBitsToRead)
{    
	int returnVal= 0;
	int bitsRead = 0;   
	while(bitsRead<numBitsToRead)
	{            
		int bitToRead = ReadIntFromBuffer();
		returnVal = returnVal | (bitToRead<<bitsRead); 
		bitsRead++;   
	}        
	return returnVal;  
}

void HuffyCompressor::WriteIntToBuffer(int Value)
{
	if(CurrentBit == 8)
	{
		CurrentBit = 0;
		CurrentByte++;
		//Zero the current byte
		Buffer[CurrentByte] = 0;
	}

	Buffer[CurrentByte] |= (Value << CurrentBit);
	CurrentBit++;
}

int HuffyCompressor::ReadIntFromBuffer()
{
	if(CurrentReadBit == 8)
	{
		CurrentReadBit = 0;
		CurrentReadByte++;
	}

	///Shift current byte over by CurrentReadBits
	unsigned int CheckBit = Buffer[CurrentReadByte] >> CurrentReadBit;
	CurrentReadBit++;

	return(CheckBit & 1);
}
