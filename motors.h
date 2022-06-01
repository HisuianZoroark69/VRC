#pragma once
#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PWM 0
#define MAX_PWM 4095
#define FREQUENCY 1500
#define SERVO_FREQ 50
#define DC_FREQ 1500

#define SERVOMIN  190 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOSTOPMIN 266
#define SERVOSTOPMAX 284 // This is the middle?
#define SERVOMAX  360 // This is the 'maximum' pulse length count (out of 4096)

#define FORWARD true
#define BACKWARD false

//#define SDA 3
//#define SCL 0
// PWM channels of pca9685 0-16
#define PWM_CHANNELJ2 7
#define PWM_CHANNELJ1 6
#define PWM_CHANNELJ6 5
#define PWM_CHANNELJ5 4
#define PWM_CHANNELJ4 3
#define PWM_CHANNELJ3 2
#define PWM_CHANNEL11 8 
#define PWM_CHANNEL12 9
#define PWM_CHANNEL21 10
#define PWM_CHANNEL22 11
#define PWM_CHANNEL31 12
#define PWM_CHANNEL32 13
#define PWM_CHANNEL41 14
#define PWM_CHANNEL42 15

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int currentFreq;

void setPWMFreq(int freq){
  if(freq != currentFreq)
  {
    currentFreq = freq;
    pwm.setPWMFreq(freq);
  }
}

/**
 * @brief Set the servo speed.
 * 
 * @param servoId The pwm channel of the servo.
 * @param c The speed of the servo, ranging from -100 to 100 (percent).
 *          Positive value will turn the servo clockwise and vice versa.
 */
void setServo(int servoId, int c){
  setPWMFreq(SERVO_FREQ);
  c = -c;
  int pulse = (c < 0 ? SERVOSTOPMIN : SERVOSTOPMAX) + 0.76 * c;
  pwm.setPWM(servoId, 0, pulse);
}
/**
 * @brief Set the DC motor speed
 * 
 * @param motorId The id of the motor's port, ranging 0 to 4
 * @param c The speed of the motor, ranging -4096 to 4096
 */
void setMotor(int motorId, int c){
  setPWMFreq(DC_FREQ);
  if(c == 0){
    pwm.setPWM(8 + motorId * 2, 4096, 0);
    pwm.setPWM(9 + motorId * 2, 4096, 0);
    return;
  }
  else if(c > 0){
    pwm.setPWM(8 + motorId * 2, 0, MAX_PWM - c);
    pwm.setPWM(9 + motorId * 2, 4096, 0);
  }
  else {
    pwm.setPWM(8 + motorId * 2, 4096, 0);
    pwm.setPWM(9 + motorId * 2, 0, MAX_PWM + c);
  }
  
}

/**
 * @brief Reset motors and servo to idle state
 * 
 */
void resetMotors(){
  for(int i = 0; i < 4; i++)
    setMotor(i, 0);
  for(int i = 2; i <= 7; i++)
    setServo(i, 0);
}

/*void setPWMMotors(int c1, int c2, int c3, int c4)
{
  // setPWM(channel, on_duty_cycle, off_duty_cycle)
  if(c1 != 0 && c1 != 0 && c1 != 0 && c1 != 0){
    Serial.print(c1);
    Serial.print("\t");
    Serial.print(c2);
    Serial.print("\t");
    Serial.print(c3);
    Serial.print("\t");
    Serial.print(c4);
    Serial.println();
  }
  pwm.setPWM(PWM_CHANNEL11, c1, MAX_PWM - c1);
  pwm.setPWM(PWM_CHANNEL12, c2, MAX_PWM - c2);
  pwm.setPWM(PWM_CHANNEL21, c3, MAX_PWM - c3);
  pwm.setPWM(PWM_CHANNEL22, c4, MAX_PWM - c4);
}*/
/**
 * @brief Initialize the PCA9685 chip
 * 
 */
void initMotors()
{
  Wire.begin(); //SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(FREQUENCY);
  Wire.setClock(400000);

  //setPWMMotors(0, 0, 0, 0);
}

// /**
//  * Set speed and direction for 2 motors
//  *
//  * @param left_motor_speed: speed with direction for left motor. Range from -1 to 1. 1: max speed forward, -1: max speed reverse
//  * @param right_motor_speed: speed with direction for right motor. Range from -1 to 1. 1: max speed forward, -1: max speed reverse
//  */
// void setSpeed(float left_motor_speed, float right_motor_speed) {

//   int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

//   if (left_motor_speed > 0) {
//     c1 = max(MIN_PWM, min(int(abs(left_motor_speed) * MAX_PWM), MAX_PWM));
//   } else {
//     c2 = max(MIN_PWM, min(int(abs(left_motor_speed) * MAX_PWM), MAX_PWM));
//   }

//   if (right_motor_speed > 0) {
//     c3 = max(MIN_PWM, min(int(abs(right_motor_speed) * MAX_PWM), MAX_PWM));
//   } else {
//     c4 = max(MIN_PWM, min(int(abs(right_motor_speed) * MAX_PWM), MAX_PWM));
//   }

//   setPWMMotors(c1, c2, c3, c4);
// }
