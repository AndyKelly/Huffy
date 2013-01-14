/*
 * HuffyPackerUtility.h
 *
 *      Author: Andy Kelly
 */

#ifndef HUFFYPACKERUTILITY_H_
#define HUFFYPACKERUTILITY_H_
#include <list>
#include <string>
#include "HuffyConstants.h"

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
	unsigned char TempBuffer[BUFFER_SIZE];

};

#endif /* HUFFYPACKERUTILITY_H_ */
