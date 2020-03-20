#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include "hardware.h"
#include "pins.h"
#include "software.h"

Adafruit_NeoPixel pixels(digital_led_count, digital_led, NEO_GRB + NEO_KHZ800);

void configPins(){
  pinMode(handle_r_up, INPUT_PULLUP);
  pinMode(handle_r_down, INPUT_PULLUP);
  pinMode(handle_l_up, INPUT_PULLUP);
  pinMode(handle_l_down, INPUT_PULLUP);
  pinMode(encoder_in1, INPUT_PULLUP);
  pinMode(encoder_in2, INPUT_PULLUP);
  pinMode(encoder_btn, INPUT_PULLUP);
  pinMode(lcd_pwm, OUTPUT);
  pixels.begin();
  clearPixels();
}

uint8_t encoderRead() { //read encoder state
  uint8_t val = 0;
  if(!digitalRead(encoder_in1)) val |= (1 << 1);
  if(!digitalRead(encoder_in2)) val |= (1 << 0);
  return val;
}

void setBacklight(byte value) {
  byte pwmValue = (float)value * 2.55;
  Serial.println(pwmValue);  
  analogWrite(lcd_pwm, pwmValue);
}

boolean checkHandlePushed(byte selectedHand){
  if (selectedHand == 1) { //right 
    if (digitalRead(handle_r_down) == 0 && digitalRead(handle_r_up) == 1) return true;
    else return false;
  }
  else if (selectedHand == 2) { //left 
    if (digitalRead(handle_l_down) == 0 && digitalRead(handle_l_up) == 1) return true;
    else return false;
  }

  else if (selectedHand == 3 || selectedHand == 4) { //both
    if ((digitalRead(handle_l_down) == 0 && digitalRead(handle_l_up) == 1) && (digitalRead(handle_r_down) == 0 && digitalRead(handle_r_up) == 1)) return true;
    else return false;
  }

  else if (selectedHand == 5) { //any
    if ((digitalRead(handle_l_down) == 0 && digitalRead(handle_l_up) == 1) || (digitalRead(handle_r_down) == 0 && digitalRead(handle_r_up) == 1)) return true;
    else return false;
  }
}

boolean checkHandleReleased(byte selectedHand){
  if (selectedHand == 1) { //right 
    if (digitalRead(handle_r_down) == 1 && digitalRead(handle_r_up) == 0) return true;
    else return false;
  }
  else if (selectedHand == 2) { //left 
    if (digitalRead(handle_l_down) == 1 && digitalRead(handle_l_up) == 0) return true;
    else return false;
  }

  else if (selectedHand == 3 || selectedHand == 4) { //both
    if ((digitalRead(handle_l_down) == 1 && digitalRead(handle_l_up) == 0) && (digitalRead(handle_r_down) == 1 && digitalRead(handle_r_up) == 0)) return true;
    else return false;
  }

  else if (selectedHand == 5) { //any
    if ((digitalRead(handle_l_down) == 1 && digitalRead(handle_l_up) == 0) || (digitalRead(handle_r_down) == 1 && digitalRead(handle_r_up) == 0)) return true;
    else return false;
  }
}

void clearPixels() {
  pixels.clear();
  pixels.show(); 
}

void redPixels(){
  clearPixels();
  for(int i=0; i<digital_led_count; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
  }
  pixels.show(); 
}

void greenPixels(){
  clearPixels();
  for(int i=0; i<digital_led_count; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
  }
  pixels.show(); 
}

void bluePixels(){
  clearPixels();
  for(int i=0; i<digital_led_count; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
  }
  pixels.show(); 
}

void whitePixels(){
  clearPixels();
  for(int i=0; i<digital_led_count; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
  }
  pixels.show(); 
}

void leftHandlePixels(){
  clearPixels();
  for(int i=0; i<digital_led_count; i++) {
    if (reverse_digital_led_strip == 0 && i < digital_led_count/2){
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
    else if (reverse_digital_led_strip == 0 && i >= digital_led_count/2){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
    else if (reverse_digital_led_strip == 1 && i >= digital_led_count/2){
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
    else if (reverse_digital_led_strip == 1 && i < digital_led_count/2){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
  }
  pixels.show();
}

void rightHandlePixels(){
  clearPixels();
  for(int i=0; i<digital_led_count; i++) {
    if (reverse_digital_led_strip == 0 && i >= digital_led_count/2){
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
    else if (reverse_digital_led_strip == 0 && i < digital_led_count/2){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
    else if (reverse_digital_led_strip == 1 && i < digital_led_count/2){
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
    else if (reverse_digital_led_strip == 1 && i >= digital_led_count/2){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
  }
  pixels.show();
}
