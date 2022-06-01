#include "motors.h"
#include "PS2_controller.h"
#include "Controls.h"

#define DEBUG

void setup()
{
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  initMotors();
  setupPS2controller();
  //Serial.println("Done setup!");
}
float currentAngle = 0;
int adder = 20;
int pulse = SERVOMIN;
void loop()
{
  ps2x.read_gamepad();
  bool pressed = false;
  //PS2control();
  MovementControl(&pressed);
  ServoControl(&pressed);
  
  if(!pressed) resetMotors();

  //Bắt buộc phải delay, k thì lủng LMAO
  delay(25);
}
