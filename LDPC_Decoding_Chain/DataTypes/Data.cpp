/*
 * Data.cpp
 *
 *  Created on: Apr 13, 2020
 *      Author: Oana
 */

#include "Data.h"

Data::Data(bool value) {
	// TODO Auto-generated constructor stub
	this->value = value;
}

Data::~Data() {
	// TODO Auto-generated destructor stub
}

Data Data::operator*(const Data &b)
{
	Data res;

	res.value= this->value & b.value;

	return res;
}

Data Data::operator+(const Data &b)
{
	Data res;

	res.value= this->value ^ b.value;

	return res;
}

Data Data::operator-(const Data &b)
{
	Data res;

	res.value= this->value ^ b.value;

	return res;
}
