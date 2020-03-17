#include <Arduino.h>
#include "software.h"

unsigned int userTimes[30];

void cleanUserTimes(){
  for(byte i=0; i<30; i++){
    userTimes[i] = 0; 
  }
}
