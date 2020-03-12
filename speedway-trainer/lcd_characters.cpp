#include <LiquidCrystal.h>
#include <Arduino.h>
#include "software.h"
#include "lcd_characters.h"

int prevBigDigits = 0;
extern LiquidCrystal lcd;
byte LT[8] =
{
 B00111,
 B01111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111
};
byte UB[8] =
{
 B11111,
 B11111,
 B11111,
 B00000,
 B00000,
 B00000,
 B00000,
 B00000
};
byte RT[8] =
{
 B11100,
 B11110,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111
};
byte LL[8] =
{
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B01111,
 B00111
};
byte LB[8] =
{
 B00000,
 B00000,
 B00000,
 B00000,
 B00000,
 B11111,
 B11111,
 B11111
};
byte LR[8] =
{
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11110,
 B11100
};
byte MB[8] =
{
 B11111,
 B11111,
 B11111,
 B00000,
 B00000,
 B00000,
 B11111,
 B11111
};
byte block[8] =
{
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111
};

void lcdInit(){
  lcd.begin(lcd_columns, lcd_rows); //init lcd display
  lcd.createChar(0,LT);
  lcd.createChar(1,UB);
  lcd.createChar(2,RT);
  lcd.createChar(3,LL);
  lcd.createChar(4,LB);
  lcd.createChar(5,LR);
  lcd.createChar(6,MB);
  lcd.createChar(7,block);
}

void bigDigits(byte x, byte y, int value){
  //values from 0 to 9999
  if (value > 9999) value = 9999;
  else if (value < 0) value = 0;
  byte num4 = value % 10;
  byte num3 = (value / 10) % 10;
  byte num2 = (value / 100) % 10;
  byte num1 = (value / 1000) % 10;

  if (prevBigDigits > 999 && value < 1000) clearnumber(x+12, y);
  else if (prevBigDigits > 99 && value < 100) clearnumber(x+8, y);
  else if (prevBigDigits > 9 && value < 10) clearnumber(x+4, y);
  prevBigDigits = value;

  if (value > 999){
    selectLcdNumber(x, y, num1);
    selectLcdNumber(x+4, y, num2);
    selectLcdNumber(x+8, y, num3);
    selectLcdNumber(x+12, y, num4);
  }
  else if (value > 99){
    selectLcdNumber(x, y, num2);
    selectLcdNumber(x+4, y, num3);
    selectLcdNumber(x+8, y, num4);
  }
  else if (value > 9){
    selectLcdNumber(x, y, num3);
    selectLcdNumber(x+4, y, num4);
  }
  else if (value < 10){
    selectLcdNumber(x, y, num4);
  }
  
}

void selectLcdNumber(byte x, byte y, byte number){
  clearnumber(x, y);
  switch(number) {
    case 0:
      custom0(x, y);
      break;
    case 1:
      custom1(x, y);
      break;
    case 2:
      custom2(x, y);
      break;
    case 3:
      custom3(x, y);
      break;
    case 4:
      custom4(x, y);
      break;
    case 5:
      custom5(x, y);
      break;
    case 6:
      custom6(x, y);
      break;
    case 7:
      custom7(x, y);
      break;
    case 8:
      custom8(x, y);
      break;
    case 9:
      custom9(x, y);
      break;
    
  }
}

void custom0(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)0);
 lcd.write((byte)1);
 lcd.write((byte)2);
 lcd.setCursor(x, y+1);
 lcd.write((byte)3);
 lcd.write((byte)4);
 lcd.write((byte)5);
}

void custom1(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)1);
 lcd.write((byte)2);
 lcd.setCursor(x, y+1);
 lcd.write((byte)4);
 lcd.write((byte)7);
 lcd.write((byte)4);
}

void custom2(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)6);
 lcd.write((byte)6);
 lcd.write((byte)2);
 lcd.setCursor(x, y+1);
 lcd.write((byte)3);
 lcd.write((byte)4);
 lcd.write((byte)4);
}

void custom3(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)6);
 lcd.write((byte)6);
 lcd.write((byte)2);
 lcd.setCursor(x, y+1);
 lcd.write((byte)4);
 lcd.write((byte)4);
 lcd.write((byte)5);
}

void custom4(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)3);
 lcd.write((byte)4);
 lcd.write((byte)7);
 lcd.setCursor(x+2, y+1);
 lcd.write((byte)7);
}

void custom5(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)3);
 lcd.write((byte)6);
 lcd.write((byte)6);
 lcd.setCursor(x, y+1);
 lcd.write((byte)4);
 lcd.write((byte)4);
 lcd.write((byte)5);
}

void custom6(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)0);
 lcd.write((byte)6);
 lcd.write((byte)6);
 lcd.setCursor(x, y+1);
 lcd.write((byte)3);
 lcd.write((byte)4);
 lcd.write((byte)5);
}

void custom7(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)1);
 lcd.write((byte)1);
 lcd.write((byte)2);
 lcd.setCursor(x+2, y+1);
 lcd.write((byte)7);
}

void custom8(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)0);
 lcd.write((byte)6);
 lcd.write((byte)2);
 lcd.setCursor(x, y+1);
 lcd.write((byte)3);
 lcd.write((byte)4);
 lcd.write((byte)5);
}

void custom9(byte x, byte y)
{
 lcd.setCursor(x, y);
 lcd.write((byte)0);
 lcd.write((byte)6);
 lcd.write((byte)2);
 lcd.setCursor(x, y+1);
 lcd.write((byte)4);
 lcd.write((byte)4);
 lcd.write((byte)7);
}

void clearnumber(byte x, byte y)
{ // clears the area the custom number is displayed in
lcd.setCursor(x,y);
lcd.print("   ");
lcd.setCursor(x,y+1);
lcd.print("   ");
}
