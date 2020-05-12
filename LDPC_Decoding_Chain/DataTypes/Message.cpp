/*
 * Message.cpp
 *
 *  Created on: Apr 13, 2020
 *      Author: Oana
 */

#include "Message.h"

Message::Message(int nr_bits) {
	// TODO Auto-generated constructor stub
	this->nr_bits = nr_bits;
}

Message::~Message() {
	// TODO Auto-generated destructor stub
}

Message Message::operator+(const Message& b)
{
	Message res = new Message(this->nr_bits);

	res.value = this->value + b.value;
	if(res.value>SAT_VALUE_POS)
	{
		res.value = SAT_VALUE_POS;
	}
	if(res.value<SAT_VALUE_NEG)
	{
		res.value = SAT_VALUE_NEG;
	}

	return res;
}

Message Message::operator-(const Message& b)
{
	Message res = new Message(this->nr_bits);

	res.value = this->value - b.value;
	if(res.value>SAT_VALUE_POS)
	{
		res.value = SAT_VALUE_POS;
	}
	if(res.value<SAT_VALUE_NEG)
	{
		res.value = SAT_VALUE_NEG;
	}

	return res;
}

bool Message::get_sign()
{
	return (this->value & (1<<nr_bits));
}

unsigned char Message::get_magnitude()
{
	if(this->value<0)
	{
		return -(this->value);
	}
	else
	{
		return this->value;
	}
}

Message Message::compare(int nr_messages, Message *list)
{
	Message res=new Message(this->nr_bits);
	bool sign=0;
	unsigned char magnitude=SAT_VALUE_POS;

	for(int i=0;i<nr_messages;i++)
	{
		sign=sign ^ list[i].get_sign();
		if(magnitude>list[i].get_magnitude())
		{
			magnitude = list[i].get_magnitude();
		}
	}
	if(sign == 1)
	{
		res.value = -magnitude;
	}
	else
	{
		res.value = magnitude;
	}

	return res;

}
