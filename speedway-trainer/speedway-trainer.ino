#include <LiquidCrystal.h>
#include "pins.h"
#include "software.h"
#include "hardware.h"
#include "lcd_characters.h"

//variables
uint8_t encoder = 0, encoder_t = 0;
boolean encoderBtnState = digitalRead(encoder_btn);
int encoderNumber = 0;
int encoderNumber_t = 0;

//objects
LiquidCrystal lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

void setup(){
  configPins();
  lcdInit();
  lcd.setCursor(0,0);
  //lcd.print("speedwaytrainspeedwa");
  bigDigits(1,1,encoderNumber);

  Serial.begin(9600);
  encoder = encoderRead();
}

void loop() {
  //encoder
  encoder_t = encoderRead();
  if (encoder != encoder_t) {
    if ((encoder==3 && encoder_t==1)) encoderLeft();
    else if ((encoder==2 && encoder_t==0)) encoderRight();
    encoder = encoder_t;
  }
  if (!digitalRead(encoder_btn) && (encoderBtnState != digitalRead(encoder_btn))){
    encoderButton();
    encoderBtnState = digitalRead(encoder_btn);
    delay(100);
  }
  else if (digitalRead(encoder_btn) && (encoderBtnState != digitalRead(encoder_btn))){
    encoderBtnState = digitalRead(encoder_btn);
    delay(100);
  }




  
  if (encoderNumber != encoderNumber_t){
    encoderNumber_t = encoderNumber;
    bigDigits(1,1,encoderNumber);
    Serial.println(encoderNumber);
  }
  
  
}

void encoderLeft(){ //encoder move - left
  Serial.println("left");
  encoderNumber--;
}

void encoderRight(){ //encoder move - right
  Serial.println("right");
  encoderNumber++;
}

void encoderButton(){
  Serial.println("button");
}
