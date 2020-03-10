#include <Arduino.h>
#include "pinconfig.h"
#include "pins.h"

void configPins(){
  pinMode(handle_r_up, INPUT_PULLUP);
  pinMode(handle_r_down, INPUT_PULLUP);
  pinMode(handle_l_up, INPUT_PULLUP);
  pinMode(handle_l_down, INPUT_PULLUP);
  pinMode(encoder_in1, INPUT_PULLUP);
  pinMode(encoder_in2, INPUT_PULLUP);
  pinMode(encoder_btn, INPUT_PULLUP);
  pinMode(lcd_pwm, OUTPUT);
  analogWrite(lcd_pwm, 255);
}
