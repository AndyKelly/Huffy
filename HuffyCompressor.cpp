#include "StdAfx.h"
#include "HuffyCompressor.h"
#include <math.h>

	int HuffyCompressor::CurrentBit = 0;
	int HuffyCompressor::CurrentByte = 0;
	int HuffyCompressor::CurrentReadBit = 0;
	int HuffyCompressor::CurrentReadByte = 0;
	unsigned char HuffyCompressor::Buffer[BufferLimit];
	//Todo Find a way to zero the first element

//Todo should be singleton
HuffyCompressor::HuffyCompressor(void)
{

}

HuffyCompressor::~HuffyCompressor(void)
{
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
