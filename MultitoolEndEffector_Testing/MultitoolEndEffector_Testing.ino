// Multi-tool End Effector Testing Main

#include "MultitoolEndEffector_Testing.h"
#include "RoveComm.h"
#include <Energia.h>

#define SOLENOID_PIN PP_2

Servo Servos[3];

void setup()
{
	Serial.begin(9600);

	RoveComm.begin(RC_ARMBOARD_FOURTHOCTET);
  delay(ROVECOMM_DELAY);

  pinMode(LASER_CTR_PIN, OUTPUT);

  digitalWrite(LASER_CTR_PIN, HIGH);

  pinMode(SOLENOID_PIN, OUTPUT);

  digitalWrite(SOLENOID_PIN, HIGH);

  Servos[0].attach(SERVO_1_CRTL_PIN);
  Servos[1].attach(SERVO_2_CRTL_PIN);
  Servos[2].attach(SERVO_3_CRTL_PIN);

  Servos[0].write(SERVO_1_RETRACTED);
  Servos[1].write(SERVO_2_RETRACTED);
  Servos[2].write(SERVO_3_RETRACTED);

	Serial.println("Multi-tool Setup Complete.");
}

void loop()
{
	char incomingByte;
  	if(Serial.available() > 0)
  	{
    	incomingByte = Serial.read();
    	Serial.print(incomingByte);
    	switch (incomingByte)                    ///(data_id) //either 0 or 1 
    	{   
        	//Don't do anything for data_id zero 
        	case '1': //No tool selected
        		Serial.println("No tool selected");
        		Servos[0].write(SERVO_1_RETRACTED);
  				  Servos[1].write(SERVO_2_RETRACTED);
  				  Servos[2].write(SERVO_3_RETRACTED);
        	  	break;
          case '2':
            break;
          case '3':
            break;
          case '4':
            break;
          case '5':
            digitalWrite(LASER_CTR_PIN, HIGH);
            break;
          case '6': 
            digitalWrite(LASER_CTR_PIN, LOW);
            break;
      }
    }
}