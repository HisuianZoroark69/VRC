#define DEBUG

#include "motors.h"
#include "PS2_controller.h"
#include "Controls.h"

void setup()
{
  #ifdef DEBUG
  Serial.begin(115200);
  #endif
  initMotors();
  setupPS2controller();
  //Serial.println("Done setup!");
}
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
