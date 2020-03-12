#include <Arduino.h>
#include "hardware.h"
#include "pins.h"
#include "software.h"

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

uint8_t encoderRead() { //read encoder state
  uint8_t val = 0;
  if(!digitalRead(encoder_in1)) val |= (1 << 1);
  if(!digitalRead(encoder_in2)) val |= (1 << 0);
  return val;
}
