/*
 * HuffyConstants.h
 *
 *      Author: Andy Kelly
 */

#ifndef HUFFYCONSTANTS_H_
#define HUFFYCONSTANTS_H_

#include <string>
static const int BUFFER_SIZE = 1000;
static const int SIGNIFICANT_DIGITS_MULTIPLIER = 100;
static const int BYTE_SIZE = 8;
static const std::string UPDATE_RESPONSE = "U";
static const std::string ERROR = "E";
enum e_HuffyTypes
{
	e_HuffyNonLeaf = 0,
	e_HuffyInt,
	e_HuffyFloat,
	e_HuffyBool,
	e_EndOfMessage,
	e_AdaptRequest
};
#endif /* HUFFYCONSTANTS_H_ */
