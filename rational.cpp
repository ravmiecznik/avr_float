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
char* Rational<uint8_t>::to_str(char *buf) {
	sprintf(buf, "R:%u/%u", nominator, denominator);
	return buf;
}

template<>
char* Rational<int8_t>::to_str(char *buf) {
	sprintf(buf, "R:%d/%d", nominator, denominator);
	return buf;
}

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

template<>
char* Rational<uint32_t>::to_str(char *buf) {
	sprintf(buf, "R:%u/%u", nominator, denominator);
	return buf;
}

template<>
char* Rational<int32_t>::to_str(char *buf) {
	sprintf(buf, "R:%d/%d", nominator, denominator);
	return buf;
}

template<>
char* Rational<uint64_t>::to_str(char *buf) {
	sprintf(buf, "R:%lu/%lu", nominator, denominator);
	return buf;
}

template<>
char* Rational<int64_t>::to_str(char *buf) {
	sprintf(buf, "R:%ld/%ld", nominator, denominator);
	return buf;
}


