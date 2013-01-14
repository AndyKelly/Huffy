/*
 * HuffyPackerUtility.cpp
 *
 *      Author: Andy Kelly
 */

#include "HuffyPackerUtility.h"
#include <cstring>
#include <iostream>

HuffyPackerUtility::HuffyPackerUtility() {
	//Clean up temp values for next run
	CurrentTempBit = 0;
	CurrentTempByte = 0;
	CurrentTempReadBit = 0;
	CurrentTempReadByte = 0;
	TempBuffer[0] = 0;

}

HuffyPackerUtility::~HuffyPackerUtility() {
	// TODO Auto-generated destructor stub
}


void HuffyPackerUtility::WriteInt(int IntToTest, int NumberOfBits)
{
	WriteIntToTempBuffer(IntToTest,NumberOfBits);
}

int HuffyPackerUtility::ReadInt(int NumberOfBits)
{
	return readIntFromTempBuffer(NumberOfBits);
}


void HuffyPackerUtility::WriteIntToTempBuffer(int Value,int numBitsToWrite)
{
	int bitsWritten = 0;
   while(bitsWritten <numBitsToWrite)
	{
		int bitToWrite = Value>>bitsWritten;
		WriteBitToTempBuffer(bitToWrite);
		bitsWritten++;
	}
}

int HuffyPackerUtility::getBit()
{
	if(CurrentTempReadBit == 8)
	{
		CurrentTempReadBit = 0;
		CurrentTempReadByte++;
	}

   int ret =  TempBuffer[CurrentTempReadByte] & (1 << CurrentTempReadBit);
   CurrentTempReadBit++;
   return ret;
}

void HuffyPackerUtility::WriteBitToTempBuffer(int Value)
{
	if(CurrentTempBit == 8)
	{
		CurrentTempBit = 0;
		CurrentTempByte++;
		//Zero the current byte
		TempBuffer[CurrentTempByte] = 0;
	}

	TempBuffer[CurrentTempByte] |= (Value << CurrentTempBit);
	CurrentTempBit++;
}

int HuffyPackerUtility::readIntFromTempBuffer(int numBitsToRead)
{
	int returnVal= 0;
	int bitsRead = 0;
	while(bitsRead<numBitsToRead)
	{
		int bitToRead = ReadBitFromTempBuffer();
		returnVal = returnVal | (bitToRead<<bitsRead);
		bitsRead++;
	}
	return returnVal;
}

int HuffyPackerUtility::ReadBitFromTempBuffer()
{
	if(CurrentTempReadBit == 8)
	{
		CurrentTempReadBit = 0;
		CurrentTempReadByte++;
	}

	///Shift current byte over by CurrentReadBits
	unsigned int CheckBit = TempBuffer[CurrentTempReadByte] >> CurrentTempReadBit;
	CurrentTempReadBit++;

	return(CheckBit & 1);
}
