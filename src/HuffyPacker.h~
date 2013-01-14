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
#include "HuffyConstants.h"
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
	float ReadFloatAtIndex(int, int);
	bool ReadBoolAtIndex(int);
	void AddBoolValueToUpdate(bool);
	void AddFloatValueToUpdate(int, float);
	int ReadIntValueFromBuffer(int);
	void AddIntValueToUpdate(int, int);
	void AddBitsUsedToUpdate(std::string);
	void AddTypetoUpdate(std::string);
	void AddIDtoUpdate(std::string);
	void WriteBitsetStyleStringToBuffer(std::string);
	bool CheckIfStringIsValid(std::string StringToCheck);
private:
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

	unsigned char Buffer[BUFFER_SIZE];
};

#endif /* HUFFYPACKER_H_ */
