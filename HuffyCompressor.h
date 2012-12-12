#pragma once
#define BufferLimit 256
class HuffyCompressor
{
public:
	HuffyCompressor(void);
	~HuffyCompressor(void);
	static void HuffyCompressor::AddIntToOutStream(int);
	static int HuffyCompressor::HowManyBitsToStoreThis(int);
	static int HuffyCompressor::HowManyBitsToStoreThis(float);
private:
	static void HuffyCompressor::WriteIntToBuffer(int);
	static int HuffyCompressor::ReadIntFromBuffer(void);
	static void HuffyCompressor::writeInt(int,int);
	static int HuffyCompressor::readInt(int);
	static int CurrentBit;
	static int CurrentByte;
	static int CurrentReadBit;
	static int CurrentReadByte;
	static unsigned char Buffer[BufferLimit]; 
};