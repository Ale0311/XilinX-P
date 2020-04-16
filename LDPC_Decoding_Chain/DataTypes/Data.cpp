/*
 * Data.cpp
 *
 *  Created on: Apr 13, 2020
 *      Author: Oana
 */

#include "Data.h"

Data::Data() {
	// TODO Auto-generated constructor stub

}

Data::~Data() {
	// TODO Auto-generated destructor stub
}

void Data::setValue(bool value){
    this->value = value;
    
}

bool Data::getValue(){
   return this->value;
    
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
