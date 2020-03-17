//pinconfig header file

//functions
void configPins(); //config i/o pins
void setBacklight(byte value);
uint8_t encoderRead(); //read encoder direction and pulse
boolean checkHandlePushed(byte selectedHand);
boolean checkHandleReleased(byte selectedHand);
void clearPixels();
void redPixels();
void greenPixels();
void bluePixels();
void whitePixels();
void rightHandlePixels();
void leftHandlePixels();
