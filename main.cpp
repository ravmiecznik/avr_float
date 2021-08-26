/*
 * main.cpp
 *
 *  Created on: 26 sie 2021
 *      Author: rafal
 */


#include <stdio.h>
#include <iostream>
#include "rational.h"


using namespace std;

typedef Rational<uint16_t> Ru16;
typedef Rational<uint32_t> Ru32;
typedef Rational<int16_t> Ri16;

int main(){
	char buffer[100];
	cout << "HELLO" << __FILE__ << endl << endl;

	Rational<uint64_t> R1(3,4);
	cout << "R1: "<< R1.to_str(buffer) << endl;
	cout << "R1: "<< R1.to_float(buffer) << endl;
//	R1: R:3/4
//	R1: 0.75


	Rational<uint16_t> R2(1,3);
	cout << "R2: "<< R2.to_str(buffer) << endl;
	cout << "R2: "<< R2.to_float(buffer) << endl;
//	R2: R:1/3
//	R2: 0.33


	cout << "R1+R2: "<< (R1+(Rational<uint64_t>)R2).to_str(buffer) << endl; //add with cast
	cout << "R1+R2: "<< (R1+(Rational<uint64_t>)R2).to_float(buffer) << endl;
//	R1+R2: R:13/12
//	R1+R2: 1.08


	cout << "R1+R2: "<< (Ri16(5,3) + Ri16(6,3)).to_str(buffer) << endl;
	cout << "R1+R2: "<< (Ri16(5,3) + Ri16(6,3)).to_float(buffer) << endl;
//	R1+R2: R:11/3
//	R1+R2: 3.66

	Ri16 R3(5,3);
	R3 += Ri16(6,3);
	cout << "R1+=R2: "<< R3.to_str(buffer) << endl;
	cout << "R1+=R2: "<< R3.to_float(buffer) << endl;
//	R1+=R2: R:11/3
//	R1+=R2: 3.66

	return 0;
}
