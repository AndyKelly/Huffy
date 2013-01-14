/*
 * HuffyPacker.cpp
 *
 *  Created on: Jan 12, 2013
 *      Author: hal
 */

#include "HuffyPacker.h"
#include "HuffyPackerUtility.h"
#include "BitString.h"
#include <iostream>
#include <string>
#include "HuffyConstants.h"
//Todo, needs some serious tidy up
HuffyPacker::HuffyPacker() {
	CurrentBit = 0;
	CurrentByte = 0;
	CurrentReadBit = 0;
	CurrentReadByte = 0;
	//Zero the first byte
	Buffer[0] = 0;
}

HuffyPacker::~HuffyPacker() {
}

void HuffyPacker::ApplyUpdateString(std::string PassedString)
{
	int counter = 0;

	for(std::string::iterator it = PassedString.begin(); it != PassedString.end(); ++it)
	{
		if(counter < BUFFER_SIZE)
		{
			Buffer[counter] = (unsigned char)*it;
			counter++;
		}
	}
}

std::string HuffyPacker::ReturnStringTest(void)
{
	int counter = 0;
	std::string Ret  ="";
	while(counter < 100)
	{
		Ret+= Buffer[counter];
	}
	return Ret;
}

std::string HuffyPacker::ReturnUpdateString()
{
	std::string ReturnString;
	int LastWrittenPosition = 0;
	if(CurrentByte != 0)
	{
		//Todo, +1 ??
		LastWrittenPosition = (((CurrentByte + 1) * BYTE_SIZE) + CurrentBit);
	}
	//Maybe nothing has been written but we want to retrieve the applied update for some reason
	else
	{
		//Todo, why would we want to read the buffer if noting has been written to it?
		//Consider revising this
		LastWrittenPosition = BUFFER_SIZE;
	}

	int counter = 0;
	while(counter <= LastWrittenPosition)
	{
		ReturnString += Buffer[counter];
		counter++;
	}
	return ReturnString;
}

float HuffyPacker::ReadFloatAtIndex(int Index, int BitsUsed)
{
	int FloatAsInt = ReadIntAtIndex(Index, BitsUsed);
	float ReturnValue = (float)FloatAsInt;
	return ReturnValue/(float)SIGNIFICANT_DIGITS_MULTIPLIER;
}

bool HuffyPacker::ReadBoolAtIndex(int Index)
{
	//Use one bit for bool
	//Todo, this should be in HuffyConstants
	if(ReadIntAtIndex(Index, 1))
	{
		return true;
	}
	return false;
}

int HuffyPacker::ReadIntAtIndex(int Index, int BitsUsed)
{
	int tempCurrentReadBit = CurrentReadBit;
	int tempCurrentReadByte = CurrentReadByte;

	if(Index > 8)
	{
		CurrentReadByte = Index / 8;
		CurrentReadBit = Index % 8;
	}
	else
	{
		CurrentReadByte = 0;
		CurrentReadBit = Index;
	}


	int ReturnVal = ReadIntValueFromBuffer(BitsUsed);

	CurrentReadBit = tempCurrentReadBit;
	CurrentReadByte = tempCurrentReadByte;

	return ReturnVal;
}

BitString HuffyPacker::GetUpdateAsBitsetString()
{
	BitString ReturnString;
	int TempReadBitIndex=0;
	while(TempReadBitIndex <= CurrentByte*8 + CurrentBit-1)
	{
		//Read one bit
		if(ReadIntAtIndex(TempReadBitIndex,1) == 1)
		{
			ReturnString.WriteOne();
		}
		else
		{
			ReturnString.WriteZero();
		}
		TempReadBitIndex++;
	}
	return ReturnString;
}


//Duplicate logic for readability
void HuffyPacker::AddIDtoUpdate(std::string BitSetFormattedString)
{
	WriteBitsetStyleStringToBuffer(BitSetFormattedString);
}

void HuffyPacker::AddTypetoUpdate(std::string BitSetFormattedString)
{
	WriteBitsetStyleStringToBuffer(BitSetFormattedString);
}

void HuffyPacker::AddBitsUsedToUpdate(std::string BitSetFormattedString)
{
	WriteBitsetStyleStringToBuffer(BitSetFormattedString);
}

void HuffyPacker::AddIntValueToUpdate(int Value, int BitsToUse)
{
	writeInt(Value, BitsToUse);
}

int HuffyPacker::ReadIntValueFromBuffer(int BitsToUse)
{
	return readInt(BitsToUse);
}


void HuffyPacker::AddFloatValueToUpdate(int BitsToUse, float Value)
{
	//Round string off to significant digits
	int i_Value = (int)(Value*SIGNIFICANT_DIGITS_MULTIPLIER);
	writeInt(i_Value, BitsToUse);
}

void HuffyPacker::AddBoolValueToUpdate(bool WriteBool)
{
	if(WriteBool)
	{
		WriteOneToBuffer();
	}
	else
	{
		WriteZeroToBuffer();
	}
}


void HuffyPacker::WriteBitsetStyleStringToBuffer(std::string StringToWrite)
{
	if(CheckIfStringIsValid(StringToWrite))
	{
		for(std::string::iterator it = StringToWrite.begin(); it != StringToWrite.end(); ++it)
		{
			if(*it == '1')
			{
				WriteOneToBuffer();
			}
			else if(*it == '0')
			{
				WriteZeroToBuffer();
			}
		}
	}
	else
	{
		std::cout<<"Invalid bitset string";
	}
}

//Todo, this can be optimised
//Fix in next iteration
bool HuffyPacker::CheckIfStringIsValid(std::string StringToCheck)
{
	bool ReturnValue = false;
	for(std::string::iterator it = StringToCheck.begin(); it != StringToCheck.end(); ++it)
	{
		ReturnValue = false;
	    if(*it == '0')
	    {
	    	ReturnValue = true;
	    }
	    if(*it == '1')
	    {
	    	ReturnValue = true;
	    }
	}
	return ReturnValue;
}

void HuffyPacker::WriteOneToBuffer()
{
	//Value of 1, use one bit
	writeInt(1,1);
}

void HuffyPacker::WriteZeroToBuffer()
{
	//Value of 0, use one bit
	writeInt(0,1);
}

int HuffyPacker::HowBigIsThisFloat(float ValueToAdd)
{
	return HowBigIsThisInt((int)ValueToAdd*SIGNIFICANT_DIGITS_MULTIPLIER);
}

//Todo, this is gloriously inefficient, these values should be cached somehow.
//Add in next iteration, an algorithmic approach could work.
int HuffyPacker::HowBigIsThisInt(int IntToTest)
{
	int readVal = 0;
	int NumberOfBits = 0;
	HuffyPackerUtility Util;
	while(readVal!=IntToTest)
	{
		NumberOfBits++;
		//Write value to temp buffer using n bits
	    Util.WriteInt(IntToTest, NumberOfBits);

		//Try read value from temp buffer using n bits
	    readVal = Util.ReadInt(NumberOfBits);

	//return n
	}
	return NumberOfBits;
}

void HuffyPacker::writeInt(int Value,int numBitsToWrite)
{
	int bitsWritten = 0;
   while(bitsWritten <numBitsToWrite)
	{
		int bitToWrite = Value>>bitsWritten;
		WriteBitToBuffer(bitToWrite);
		bitsWritten++;
	}
}

int HuffyPacker::readInt(int numBitsToRead)
{
	int returnVal= 0;
	int bitsRead = 0;
	while(bitsRead<numBitsToRead)
	{
		int bitToRead = ReadBitFromBuffer();
		returnVal = returnVal | (bitToRead<<bitsRead);
		bitsRead++;
	}
	return returnVal;
}

void HuffyPacker::WriteBitToBuffer(int Value)
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

int HuffyPacker::ReadBitFromBuffer()
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
