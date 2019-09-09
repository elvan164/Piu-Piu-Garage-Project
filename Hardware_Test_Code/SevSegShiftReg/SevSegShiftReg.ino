/*
 * This is an example of using the SevsegShiftReg library, implementing a generic counter with millis().
 * millis() is used instead of delay as the sevseg flickers between the ones and tens digit to display the number
 * and delaying will affect the clarity of the numbers.
 */
#include <SevsegShiftReg.h>
unsigned long timer = millis();
unsigned long counter = millis();
//Pin connected to ST_CP of 74HC595
#define LATCHPIN 10
//Pin connected to SH_CP of 74HC595
#define CLOCKPIN 12
////Pin connected to DS of 74HC595
#define DATAPIN 11

SevsegShiftReg mySevseg(LATCHPIN, CLOCKPIN, DATAPIN);

void setup() {
  //set pins to output so you can control the shift register
  mySevseg.setupPins();
}

void loop() {
  static int i = 0;
  timer = millis();
  if(timer - counter >= 500){
    counter = timer;
    i++;
  }
  if(i>9){
    i = 0;
  }
  mySevseg.displaySingleDigit(i);

}



