#include <LiquidCrystal.h>
#include "pins.h"
#include "software.h"
#include "pinconfig.h"

LiquidCrystal lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

//variables
uint8_t encoder = 0, encoder_t = 0;

void setup(){
  configPins();
  lcd.begin(lcd_columns, lcd_rows); //init lcd display
  lcd.print("speedway trainer");
  encoder = encoder_read();

  Serial.begin(9600);
}

void loop() {
  //encoder
  encoder_t = encoder_read();
  if (encoder != encoder_t) {
    if ((encoder==3 && encoder_t==1)) encoder_left();
    else if ((encoder==2 && encoder_t==0)) encoder_right();
    encoder = encoder_t;
  }
}

void encoder_left(){ //encoder move - left
  Serial.println("left");
}

void encoder_right(){ //encoder move - right
  Serial.println("right");
}

uint8_t encoder_read() { //read encoder state
  uint8_t val = 0;
  if(!digitalRead(encoder_in1)) val |= (1 << 1);
  if(!digitalRead(encoder_in2)) val |= (1 << 0);
  return val;
}
