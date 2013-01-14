/*
 * BitString.cpp
 *
 *  Created on: Jan 12, 2013
 *      Author: hal
 */
#include <algorithm>
#include "BitString.h"

BitString::BitString()
{
	m_Contents = "";
}

BitString::~BitString()
{
}

void BitString::Reverse()
{
	std::reverse(m_Contents.begin(), m_Contents.end());
}

void BitString::WriteOne()
{
	m_Contents += "1";
}

void BitString::WriteZero()
{
	m_Contents += "0";
}

std::string BitString::GetValue()
{
	return m_Contents;
}

