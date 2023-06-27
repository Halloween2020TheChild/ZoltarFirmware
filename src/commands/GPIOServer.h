/*
 * GPIOServer.h
 *
 *  Created on: Jun 21, 2023
 *      Author: hephaestus
 */

#ifndef SRC_COMMANDS_GPIOSERVER_H_
#define SRC_COMMANDS_GPIOSERVER_H_

#include <SimplePacketComs.h>
#include "../LewanSoulPlanner.h"

#include <Arduino.h>
#define input1 27
#define input2 17
#define output1 13

class GPIOServer: public PacketEventAbstract  {
public:
	GPIOServer();
	virtual ~GPIOServer();
	//User function to be called when a packet comes in
	// Buffer contains data from the packet coming in at the start of the function
	// User data is written into the buffer to send it back
	void event(float * buffer);
};

#endif /* SRC_COMMANDS_GPIOSERVER_H_ */
