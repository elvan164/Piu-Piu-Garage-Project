#ifndef Gun_h
#define Gun_h

#include "Arduino.h"
#include "NewTone.h"
#include "Adafruit_NeoPixel.h"
#include "IRremote.h"
#include "SevsegShiftReg.h"

class Gun

{
	public:
    Gun(int minBullet, int maxBullet, int numPixels, int neopixelPin, int buzzerPin, int vibrationPin);
    void attachSevseg(SevsegShiftReg disp);
    void bootupSequence();
    void shoot();
    void updateAmmoBar();
    void setSendCode(int sendCode);
    int getSendCode();
    int getMaxBullet();
    void setMaxBullet(int maxBullet);
    int getCurrentBullet();
    void setCurrentBullet(int numBullets);


	private:
    Adafruit_NeoPixel strip;
    IRsend irsend;
    SevsegShiftReg disp;
    int numPixels;
    int sendCode = 0xa90;
    int minBullet, maxBullet, currentBullet, buzzerPin, vibrationPin;
    unsigned long previousMillisforbootupSound = 0;        // will store last time LED was updated
    const long bootupSoundInterval = 10;           // interval for bootupSound to change tone (milliseconds)
    int bootupCount=0;
    int bootupSoundDuration = 2000;
    int bootupFreq=500;
};

#endif
