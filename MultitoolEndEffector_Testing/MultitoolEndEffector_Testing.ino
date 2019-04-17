// Multi-tool End Effector Testing Main

#include "MultitoolEndEffector_Testing.h"
#include "RoveComm.h"
#include <Energia.h>


Servo Servos[3];

void setup()
{
	Serial.begin(9600);
  delay(ROVECOMM_DELAY);

	RoveComm.begin(RC_ARMBOARD_FOURTHOCTET);
  delay(ROVECOMM_DELAY);

  //pinMode(LASER_CRTL_PIN, OUTPUT);
  pinMode(SOLENOID_CRTL_PIN, OUTPUT);
  pinMode(SW1_IND_PIN, OUTPUT);
  pinMode(SW2_IND_PIN, OUTPUT);
  pinMode(SW3_IND_PIN, OUTPUT);
  pinMode(SWE_IND_PIN, OUTPUT);

  //digitalWrite(LASER_CRTL_PIN, HIGH);
  digitalWrite(SOLENOID_CRTL_PIN, LOW);
  digitalWrite(SW1_IND_PIN, LOW);
  digitalWrite(SW2_IND_PIN, LOW);
  digitalWrite(SW3_IND_PIN, LOW);
  digitalWrite(SWE_IND_PIN, LOW);

  Servos[0].attach(SERVO_1_CRTL_PIN);
  Servos[1].attach(SERVO_2_CRTL_PIN);
  Servos[2].attach(SERVO_3_CRTL_PIN);

  Servos[0].write(SERVO_1_RETRACTED); //tried Servos[0].writeMicroseconds(1500); and still knothing on PM_7 pin.
  Servos[1].write(SERVO_2_RETRACTED);
  Servos[2].write(SERVO_3_RETRACTED);

	Serial.println("Multi-tool Setup Complete.");
}

void loop()
{
  //Servos[0].write(SERVO_1_RETRACTED);
	char incomingByte;
  	if(Serial.available() > 0)
  	{
    	incomingByte = Serial.read();
    	Serial.print(incomingByte);
    	switch (incomingByte)   
    	{   
        	//Don't do anything for data_id zero 
        	case '1': //No tool selected
        		Serial.println("No tool selected");
        		Servos[0].write(SERVO_1_RETRACTED);
  				  Servos[1].write(SERVO_2_RETRACTED);
  				  Servos[2].write(SERVO_3_RETRACTED);
        	  	break;
          case '2':
            Serial.println("Typing tool selected");
            Servos[0].write(SERVO_1_SELECTED);
            Servos[1].write(SERVO_2_RETRACTED);
            Servos[2].write(SERVO_3_RETRACTED);
            break;
          case '3':
            Serial.println("Hex tool selected");
            Servos[0].write(SERVO_1_RETRACTED);
            Servos[1].write(SERVO_2_SELECTED);
            Servos[2].write(SERVO_3_RETRACTED);
            break;
          case '4':
            Serial.println("Screwdriver tool selected");
            Servos[0].write(SERVO_1_RETRACTED);
            Servos[1].write(SERVO_2_RETRACTED);
            Servos[2].write(SERVO_3_SELECTED);
            break;
          case '5':
            //digitalWrite(LASER_CRTL_PIN, LOW);
            digitalWrite(SOLENOID_CRTL_PIN, LOW); //Solenoid off
            break;
          case '6': 
            //digitalWrite(LASER_CRTL_PIN, HIGH);
            digitalWrite(SOLENOID_CRTL_PIN, HIGH); //Solenoid actuates
            digitalWrite(SW1_IND_PIN, HIGH);
            delay(250);
            digitalWrite(SOLENOID_CRTL_PIN, LOW); //Solenoid actuates
            digitalWrite(SW1_IND_PIN, LOW);
            break;
      }
    }
}