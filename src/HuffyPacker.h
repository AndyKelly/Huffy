/*
 * HuffyPacker.h
 *
 *  Created on: Jan 12, 2013
 *      Author: hal
 */

#ifndef HUFFYPACKER_H_
#define HUFFYPACKER_H_
#include <list>
#include <string>
#include "BitString.h"
class HuffyPacker {
public:
	std::string ReturnStringTest();
	HuffyPacker();
	~HuffyPacker();
	BitString GetUpdateAsBitsetString();
	void ApplyUpdateString(std::string);
	std::string ReturnUpdateString();
	int HowBigIsThisInt(int);
	int HowBigIsThisFloat(float);
	int ReadIntAtIndex(int, int);
	void AddBoolValueToUpdate(bool);
	void AddFloatValueToUpdate(int, float);
	int ReadIntValueFromBuffer(int);
	void AddIntValueToUpdate(int, int);
	void AddBitsUsedToUpdate(std::string);
	void AddTypetoUpdate(std::string);
	void AddIDtoUpdate(std::string);
	void WriteBitsetStyleStringToBuffer(std::string);
	bool CheckIfStringIsValid(std::string StringToCheck);

	void WriteOneToBuffer();
	void WriteZeroToBuffer();
	void writeInt(int,int);
	int readInt(int);
	void WriteBitToBuffer(int);
	int ReadBitFromBuffer();

	int CurrentBit;
	int CurrentByte;
	int CurrentReadBit;
	int CurrentReadByte;

	//Todo change to something sensible, Huffy constants.h
	unsigned char Buffer[1000];
};

#endif /* HUFFYPACKER_H_ */
