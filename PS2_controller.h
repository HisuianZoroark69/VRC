#pragma once
//#include "motors.h"
#include <PS2X_lib.h>

PS2X ps2x; // create PS2 Controller Class

#define PS2_DAT 12 //MISO  19
#define PS2_CMD 13 //MOSI  23
#define PS2_SEL 15 //SS     51
#define PS2_CLK 14 //SLK   18

#define pressures false
#define rumble false

//#define MIN_PWM 0
//#define MAX_PWM 4095
//bool RUN = 0;

void setupPS2controller()
{
  //Serial.begin(115200);
  Serial.print("Ket noi voi tay cam PS2:");

  int error = -1;
  for (int i = 0; i < 10; i++) // thử kết nối với tay cầm ps2 trong 10 lần
  {
    delay(1000); // đợi 1 giây
    // cài đặt chân và các chế độ: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    Serial.print(".");
  }

  switch (error) // kiểm tra lỗi nếu sau 10 lần không kết nối được
  {
  case 0:
    Serial.println(" Ket noi tay cam PS2 thanh cong");
    break;
  case 1:
    Serial.println(" LOI: Khong tim thay tay cam, hay kiem tra day ket noi vơi tay cam ");
    break;
  case 2:
    Serial.println(" LOI: khong gui duoc lenh");
    break;
  case 3:
    Serial.println(" LOI: Khong vao duoc Pressures mode ");
    break;
  }
}
bool PS2control()
{
  /*// Based on IgorF2's Arduino Bot:https://www.instructables.com/Arduino-Robot-With-PS2-Controller-PlayStation-2-Jo/

  int nJoyX = ps2x.Analog(PSS_LX); // read x-joystick
  int nJoyY = ps2x.Analog(PSS_LY); // read y-joystick

  nJoyX = map(nJoyX, 0, 255, -1023, 1023);
  nJoyY = map(nJoyY, 0, 255, 1023, -1023);

  // OUTPUTS
  int nMotMixL; // Motor (left) mixed output
  int nMotMixR; // Motor (right) mixed output

  // CONFIG
  // - fPivYLimt  : The threshold at which the pivot action starts
  //                This threshold is measured in units on the Y-axis
  //                away from the X-axis (Y=0). A greater value will assign
  //                more of the joystick's range to pivot actions.
  //                Allowable range: (0..+127)
  float fPivYLimit = 1023.0;

  // TEMP VARIABLES
  float nMotPremixL; // Motor (left) premixed output
  float nMotPremixR; // Motor (right) premixed output
  int nPivSpeed;     // Pivot Speed
  float fPivScale;   // Balance scale between drive and pivot

  // Calculate Drive Turn output due to Joystick X input
  if (nJoyY >= 0)
  {
    // Forward
    nMotPremixL = (nJoyX >= 0) ? 1023.0 : (1023.0 + nJoyX);
    nMotPremixR = (nJoyX >= 0) ? (1023.0 - nJoyX) : 1023.0;
  }
  else
  {
    // Reverse
    nMotPremixL = (nJoyX >= 0) ? (1023.0 - nJoyX) : 1023.0;
    nMotPremixR = (nJoyX >= 0) ? 1023.0 : (1023.0 + nJoyX);
  }

  // Scale Drive output due to Joystick Y input (throttle)
  nMotPremixL = nMotPremixL * nJoyY / 1023.0;
  nMotPremixR = nMotPremixR * nJoyY / 1023.0;

  // Now calculate pivot amount
  // - Strength of pivot (nPivSpeed) based on Joystick X input
  // - Blending of pivot vs drive (fPivScale) based on Joystick Y input
  nPivSpeed = nJoyX;
  fPivScale = (abs(nJoyY) > fPivYLimit) ? 0.0 : (1.0 - abs(nJoyY) / fPivYLimit);

  // Calculate final mix of Drive and Pivot
  nMotMixL = (1.0 - fPivScale) * nMotPremixL + fPivScale * (nPivSpeed);
  nMotMixR = (1.0 - fPivScale) * nMotPremixR + fPivScale * (-nPivSpeed);

  Serial.print(nMotMixL);
  Serial.print("\t");
  Serial.println(nMotMixR);
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

  if (nMotMixR > 50)
  {
    c3 = nMotMixR;
    // pwm.setPWM(PWM_CHANNEL1, motor_right_speed, MAX_PWM - motor_right_speed );
    // pwm.setPWM(PWM_CHANNEL2, 0, MAX_PWM );
  }

  else if (nMotMixR < -50)
  {
    // pwm.setPWM(PWM_CHANNEL2, motor_right_speed, MAX_PWM - motor_right_speed );
    // pwm.setPWM(PWM_CHANNEL1, 0, MAX_PWM );
    c4 = abs(nMotMixR);
  }

  if (nMotMixL > 50)
  {
    // pwm.setPWM(PWM_CHANNEL3, motor_left_speed, MAX_PWM - motor_left_speed );
    // pwm.setPWM(PWM_CHANNEL4, 0, MAX_PWM );
    c1 = nMotMixL;
  }
  else if (nMotMixL < -50)
  {
    // pwm.setPWM(PWM_CHANNEL4, motor_left_speed, MAX_PWM - motor_left_speed );
    // pwm.setPWM(PWM_CHANNEL3, 0, MAX_PWM );
    c2 = abs(nMotMixL);
  }
  setPWMMotors(c1, c2, c3, c4);
  delay(50);
  return 1;*/
  ps2x.read_gamepad(false, false); // gọi hàm để đọc tay điều khiển

  // các trả về giá trị TRUE (1) khi nút được giữ
  if (ps2x.Button(PSB_START)) // nếu nút Start được giữ, in ra Serial monitor
    Serial.println("Start is being held");
  if (ps2x.Button(PSB_SELECT)) // nếu nút Select được giữ, in ra Serial monitor
    Serial.println("Select is being held");

  if (ps2x.Button(PSB_PAD_UP)) // tương tự như trên kiểm tra nút Lên (PAD UP)
  {
    Serial.print("Up held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC); // đọc giá trị analog ở nút này, xem nút này được bấm mạnh hay nhẹ
  }
  if (ps2x.Button(PSB_PAD_RIGHT))
  {
    Serial.print("Right held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  }
  if (ps2x.Button(PSB_PAD_LEFT))
  {
    Serial.print("LEFT held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
  }
  if (ps2x.Button(PSB_PAD_DOWN))
  {
    Serial.print("DOWN held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
  }

  if (ps2x.NewButtonState())
  { // Trả về giá trị TRUE khi nút được thay đổi trạng thái (bật sang tắt, or tắt sang bật)
    if (ps2x.Button(PSB_L3))
      Serial.println("L3 pressed");
    if (ps2x.Button(PSB_R3))
      Serial.println("R3 pressed");
    if (ps2x.Button(PSB_L2))
      Serial.println("L2 pressed");
    if (ps2x.Button(PSB_R2))
      Serial.println("R2 pressed");
    if (ps2x.Button(PSB_TRIANGLE))
      Serial.println("△ pressed");
  }
  //△□○×
  if (ps2x.ButtonPressed(PSB_CIRCLE)) // Trả về giá trị TRUE khi nút được ấn (từ tắt sang bật)
    Serial.println("○ just pressed");
  if (ps2x.NewButtonState(PSB_CROSS)) // Trả về giá trị TRUE khi nút được thay đổi trạng thái
    Serial.println("× just changed");
  if (ps2x.ButtonReleased(PSB_SQUARE)) //  Trả về giá trị TRUE khi nút được ấn (từ tắt sang bật)
    Serial.println("□ just released");

  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // các trả về giá trị TRUE khi nút được giữ
  {                                               // Đọc giá trị 2 joystick khi nút L1 hoặc R1 được giữ
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY)); // đọc trục Y của joystick bên trái. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC);
  }
  delay(50);
}
