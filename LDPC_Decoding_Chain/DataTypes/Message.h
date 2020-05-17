/*
 * Message.h
 *
 *  Created on: Apr 13, 2020
 *      Author: Oana
 */

#ifndef DATATYPES_MESSAGE_H_
#define DATATYPES_MESSAGE_H_

class Message {
public:
	int nr_bits;
	char value;

	const char SAT_VALUE_POS = 2**(nr_bits-1)-1;
	const char SAT_VALUE_NEG = -(2**nr_bits-1);

	Message(int nr_bits);
	~Message();

	Message operator+(const Message& b);
	Message operator-(const Message& b);

	bool get_sign();
	unsigned char get_magnitude();

	Message compare(int nr_messages, Message *list);
};

#endif /* DATATYPES_MESSAGE_H_ */
