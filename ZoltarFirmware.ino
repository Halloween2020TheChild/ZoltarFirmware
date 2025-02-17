/**@file template.ino */
#include <SimplePacketComs.h>
#include <lx16a-servo.h>
#include <Esp32WifiManager.h>
#include <Esp32SimplePacketComs.h>
#include <server/NameCheckerServer.h>
#include "src/commands/GetPIDData.h"
#include "src/commands/SetPIDSetpoint.h"
#include <ESP32Servo.h>
#include "src/LewanSoulPlanner.h"
#include "src/commands/GPIOServer.h"

//Create a wifi manager
static WifiManager manager;
static UDPSimplePacket coms;
static LewanSoulPlanner * planner1=NULL;
static LewanSoulPlanner * planner2=NULL;
static String name ="Zoltar";
static TaskHandle_t complexHandlerTaskUS;
Servo eyelid;
Servo lift;
void MotorThread0(void * param){
	Serial.println("Starting the Motor loop thread");

	while (1) {
		vTaskDelay(1); //sleep 10ms
		if(planner2!=NULL&&manager.getState() == Connected)
			planner2->loop();
	}
	Serial.println("ERROR Motor thread died!");
}
void MotorThread1(void * param){
	Serial.println("Starting the Motor loop thread");

	while (1) {
		vTaskDelay(1); //sleep 10ms
		if(planner1!=NULL &&manager.getState() == Connected)
			planner1->loop();
	}
	Serial.println("ERROR Motor thread died!");
}

void setup() {
	eyelid.attach(12);
	lift.attach(14);
	eyelid.write(90);
	lift.write(90);

	planner1 =  new LewanSoulPlanner(7,0);
	planner2 =  new LewanSoulPlanner(7,1);

	coms.attach((PacketEvent *)new SetPIDSetpoint(7,planner1,planner2));
	coms.attach((PacketEvent *)new GetPIDData(7,planner1,planner2));
	coms.attach((PacketEvent *)new GPIOServer());
	coms.attach(new NameCheckerServer(&name));
	xTaskCreatePinnedToCore(MotorThread0, "Motor Thread 0", 8192, NULL, 1, // low priority timout thread
					&complexHandlerTaskUS, 1);
	xTaskCreatePinnedToCore(MotorThread1, "Motor Thread 1", 8192, NULL, 1, // low priority timout thread
						&complexHandlerTaskUS, 1);
	manager.setup();

}

void loop() {
	// read the serial port for new passwords and maintain connections
	manager.loop();
	//if (manager.getState() == Connected) {
		if(planner1->state == running ||planner1->state==WaitingToRun||planner1->state==disabled)
			if(planner2->state == running ||planner2->state==WaitingToRun||planner2->state==disabled)
				coms.server();
	//}
}
