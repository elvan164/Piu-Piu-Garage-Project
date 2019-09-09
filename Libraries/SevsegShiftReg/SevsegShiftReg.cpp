#include "Arduino.h"
#include "SevsegShiftReg.h"

SevsegShiftReg::SevsegShiftReg(){}

SevsegShiftReg::SevsegShiftReg(int latchPin, int clockPin, int dataPin, int tensDigitPin, int onesDigitPin){
    this->latchPin = latchPin;
    this->clockPin = clockPin;
    this->dataPin = dataPin;
    this->tensDigitPin = tensDigitPin;
    this->onesDigitPin = onesDigitPin;
    doubleDigit = true;
}

SevsegShiftReg::SevsegShiftReg(int latchPin, int clockPin, int dataPin, int numDigits){
    this->latchPin = latchPin;
    this->clockPin = clockPin;
    this->dataPin = dataPin;
    if(numDigits == 2){
        useNotGate = true;
    }
}

void SevsegShiftReg::setupPins(){
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    if(doubleDigit && !useNotGate){
        pinMode(onesDigitPin, OUTPUT);
        pinMode(tensDigitPin, OUTPUT);
    }
}

void SevsegShiftReg::display2Digits(int num){
    if(useNotGate){
        digitalWrite(latchPin, LOW);
        // shift out the bits:
        shiftOut(dataPin, clockPin, MSBFIRST, numList_L[num/10]);
        //take the latch pin high so the LEDs will light up:
        digitalWrite(latchPin, HIGH);
        delay(5);

        digitalWrite(latchPin, LOW);
        // shift out the bits:
        shiftOut(dataPin, clockPin, MSBFIRST, numList_R[num%10]);
        //take the latch pin high so the LEDs will light up:
        digitalWrite(latchPin, HIGH);
        delay(5);
    }else{
        digitalWrite(latchPin, LOW);
        // shift out the bits:
        shiftOut(dataPin, clockPin, MSBFIRST, numList_L[num/10]);
        digitalWrite(tensDigitPin, LOW);
        digitalWrite(onesDigitPin, HIGH);
        //take the latch pin high so the LEDs will light up:
        digitalWrite(latchPin, HIGH);
        delay(5);

        digitalWrite(latchPin, LOW);
        // shift out the bits:
        shiftOut(dataPin, clockPin, MSBFIRST, numList_R[num%10]);
        digitalWrite(tensDigitPin, HIGH);
        digitalWrite(onesDigitPin, LOW);
        //take the latch pin high so the LEDs will light up:
        digitalWrite(latchPin, HIGH);
        delay(5);
    }
}

void SevsegShiftReg::displayLeftDigit(int num){
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numList_L[num]);
    digitalWrite(tensDigitPin, LOW);
    digitalWrite(onesDigitPin, HIGH);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(5);
}

void SevsegShiftReg::displayRightDigit(int num){
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numList_L[num]);
    digitalWrite(tensDigitPin, HIGH);
    digitalWrite(onesDigitPin, LOW);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(5);
}

void SevsegShiftReg::display2DigitsDetail(int hexNum){
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, hexNum);
    digitalWrite(tensDigitPin, LOW);
    digitalWrite(onesDigitPin, LOW);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(5);
}

void SevsegShiftReg::displayLeftDigitDetail(int hexNum){
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, hexNum);
    digitalWrite(tensDigitPin, LOW);
    digitalWrite(onesDigitPin, HIGH);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(5);
}

void SevsegShiftReg::displayRightDigitDetail(int hexNum){
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, hexNum);
    digitalWrite(tensDigitPin, HIGH);
    digitalWrite(onesDigitPin, LOW);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(5);
}

void SevsegShiftReg::displaySingleDigit(int num){
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numList_L[num]);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(5);
}

void SevsegShiftReg::displaySingleDigitDetail(int hexNum){
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, hexNum);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    delay(5);
}
