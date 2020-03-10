#include <LiquidCrystal.h>
#include "pins.h"
#include "software.h"
#include "pinconfig.h"

LiquidCrystal lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

void setup(){
  configPins();
  lcd.begin(lcd_columns, lcd_rows); //init lcd display
  lcd.print("speedway trainer");
}

void loop() {
}
