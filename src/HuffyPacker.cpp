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
	//Todo should be coming from HuffyConstants.h
	int BufferSize = 1000;
	int counter = 0;

	for(std::string::iterator it = PassedString.begin(); it != PassedString.end(); ++it)
	{
		if(counter < BufferSize)
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
	//Todo this 8 should be coming from HuffyConstants.h
	int LastWrittenPosition = 0;
	if(CurrentByte != 0)
	{
		//Should be coming from huffyconstants, i.e. Byte size
		LastWrittenPosition = (((CurrentByte + 1) * 8) + CurrentBit);
	}
	//Maybe nothing has been written but we want to retrieve the applied update for some reason
	else
	{
		//Should be coming from huffyconstants, i.e. BufferSize
		LastWrittenPosition = 1000;
	}

	int counter = 0;
	while(counter <= LastWrittenPosition)
	{
		ReturnString += Buffer[counter];
		counter++;
	}
	return ReturnString;
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
	while(CurrentReadByte <= CurrentByte)
	{
		//Read one bit
		if(readInt(1) == 1)
		{
			ReturnString.WriteOne();
		}
		else
		{
			ReturnString.WriteZero();
		}
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
	//Todo, should get significant digits from HuffyCOnstants.h
	//Round string off to significant digits
	int i_Value = (int)(Value*100);
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
}

bool HuffyPacker::CheckIfStringIsValid(std::string StringToCheck)
{
	for(std::string::iterator it = StringToCheck.begin(); it != StringToCheck.end(); ++it)
	{
	    if(*it != '0' || *it != '0')
	    {
	    	return false;
	    }
	}
	return true;
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
	//Todo, get significant digits from HuffyConstants.h
	return HowBigIsThisInt((int)ValueToAdd*100);
}

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
