/*
 * BitString.h
 *
 *  Created on: Jan 12, 2013
 *      Author: hal
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
	std::string GetValue();
private:
	std::string m_Contents;
	bool m_Initalised;
};

#endif /* BITSTRING_H_ */
