#include <LiquidCrystal.h>
#include "pins.h"
#include "software.h"
#include "hardware.h"
#include "lcd_characters.h"

//variables
uint8_t encoder = 0, encoder_t = 0;
boolean encoderBtnState = digitalRead(encoder_btn);
byte menu = main_menu;
byte menuSelectorPos = 1;
byte menuSelectorPage = 1;
byte displayBacklight = 100;
int encoderNumber = 0;
int encoderNumber_t = 0;

//objects
LiquidCrystal lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

void setup(){
  configPins();
  lcdInit();
  showMenu();
  setBacklight(displayBacklight);
  
  Serial.begin(9600);
  encoder = encoderRead();
}

void loop() {
  //encoder section
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
  //end of encoder section 
  
  if (encoderNumber != encoderNumber_t){
    encoderNumber_t = encoderNumber;
    bigDigits(1,1,encoderNumber);
  }
}

void showMenu(){
  lcd.clear();
  if (menu == main_menu){
    showSelector(menuSelectorPos);
    lcd.setCursor(8, 0);
    lcd.print("MENU");
    lcd.setCursor(1, 1);
    lcd.print("1.Program");
    lcd.setCursor(1, 2);
    lcd.print("2.Podswietlenie");
    lcd.setCursor(1, 3);
    lcd.print("3.Autor");
  }
  else if (menu == program_menu){
    showSelector(menuSelectorPos);
    lcd.setCursor(6, 0);
    lcd.print("PROGRAM");
    lcd.setCursor(1, 1);
    if (menuSelectorPage == 1) lcd.print("1.Reka prawa");
    else if (menuSelectorPage == 2) lcd.print("4.Losowe rece");
    lcd.setCursor(1, 2);
    if (menuSelectorPage == 1) lcd.print("2.Reka lewa");
    else if (menuSelectorPage == 2) lcd.print("5.Wroc");
    lcd.setCursor(1, 3);
    if (menuSelectorPage == 1) lcd.print("3.Obie rece");
  }
  else if (menu == backlight_menu){
    lcd.setCursor(1, 0);
    lcd.print("PODSWIETLENIE LCD");
    if (displayBacklight == 100) {
      bigDigits(4, 2, displayBacklight);
      lcd.setCursor(16, 3);
    }
    else if (displayBacklight > 9) {
      bigDigits(6, 2, displayBacklight);
      lcd.setCursor(14, 3);
    }
    else if (displayBacklight < 10) {
      bigDigits(8, 2, displayBacklight);
      lcd.setCursor(12, 3);
    }
    lcd.print("%");
    setBacklight(displayBacklight);
  }
}

void encoderLeft(){ //encoder move - left
  if (menu == main_menu){
    menuSelectorPos--;
    if (menuSelectorPos > 3) menuSelectorPos = 1;
    else if (menuSelectorPos < 1) menuSelectorPos = 3;
    showSelector(menuSelectorPos);
  }
  else if (menu == program_menu){
    menuSelectorPos--;
    if (menuSelectorPos < 1) {
      if (menuSelectorPage == 2) menuSelectorPos = 3;
      else if (menuSelectorPage == 1) menuSelectorPos = 2;
      if (menuSelectorPage == 1) menuSelectorPage = 2;
      else if (menuSelectorPage == 2) menuSelectorPage = 1;
      showMenu();
    }
    showSelector(menuSelectorPos);
  }
  else if (menu == backlight_menu){
    displayBacklight--;
    if (displayBacklight < 1) {
      displayBacklight = 1;
    }
    showMenu();
  }
}

void encoderRight(){ //encoder move - right
  if  (menu == main_menu){
    menuSelectorPos++;
    if (menuSelectorPos > 3) menuSelectorPos = 1;
    else if (menuSelectorPos < 1) menuSelectorPos = 3;
    showSelector(menuSelectorPos);
  }
  else if (menu == program_menu){
    menuSelectorPos++;
    if (menuSelectorPos > 3 || (menuSelectorPos == 3 && menuSelectorPage == 2)) {
      menuSelectorPos = 1;
      if (menuSelectorPage == 1) menuSelectorPage = 2;
      else if (menuSelectorPage == 2) menuSelectorPage = 1;
      showMenu();
    }
    showSelector(menuSelectorPos);
  }
  else if (menu == backlight_menu){
    displayBacklight++;
    if (displayBacklight > 100) {
      displayBacklight = 100;
    }
    showMenu();
  }
}

void encoderButton(){
  if (menu == main_menu) {
    if (menuSelectorPos == 1){
      menu = program_menu;
    }
    else if (menuSelectorPos == 2){
      menu = backlight_menu;
    }
    else if (menuSelectorPos == 3){
      
    }
    menuSelectorPos = 1;
    menuSelectorPage = 1;
    showMenu();
  }
  else if (menu == program_menu) {
    if (menuSelectorPos == 1){
      
    }
    else if (menuSelectorPos == 2){
      if (menuSelectorPage == 2) menu = main_menu;
    }
    else if (menuSelectorPos == 3){
      
    } 
    menuSelectorPos = 1;
    menuSelectorPage = 1;
    showMenu();
  }
  else if (menu == backlight_menu) {
    menuSelectorPos = 1;
    menuSelectorPage = 1;
    menu = main_menu;
    showMenu();
  }
}
