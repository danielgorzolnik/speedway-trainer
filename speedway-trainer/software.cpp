#include <Arduino.h>
#include "software.h"

unsigned int userTimes[30];

void cleanUserTimes(){
  for(byte i=0; i<30; i++){
    userTimes[i] = 0; 
  }
}

void addTimeToResult(byte numberOfTraining, int result){
  userTimes[numberOfTraining-1] = result; 
}

int calculateTimeAvg() {
  byte counter = 0;
  unsigned long sum = 0;
  for(byte i=0; i<30; i++){
    if (userTimes[i] > 0){
      counter++;
      sum = sum + userTimes[i];
    }
  }
  return sum / counter;
}

int calculateTimeMax(){
  int result = 0;
  for(byte i=0; i<30; i++){
    if (userTimes[i] > result){
      result = userTimes[i];
    }
  }
  return result;
}

int calculateTimeMin(){
  int result = 10000;
  for(byte i=0; i<30; i++){
    if (userTimes[i] < result && userTimes[i] != 0){
      result = userTimes[i];
    }
  }
  return result;
}
