/*
 * BitString.h
 *
 *      Author: Andy Kelly
 */

#ifndef BITSTRING_H_
#define BITSTRING_H_
#include <string>
class BitString {
public:
	BitString();
	virtual ~BitString();
	void WriteOne();
	void WriteZero();
	void Reverse();
	std::string GetValue();
private:
	std::string m_Contents;
	bool m_Initalised;
};

#endif /* BITSTRING_H_ */
