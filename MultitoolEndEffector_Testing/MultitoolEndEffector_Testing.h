// Multi-tool End Effector Testing Header

#ifndef _MultitoolEndEffector
#define _MultitoolEndEffector

#include "RoveComm.h"
#include "Servo.h"

RoveCommEthernetUdp RoveComm;

	//Pinout
#define SERVO_1_CRTL_PIN	PM_7
#define SERVO_2_CRTL_PIN	PA_7
#define SERVO_3_CRTL_PIN	PM_6
#define LASER_CTR_PIN		PN_3
    //Delays
#define ROVECOMM_DELAY     	5
	//Servo Positions
#define SERVO_1_RETRACTED	180
#define SERVO_2_RETRACTED	175
#define SERVO_3_RETRACTED	155
#define SERVO_1_SELECTED	10
#define SERVO_2_SELECTED	10
#define SERVO_3_SELECTED	10

void setup();
void loop();

#endif