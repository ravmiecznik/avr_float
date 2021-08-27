/*
 * rational.h
 *
 *  Created on: 26 sie 2021
 *      Author: rafal
 */

#ifndef FRACTION_H_
#define FRACTION_H_

#include <iostream>
#include <stdio.h>
#include <stdint.h>


#define MAX_FLOAT_PRECISION 9
template<typename t>
/*
 * Example:
 * map(Ru32(1,2), Ru32(0,1), Ru32(100,1), Ru32(0,1), Ru32(500,1))
 * result: 2.5
 */
t map(t x, t in_min, t in_max, t out_min, t out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


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
class Fraction {
private:
	;
public:
	void simplify();
	t nominator;
	t denominator;
	Fraction(t nom, t denom = 1);
//	Rational(t nom): nominator(nom), denominator(1) {
//		simplify();
//	};
	Fraction(const Fraction<t>& r) :
			nominator(r.nominator), denominator(r.denominator) {
		simplify();
	}
	;
	Fraction(const Fraction<t>* r) :
			nominator(r->nominator), denominator(r->denominator) {
		simplify();
	}
	;
	char* to_str(char* buf);
	char* to_float(char* buf, uint8_t precision=2);

	template<typename cast_to>
	operator Fraction<cast_to>() {
		return Fraction<cast_to>(static_cast<cast_to>(nominator),
				static_cast<cast_to>(denominator));
	}

	void operator*=(const Fraction<t> other) {
		nominator *= other.nominator;
		denominator *= other.denominator;
		simplify();
	}

	void operator/=(const Fraction<t> other) {
		nominator *= other.denominator;
		denominator *= other.nominator;
		simplify();
	}

	void operator+=(const Fraction<t> other) {
		Fraction<t> new_r = Fraction<t>(this) + Fraction<t>(other);
		nominator = new_r.nominator;
		denominator = new_r.denominator;
	}

	void operator-=(const Fraction<t> other) {
		Fraction<t> new_r = Fraction<t>(this)
				+ Fraction<t>(-other.nominator, other.denominator);
		nominator = new_r.nominator;
		denominator = new_r.denominator;
	}
};

template<typename t>
Fraction<t> operator+(const Fraction<t>& a, const Fraction<t>& b);

template<typename t>
Fraction<t> operator-(const Fraction<t>& a, const Fraction<t>& b);

template<typename t>
Fraction<t> operator*(const Fraction<t>& a, const Fraction<t>& b);

template<typename t>
Fraction<t> operator/(const Fraction<t>& a, const Fraction<t>& b);


template<typename t>
void Fraction<t>::simplify() {
	t ratio = 1;
	if(nominator !=0 ){
		ratio = gcd<t>(nominator, denominator);
	}
	nominator /= ratio;
	denominator /= ratio;
	if (denominator < 0) {
		denominator *= -1;
		nominator *= -1;
	}
}

template<typename t>
Fraction<t>::Fraction(t nom, t denom) :
		nominator(nom), denominator(denom) {
	simplify();
}

template<>
char* Fraction<int8_t>::to_str(char *buf);

template<>
char* Fraction<uint8_t>::to_str(char *buf);

template<>
char* Fraction<int16_t>::to_str(char *buf);

template<>
char* Fraction<uint16_t>::to_str(char *buf);

template<>
char* Fraction<int32_t>::to_str(char *buf);

template<>
char* Fraction<uint32_t>::to_str(char *buf);

template<>
char* Fraction<int64_t>::to_str(char *buf);

template<>
char* Fraction<uint64_t>::to_str(char *buf);


template<typename t>
Fraction<t> operator+(const Fraction<t>& a, const Fraction<t>& b) {
	t new_denominator = a.denominator * b.denominator;
	return Fraction<t>(
			a.denominator * b.nominator + b.denominator * a.nominator,
			new_denominator);
}

template<typename t>
Fraction<t> operator-(const Fraction<t>& a, const Fraction<t>& b) {
	t new_denominator = a.denominator * b.denominator;
	return Fraction<t>(
			b.denominator * a.nominator - a.denominator * b.nominator,
			new_denominator);
}

template<typename t>
Fraction<t> operator*(const Fraction<t>& a, const Fraction<t>& b) {
	return Fraction<t>(b.nominator * a.nominator, a.denominator * b.denominator);
}


template<typename t>
Fraction<t> operator*(const Fraction<t>& a, uint32_t b) {
	return Fraction<t>(b * a.nominator, a.denominator);
}

template<typename t>
Fraction<t> operator*(uint32_t b, const Fraction<t>& a) {
	return Fraction<t>(b * a.nominator, a.denominator);
}

template<typename t>
Fraction<t> operator/(const Fraction<t>& a, const Fraction<t>& b) {
	return Fraction<t>(a.nominator * b.denominator, b.nominator * a.denominator);
}

template<typename t>
char* Fraction<t>::to_float(char* buff, uint8_t precision){
	FloatingNum<int64_t> fn = to_floating<int64_t>(nominator, denominator, precision);
	return fn.to_str(buff);
}

#endif /* FRACTION_H_ */
