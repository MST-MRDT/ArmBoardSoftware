// Multi-tool End Effector Testing Header

#ifndef _MultitoolEndEffector
#define _MultitoolEndEffector

#include "RoveComm.h"
#include "Servo.h"

RoveCommEthernetUdp RoveComm;

	//Pinout
#define SERVO_1_CRTL_PIN   PM_7
#define SERVO_2_CRTL_PIN   PA_7
#define SERVO_3_CRTL_PIN   PM_6
#define LASER_CRTL_PIN		PN_3
#define SOLENOID_CRTL_PIN 	PP_2
#define SW1_IND_PIN			PH_0
#define SW2_IND_PIN			PH_1
#define SW3_IND_PIN			PK_6
#define SWE_IND_PIN			PK_7
    //Delays
#define ROVECOMM_DELAY     	10
	//Servo Positions
#define SERVO_1_RETRACTED	155
#define SERVO_2_RETRACTED	175
#define SERVO_3_RETRACTED	155
#define SERVO_1_SELECTED	10
#define SERVO_2_SELECTED	10
#define SERVO_3_SELECTED	10
#define SERVO_1_REST       1470 //1470 is boundary in which it stops drifting to right; 1476 is boundary in which it stops drifting left; 1473 is middle, no drifting
#define SERVO_2_REST       1400 //Main cam pitch facing up. Can lower value to face further upwards.
#define SERVO_3_REST       1830 //Drive cam pan facing forward.
void setup();
void loop();

#endif