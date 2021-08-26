/*
 * rational.cpp
 *
 *  Created on: 26 sie 2021
 *      Author: rafal
 */

#include "rational.h"

/*
 * GREATEST COMMON DIVISOR
 */


template<>
char* Rational<uint16_t>::to_str(char *buf) {
	sprintf(buf, "R:%u/%u", nominator, denominator);
	return buf;
}

template<>
char* Rational<int16_t>::to_str(char *buf) {
	sprintf(buf, "R:%d/%d", nominator, denominator);
	return buf;
}


