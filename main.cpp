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
	cout << Ri16(4,-3).to_float(buffer, 30) << endl;
	cout << Ri16(4,3).to_str(buffer) << endl;
	return 0;
}
