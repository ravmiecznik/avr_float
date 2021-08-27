/*
 * rational.cpp
 *
 *  Created on: 26 sie 2021
 *      Author: rafal
 */

#include "fraction.h"

/*
 * GREATEST COMMON DIVISOR
 */

template<>
char* Fraction<uint8_t>::to_str(char *buf) {
	sprintf(buf, "R:%u/%u", nominator, denominator);
	return buf;
}

template<>
char* Fraction<int8_t>::to_str(char *buf) {
	sprintf(buf, "R:%d/%d", nominator, denominator);
	return buf;
}

template<>
char* Fraction<uint16_t>::to_str(char *buf) {
	sprintf(buf, "R:%u/%u", nominator, denominator);
	return buf;
}

template<>
char* Fraction<int16_t>::to_str(char *buf) {
	sprintf(buf, "R:%d/%d", nominator, denominator);
	return buf;
}

template<>
char* Fraction<uint32_t>::to_str(char *buf) {
	sprintf(buf, "R:%u/%u", nominator, denominator);
	return buf;
}

template<>
char* Fraction<int32_t>::to_str(char *buf) {
	sprintf(buf, "R:%d/%d", nominator, denominator);
	return buf;
}

template<>
char* Fraction<uint64_t>::to_str(char *buf) {
	sprintf(buf, "R:%lu/%lu", nominator, denominator);
	return buf;
}

template<>
char* Fraction<int64_t>::to_str(char *buf) {
	sprintf(buf, "R:%ld/%ld", nominator, denominator);
	return buf;
}


