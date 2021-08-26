/*
 * rational.h
 *
 *  Created on: 26 sie 2021
 *      Author: rafal
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <iostream>
#include <stdio.h>
#include <stdint.h>


#define MAX_FLOAT_PRECISION 9

/*
 * GREATEST COMMON DIVISOR
 */
template<typename ret_t, typename in_t>
ret_t gcd(in_t a, in_t b) {
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	while (a != b)
		if (a > b)
			a -= b;
		else
			b -= a;
	return static_cast<ret_t>(a);
}

/////FloatingNum//////////////////////////////////////////////////////////////////////////////////
/*
 * Class to provide string representation of Rational object
 * Rational(1/3) -> FloatingNum(1, 3, 3).to_str((char*)buff) => 1.333
 */
template<class t>
class FloatingNum {
public:
	t integer;
	t remainder;
	uint8_t floating_points;  //! max precision is 9 decimal places
	FloatingNum(t i, t r = 0, uint8_t floating_points = 0) :
			integer(i), remainder(r), floating_points(floating_points) {
	}
	;

public:
	char* to_str(char* s_result);

};

template<typename t>
char* FloatingNum<t>::to_str(char* s_result) {
	char fmt[11] = "%ld.%0";
	sprintf(&fmt[6], "%uld", floating_points);
	fmt[6] = floating_points + 48; //ascii code 48=>0, inject leading zeros to decimal part
	sprintf(s_result, fmt, this->integer, this->remainder);
	return s_result;
}

template<typename t>
FloatingNum<t> to_floating(t nominator, t denominator, uint8_t precision = 1) {
	int sign=1;
	if((nominator < 0 and denominator > 0) or (nominator > 0 and denominator < 0)){
		sign = -1;
	}

	precision= (precision <= MAX_FLOAT_PRECISION) ? precision : MAX_FLOAT_PRECISION;
	int64_t decimal_factor = 1;
	for (uint8_t i = 0; i < precision; i++) {
		decimal_factor *= 10;
	}
	nominator *= decimal_factor;
	t int_part = nominator / denominator;
	t remainder = sign*int_part % decimal_factor;
	return FloatingNum<t>(int_part / decimal_factor, remainder, precision);
}


/////RATIONAL/////////////////////////////////////////////////////////////////////////////////////

/*
 * Class for Rational values calculations
 */
template<typename t>
class Rational {
private:
	void simplify();
public:
	t nominator;
	t denominator;
	Rational(t nom, t denom = 1);
	Rational(const Rational<t>& r) :
			nominator(r.nominator), denominator(r.denominator) {
		simplify();
	}
	;
	Rational(const Rational<t>* r) :
			nominator(r->nominator), denominator(r->denominator) {
		simplify();
	}
	;
	char* to_str(char* buf);
	char* to_float(char* buf, uint8_t precision=2);

	template<typename cast_to>
	operator Rational<cast_to>() {
		return Rational<cast_to>(static_cast<cast_to>(nominator),
				static_cast<cast_to>(denominator));
	}

	void operator*=(const Rational<t> other) {
		nominator *= other.nominator;
		denominator *= other.denominator;
		simplify();
	}

	void operator/=(const Rational<t> other) {
		nominator *= other.denominator;
		denominator *= other.nominator;
		simplify();
	}

	void operator+=(const Rational<t> other) {
		Rational<t> new_r = Rational<t>(this) + Rational<t>(other);
		nominator = new_r.nominator;
		denominator = new_r.denominator;
	}

	void operator-=(const Rational<t> other) {
		Rational<t> new_r = Rational<t>(this)
				+ Rational<t>(-other.nominator, other.denominator);
		nominator = new_r.nominator;
		denominator = new_r.denominator;
	}
};

template<typename t>
Rational<t> operator+(const Rational<t>& a, const Rational<t>& b);

template<typename t>
Rational<t> operator-(const Rational<t>& a, const Rational<t>& b);

template<typename t>
Rational<t> operator*(const Rational<t>& a, const Rational<t>& b);

template<typename t>
Rational<t> operator/(const Rational<t>& a, const Rational<t>& b);


template<typename t>
void Rational<t>::simplify() {
	t ratio = gcd<t>(nominator, denominator);
	nominator /= ratio;
	denominator /= ratio;
	if (denominator < 0) {
		denominator *= -1;
		nominator *= -1;
	}
}

template<typename t>
Rational<t>::Rational(t nom, t denom) :
		nominator(nom), denominator(denom) {
	simplify();
}

template<>
char* Rational<int8_t>::to_str(char *buf);

template<>
char* Rational<uint8_t>::to_str(char *buf);

template<>
char* Rational<int16_t>::to_str(char *buf);

template<>
char* Rational<uint16_t>::to_str(char *buf);

template<>
char* Rational<int32_t>::to_str(char *buf);

template<>
char* Rational<uint32_t>::to_str(char *buf);

template<>
char* Rational<int64_t>::to_str(char *buf);

template<>
char* Rational<uint64_t>::to_str(char *buf);


template<typename t>
Rational<t> operator+(const Rational<t>& a, const Rational<t>& b) {
	t new_denominator = a.denominator * b.denominator;
	return Rational<t>(
			a.denominator * b.nominator + b.denominator * a.nominator,
			new_denominator);
}

template<typename t>
Rational<t> operator-(const Rational<t>& a, const Rational<t>& b) {
	t new_denominator = a.denominator * b.denominator;
	return Rational<t>(
			b.denominator * a.nominator - a.denominator * b.nominator,
			new_denominator);
}

template<typename t>
Rational<t> operator*(const Rational<t>& a, const Rational<t>& b) {
	return Rational<t>(b.nominator * a.nominator, a.denominator * b.denominator);
}

template<typename t>
Rational<t> operator/(const Rational<t>& a, const Rational<t>& b) {
	return Rational<t>(a.nominator * b.denominator, b.nominator * a.denominator);
}

template<typename t>
char* Rational<t>::to_float(char* buff, uint8_t precision){
	FloatingNum<int64_t> fn = to_floating<int64_t>(nominator, denominator, precision);
	return fn.to_str(buff);
}

#endif /* RATIONAL_H_ */
