/*
 * BTM7752GwithPCA9685.cpp
 *
 *  Created on: Dec 7, 2017
 *      Author: elive
 */

#include <stdint.h>
#include <BTM7752GwithPCA9685.h>
#include "RoveJointUtilities.h"

static bool initialized = false;
static const RoveI2C_Speed DEFAULT_SPEED = I2CSPEED_FAST;
static const uint8_t RESET_ADDRESS = 0b00000000;
static const uint8_t RESET_MSG =     0b000001100;
static const uint8_t M1REGISTER_ADDRESS = 0b00000000;
static const uint8_t M1REGISTER_MSG =     0b00100000; //this will turn off sleep mode, turn on auto increment
static const uint16_t PWM_MAX = 4095;
static const uint8_t MAX_MOTOR_CHANNELS = 7;

BTM7752GwithPCA9685::BTM7752GwithPCA9685(uint8_t chipAdd, uint8_t motorInd, uint8_t motorEnablePin, uint8_t i2cNenablePin, uint8_t i2cIndex, uint8_t clockPin, uint8_t dataPin, bool inverted)
: OutputDevice(InputPowerPercent, inverted)
{
  chipAddress = chipAdd;
  motorIndex = motorInd;
  i2cHandle = i2cInit(i2cIndex, DEFAULT_SPEED, clockPin, dataPin);
  motorEnPin = motorEnablePin;

  if(motorInd > MAX_MOTOR_CHANNELS)
  {
    debugFault("Error in BTM7752GwithPCA9685 constructor: motor index out of bounds");
  }

  if(!initialized)
  {
    roveI2cSend(i2cHandle, RESET_ADDRESS, RESET_MSG);
    delay(1);
    roveI2cSendReg(i2cHandle, chipAddress, M1REGISTER_ADDRESS, M1REGISTER_MSG);
    delay(1);
    digitalPinWrite(i2cNenablePin, LOW);
    initialized = true;
  }


}

BTM7752GwithPCA9685::~BTM7752GwithPCA9685()
{
}

void BTM7752GwithPCA9685::move(const long movement)
{
  if(enabled && movement != 0)
  {
    currentMove = movement;
    long mov = movement;
    long offRegNum; //the off register determines when the high pulse turns off in pwm
    long onRegNum = 0; //on register is when high pulse turns on. Make it 0 so it just starts on, then turns off when offRegNum says to
    uint8_t channelRegisterBaseOffset;
    uint8_t offMsg[4] = {0, 0, 0, 0};

    if(invert)
    {
      mov *= -1;
    }

    offRegNum = (mov * PWM_MAX) / POWERPERCENT_MAX;
    channelRegisterBaseOffset = 6 + 8*motorIndex;

    //figure out which channel to send to, and set the opposite channel to 0
    if(mov > 0)
    {
      roveI2cSendBurstReg(i2cHandle, chipAddress, channelRegisterBaseOffset+4, offMsg, 4);
      channelRegisterBaseOffset += 0;
    }
    else if(mov < 0)
    {
      roveI2cSendBurstReg(i2cHandle, chipAddress, channelRegisterBaseOffset, offMsg, 4);
      channelRegisterBaseOffset += 4;
    }

    uint8_t msg[4] = {onRegNum, onRegNum, (uint8_t)offRegNum, ((uint8_t)(offRegNum>>8))};
    roveI2cSendBurstReg(i2cHandle, chipAddress, channelRegisterBaseOffset, msg, 4);
  }
  else
  {
    stop();
  }
}

void BTM7752GwithPCA9685::setPower(bool power)
{
  enabled = power;
  digitalPinWrite(motorEnPin, power);
}

void BTM7752GwithPCA9685::stop()
{
  //moving the motor at 0 speed, aka "stopping" it
  long offRegNum; //the off register determines when the high pulse turns off in pwm
  long onRegNum = 0; //on register is when high pulse turns on. Make it 0 so it just starts on, then turns off when offRegNum says to
  uint8_t channelRegisterBaseOffset;

  currentMove = 0;

  offRegNum = 0;
  channelRegisterBaseOffset = 6 + 8*motorIndex;

  uint8_t msg[4] = {onRegNum, onRegNum, (uint8_t)offRegNum, ((uint8_t)(offRegNum>>8))};
  roveI2cSendBurstReg(i2cHandle, chipAddress, channelRegisterBaseOffset, msg, 4);
  roveI2cSendBurstReg(i2cHandle, chipAddress, channelRegisterBaseOffset+4, msg, 4); //send to forward and reverse channels
}

long BTM7752GwithPCA9685::getCurrentMove()
{
  return currentMove;
}
