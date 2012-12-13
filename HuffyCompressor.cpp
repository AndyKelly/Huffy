#include "StdAfx.h"
#include "HuffyManager.h"
#include "HuffyCompressor.h"

#include <math.h>

//Static init
	int HuffyCompressor::CurrentBit = 0;
	int HuffyCompressor::CurrentByte = 0;
	int HuffyCompressor::CurrentReadBit = 0;
	int HuffyCompressor::CurrentReadByte = 0;
	unsigned char HuffyCompressor::Buffer[BufferLimit];
	//Todo Find a way to zero the first element

	HuffyManager::TypeQueueElement* HuffyCompressor::m_TypeTreeRootNode = NULL;
	HuffyManager::IDQueueElement* HuffyCompressor::m_IntIDTreeRootNode = NULL;
	HuffyManager::IDQueueElement* HuffyCompressor::m_FloatIDTreeRootNode = NULL;
	HuffyManager::IDQueueElement* HuffyCompressor::m_BoolIDTreeRootNode = NULL;
	HuffyManager::BitsUsedQueueElement* HuffyCompressor::m_BitsUsedTreeRootNode = NULL;

//Todo should be singleton
HuffyCompressor::HuffyCompressor(void)
{

}

HuffyCompressor::~HuffyCompressor(void)
{
}
void HuffyCompressor::PassPointersToHuffyTreeRootNodes(HuffyManager::TypeQueueElement* NewTypeTree,
	HuffyManager::IDQueueElement* NewIntIdTree,
	HuffyManager::IDQueueElement* NewFloatIDTree,
	HuffyManager::IDQueueElement* NewBoolIDTree,
	HuffyManager::BitsUsedQueueElement* NewBitsUsedIDTree )
{
	//Todo delete old tree's

	m_TypeTreeRootNode = NewTypeTree;
	m_IntIDTreeRootNode = NewIntIdTree;
	m_FloatIDTreeRootNode = NewFloatIDTree;
	m_BoolIDTreeRootNode = NewBoolIDTree;
	m_BitsUsedTreeRootNode = NewBitsUsedIDTree;
}

void HuffyCompressor::AddIntToOutStream(int ValueToAdd)
{
	//Todo Add type to Ostream
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
