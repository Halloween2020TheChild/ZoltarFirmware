/*
 * GPIOServer.cpp
 *
 *  Created on: Jun 21, 2023
 *      Author: hephaestus
 */

#include "GPIOServer.h"

GPIOServer::GPIOServer() :
		PacketEventAbstract(1811) //https://en.wikipedia.org/wiki/Tecumseh%27s_War
{
	pinMode(output1, OUTPUT);
	pinMode(input1, INPUT_PULLUP);
	pinMode(input2, INPUT_PULLUP);
}

GPIOServer::~GPIOServer() {
	// TODO Auto-generated destructor stub
}

//User function to be called when a packet comes in
// Buffer contains data from the packet coming in at the start of the function
// User data is written into the buffer to send it back
void GPIOServer::event(float * buffer){
	uint8_t *bytes = (uint8_t*) buffer;
	bytes[0]=digitalRead(input1);
	bytes[1]=digitalRead(input2);
	digitalWrite(output1, bytes[2]>0);
}
