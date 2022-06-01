#pragma once
#include "motors.h"
#include "PS2_controller.h"

#define SPEED 3000
#define TURNING_SPEED 1000

/**
 * @brief Control the movement of the robot
 * 
 * @param pressed The pointer to check whether
 *                a button is pressed in the loop
 */
void MovementControl(bool &pressed) {
  if (ps2x.Button(PSB_PAD_UP)) // tương tự như trên kiểm tra nút Lên (PAD UP)
  { 
    #ifdef DEBUG
    Serial.println("Up Pressed");
    #endif
    pressed = true;
    setMotor(0, SPEED);
    setMotor(1, SPEED);
  }
  if (ps2x.Button(PSB_PAD_RIGHT))
  {
    #ifdef DEBUG
    Serial.println("Right Pressed");
    #endif
    pressed = true;
    setMotor(0, TURNING_SPEED);
    setMotor(1, -TURNING_SPEED);
  }
  if (ps2x.Button(PSB_PAD_LEFT))
  {
    #ifdef DEBUG
    Serial.println("Left Pressed");
    #endif
    pressed = true;
    setMotor(0, -TURNING_SPEED);
    setMotor(1, TURNING_SPEED);
  }
  if (ps2x.Button(PSB_PAD_DOWN))
  {
    #ifdef DEBUG
    Serial.println("Down Pressed");
    #endif
    pressed = true;
    setMotor(0, -SPEED);
    setMotor(1, -SPEED);
    //setPWMMotors(SPEED, 0, SPEED, 0);
  }
}

/**
 * @brief Control the servos and other motors of the robot
 * 
 * @param pressed The pointer to check whether
 *                a button is pressed in the loop
 */
void ServoControl(bool &pressed){
  if (ps2x.Button(PSB_L1)){
    #ifdef DEBUG
    Serial.println("L1 pressed");
    #endif
    pressed = true;
    setMotor(2, SPEED);
    setMotor(3, -SPEED);
  }
  if (ps2x.Button(PSB_CIRCLE)){
    #ifdef DEBUG
    Serial.println("Circle pressed");
    #endif
    setServo(7, 20);
    pressed = true; 
  }
}