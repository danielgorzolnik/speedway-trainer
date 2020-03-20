#include <LiquidCrystal.h>
#include <TimerOne.h>
#include "pins.h"
#include "software.h"
#include "hardware.h"
#include "lcd_characters.h"

//variables
uint8_t encoder = 0, encoder_t = 0;
boolean encoderBtnState = digitalRead(encoder_btn);
byte randomHandChoose = 0;
byte timerDivider = 0;
byte selectedHand = 0; //1-right, 2-left, 3-both, 4-random
byte selectedNumberOfStarts = 0;
byte currentNumberOfStarts = 0;
byte menu = main_menu;
byte menuSelectorPos = 1;
byte menuSelectorPage = 1;
byte displayBacklight = 100;
int encoderNumber = 0;
int encoderNumber_t = 0;
int mainTimer = 0;
int userTimer=0;
int showSummaryTimer = 0;
int waitTime=0;


//objects
LiquidCrystal lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

void setup(){
  configPins();
  lcdInit();
  showMenu();
  setBacklight(displayBacklight);

  Timer1.initialize(5000); // divide 1000 = 1 ms
  Timer1.attachInterrupt(timerVoid);
  randomSeed(analogRead(A0));
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
    delay(200);
  }
  else if (digitalRead(encoder_btn) && (encoderBtnState != digitalRead(encoder_btn))){
    encoderBtnState = digitalRead(encoder_btn);
    delay(200);
  }
  //end of encoder section 
  
  if (encoderNumber != encoderNumber_t){
    encoderNumber_t = encoderNumber;
    bigDigits(1,1,encoderNumber);
  }
}

void showMenu(){
  lcd.clear();
  if (menu == main_menu){ //MAIN_MENU
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
  else if (menu == program_menu){ //PROGRAM_MENU
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
  else if (menu == backlight_menu){ //BACKLIGHT_MENU
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

  else if (menu == choose_number_of_starts_menu) { //CHOOSE NUMBER OF STARTS MENU
    showSelector(menuSelectorPos);
    lcd.setCursor(3, 0);
    if (selectedHand == 1) lcd.print("PRAWA - STARTY");
    else if (selectedHand == 2) lcd.print("LEWA - STARTY");
    else if (selectedHand == 3) lcd.print("OBIE - STARTY");
    else if (selectedHand == 4) {
      lcd.setCursor(2, 0);
      lcd.print("LOSOWE - STARTY");
    }
    lcd.setCursor(1, 1);
    if (menuSelectorPage == 1) lcd.print("1.10 Startow");
    else if (menuSelectorPage == 2) lcd.print("4.Wroc");
    lcd.setCursor(1, 2);
    if (menuSelectorPage == 1) lcd.print("2.20 Startow");
    lcd.setCursor(1, 3);
    if (menuSelectorPage == 1) lcd.print("3.30 Startow");
  }

  else if (menu == wait_for_handle_menu){ //WAITING FOR HANDLE MENU
    lcd.setCursor(3, 0);
    lcd.print("PRZYGOTUJ SIE!");
    lcd.setCursor(4, 1);
    String selectedHandString = "START: ";
    selectedHandString = selectedHandString + String(currentNumberOfStarts) + "/" + String(selectedNumberOfStarts);
    lcd.print(selectedHandString);
    lcd.setCursor(3, 2);
    selectedHandString = "";
    if (selectedHand == 1) selectedHandString = "prawa";
    else if (selectedHand == 2) selectedHandString = "lewa";
    else if (selectedHand == 3 || selectedHand == 4) selectedHandString = "obie";
    selectedHandString = "wcisnij " + selectedHandString;
    lcd.print(selectedHandString);
    lcd.setCursor(7, 3);
    if (selectedHand == 1 || selectedHand == 2) lcd.print("klamke");
    else if (selectedHand == 3 || selectedHand == 4) lcd.print("klamki");
  }
  
  else if(menu == training_wait_menu){ // TRAINING WAIT MENU
    lcd.setCursor(3, 0);
    lcd.print("PRZYGOTUJ SIE!");
    lcd.setCursor(4, 1);
    String selectedHandString = "START: ";
    selectedHandString = selectedHandString + String(currentNumberOfStarts) + "/" + String(selectedNumberOfStarts);
    lcd.print(selectedHandString);
  }

   else if(menu == training_release_menu){ // TRAINING RELEASE MENU
    lcd.setCursor(4, 0);
    String selectedHandString = "START: ";
    selectedHandString = selectedHandString + String(currentNumberOfStarts) + "/" + String(selectedNumberOfStarts);
    lcd.print(selectedHandString);
    if (selectedHand == 1) selectedHandString = "PRAWA";
    else if (selectedHand == 2) selectedHandString = "LEWA";
    else if (selectedHand == 3) selectedHandString = "OBIE";
    else if (selectedHand == 4){
      if (randomHandChoose == 1) selectedHandString = "PRAWA";
      else if (randomHandChoose == 2) selectedHandString = "LEWA";
      else if (randomHandChoose == 3) selectedHandString = "OBIE";
    }
    lcd.setCursor(5,2);
    lcd.print("PUSC " + selectedHandString);
    lcd.setCursor(6,3);
    if (selectedHand == 3 || (selectedHand == 4 && randomHandChoose == 3)) lcd.print("MANETKI");
    else lcd.print("MANETKE");
  }

  else if (training_summary_single_menu){ // TRAINING SUMMARY SINGLE MENU
    int userResult = userTimer * 5;
    lcd.setCursor(5,0);
    lcd.print("Twoj wynik");
    if (userResult > 999){
      bigDigits(1, 2, userResult);
      lcd.setCursor(17, 3);
    }
    else {
      bigDigits(4, 2, userResult);
      lcd.setCursor(16, 3);
    }
    lcd.print("ms");
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
  else if (menu == choose_number_of_starts_menu){
    menuSelectorPos--;
    if (menuSelectorPos < 1) {
      if (menuSelectorPage == 2) menuSelectorPos = 3;
      else if (menuSelectorPage == 1) menuSelectorPos = 1;
      if (menuSelectorPage == 1) menuSelectorPage = 2;
      else if (menuSelectorPage == 2) menuSelectorPage = 1;
      showMenu();
    }
    showSelector(menuSelectorPos);
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
  else if (menu == choose_number_of_starts_menu){
    menuSelectorPos++;
    if (menuSelectorPos > 3 || (menuSelectorPos == 2 && menuSelectorPage == 2)) {
      menuSelectorPos = 1;
      if (menuSelectorPage == 1) menuSelectorPage = 2;
      else if (menuSelectorPage == 2) menuSelectorPage = 1;
      showMenu();
    }
    showSelector(menuSelectorPos);
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
      if (menuSelectorPage == 1){
         selectedHand = 1;
      }
      else {
        selectedHand = 4;
      }
      menu = choose_number_of_starts_menu;
    }
    else if (menuSelectorPos == 2){
      if (menuSelectorPage == 1){
        selectedHand = 2;
        menu = choose_number_of_starts_menu;
      }
      else menu = main_menu;
    }
    else if (menuSelectorPos == 3){
      if (menuSelectorPage == 1){
         selectedHand = 3;
          menu = choose_number_of_starts_menu;
      }
    } 
    menuSelectorPos = 1;
    menuSelectorPage = 1;
    showMenu();
  }
  else if (menu == backlight_menu) { //BACKLIGHT_MENU
    menuSelectorPos = 1;
    menuSelectorPage = 1;
    menu = main_menu;
    showMenu();
  }
  else if (menu == choose_number_of_starts_menu) { //CHOOSE NUMBER OF STARTS MENU
    if (menuSelectorPos == 1){
      if (menuSelectorPage == 1){
         selectedNumberOfStarts = 10;
         menu = wait_for_handle_menu;
      }
      else {
        menu = program_menu;
      }
    }
    else if (menuSelectorPos == 2){
      selectedNumberOfStarts = 20;
      menu = wait_for_handle_menu;
    }
    else if (menuSelectorPos == 3){
      selectedNumberOfStarts = 30;
      menu = wait_for_handle_menu;
    }
    currentNumberOfStarts = 1;
    menuSelectorPos = 1;
    menuSelectorPage = 1;
    showMenu();
  }
  else if (menu == wait_for_handle_menu) { // WAIT FOR HANDLE PUSH
    clearPixels();
    menu = choose_number_of_starts_menu;
    menuSelectorPos = 1;
    menuSelectorPage = 1;
    showMenu();
  }
}

void timerVoid(void){
  //do in every 5ms
  if (menu == training_wait_menu){
    mainTimer++;
    if (mainTimer >= waitTime){
      menu = training_release_menu;
      showMenu();
      if (selectedHand == 1) rightHandlePixels();
      else if (selectedHand == 2) leftHandlePixels();
      else if (selectedHand == 3) greenPixels();
      else if (selectedHand == 4){
        if (randomHandChoose == 1) rightHandlePixels();
        else if (randomHandChoose == 2) leftHandlePixels();
        else if (randomHandChoose == 3) greenPixels();
      }
    }
  }

  else if (menu == training_release_menu){
    userTimer++;
    boolean released = false;
    if (selectedHand == 1) released = checkHandleReleased(1);
    else if (selectedHand == 2) released = checkHandleReleased(2);
    else if (selectedHand == 3) released = checkHandleReleased(3);
    else if (selectedHand == 4){
      if (randomHandChoose == 1) released = checkHandleReleased(1);
      else if (randomHandChoose == 2) released = checkHandleReleased(2);
      else if (randomHandChoose == 3) released = checkHandleReleased(3);
    }
    if (released) {
      menu = training_summary_single_menu;
      clearPixels();
      showMenu();
    }
  }

  else if (menu == training_summary_single_menu) {
    showSummaryTimer++;
    if (showSummaryTimer > (single_summary_show_time /5)) {
      currentNumberOfStarts++;
      showSummaryTimer = 0;
      if (currentNumberOfStarts > selectedNumberOfStarts) {
        menu = training_summary_all_menu;
        showMenu();
      }
      else {
        menu = wait_for_handle_menu;
        showMenu();
      }
    }
    
  }
  
  //end
  timerDivider++;
  if (timerDivider > 20){
    //do in every 100ms
    if (menu == wait_for_handle_menu){
        if (checkHandlePushed(selectedHand)){
          //redPixels();
          waitTime=int(random(min_timer_wait/5, max_timer_wait/5));
          if (selectedHand == 4) randomHandChoose = byte(random(1, 4));
          menu = training_wait_menu;
          showMenu();
          mainTimer=0;
          userTimer=0;
        }
        else redPixels();
    }
    
    //end
    timerDivider = 0;
  }
}
