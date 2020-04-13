/*
 * Data.h
 *
 *  Created on: Apr 13, 2020
 *      Author: Oana
 */

#ifndef DATATYPES_DATA_H_
#define DATATYPES_DATA_H_


//class used for encoding
class Data {
public:
	bool value;

	Data(bool value);
	~Data();

	Data operator+(const Data& b);
	Data operator-(const Data& b);
	Data operator*(const Data& b);

};

#endif /* DATATYPES_DATA_H_ */
