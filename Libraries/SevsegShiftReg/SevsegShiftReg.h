/*
    4 digit 7 segment displays use 12 digital pins. You may need more pins if your display has colons or apostrophes.
    There are 4 digit pins and 8 segment pins. Digit pins are connected to the cathodes for common cathode displays, or
    anodes for common anode displays. 8 pins control the individual segments (seven segments plus the decimal point).
    Connect the four digit pins with four limiting resistors in series to any digital or analog pins. Connect the eight
    segment pins to any digital or analog pins (no limiting resistors needed).

    SN74HC595 Chip
                           __                  __
     Vcc     A     DS      OE   Latch   clk    MR     SerialOut
     _|______|______|______|______|______|______|______|_
    |                                                    |
    |)                                                   |
    |____________________________________________________|
      |      |      |      |      |      |      |      |
      B      C      D      E      F      G      H     GND
    2 digit sevseg:
      a  b  d1 d2 f
     _|__|__|__|__|_
    |               |        alternative wiring: d1 to H, invert H to d2
    |_______________|
      |  |  |  |  |
      c dot e  d  g
    1 digit sevseg:
      g  f gnd a  b
     _|__|__|__|__|_
    |               |
    |_______________|
      |  |  |  |  |
      e  d gnd c  dot
*/

#ifndef SevsegShiftReg_h
#define SevsegShiftReg_h
#include "Arduino.h"

class SevsegShiftReg
{
    public:
    SevsegShiftReg(int latchPin, int clockPin, int dataPin, int tensDigitPin, int onesDigitPin);
    SevsegShiftReg(int latchPin, int clockPin, int dataPin, int numDigits);
    SevsegShiftReg();
    void setupPins();
    // display2Digits is a function to output numbers into 2 digit 10 pins 7-segment display
    //this function requires rapid update between the 2 digits, thus delay cannot be used to update the number.
    void display2Digits(int num);
    void displayLeftDigit(int num);
    void displayRightDigit(int num);
    // displayDetail function takes input in terms of binary/hex numbers to light up desired led segments
    void display2DigitsDetail(int hexNum);
    void displayLeftDigitDetail(int hexNum);
    void displayRightDigitDetail(int hexNum);
    //function to display desired digit
    void displaySingleDigit(int num);
    void displaySingleDigitDetail(int hexNum);


    private:
    byte numList_L[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
    byte numList_R[10] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF};
    int latchPin, clockPin, dataPin, tensDigitPin, onesDigitPin;
    bool doubleDigit = false;
    bool useNotGate = false;
};
#endif
