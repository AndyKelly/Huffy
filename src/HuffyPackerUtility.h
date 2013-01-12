/*
 * HuffyPackerUtility.h
 *
 *  Created on: Jan 11, 2013
 *      Author: hal
 */

#ifndef HUFFYPACKERUTILITY_H_
#define HUFFYPACKERUTILITY_H_
#include <list>
#include <string>

class HuffyPackerUtility {
public:
	HuffyPackerUtility();
	virtual ~HuffyPackerUtility();
	void WriteInt(int, int);
	int ReadInt(int);
private:
	void WriteIntToTempBuffer(int,int);
	int readIntFromTempBuffer(int);
	void WriteBitToTempBuffer(int);
	int ReadBitFromTempBuffer();
	int getBit(void);
	int CurrentTempBit;
	int CurrentTempByte;
	int CurrentTempReadBit;
	int CurrentTempReadByte;
	//Todo something sensible here
	unsigned char TempBuffer[100];

};

#endif /* HUFFYPACKERUTILITY_H_ */
