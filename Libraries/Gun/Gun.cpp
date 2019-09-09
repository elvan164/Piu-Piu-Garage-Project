#include "Arduino.h"
#include "Gun.h"
#include "NewTone.h"
#include "Adafruit_NeoPixel.h"
#include "IRremote.h"
#include "SevsegShiftReg.h"

    Gun::Gun(int minBullet, int maxBullet, int numPixels, int neopixelPin, int buzzerPin, int vibrationPin){
        this->minBullet = minBullet;
        this->maxBullet = maxBullet;
        currentBullet = 0;
        this->buzzerPin = buzzerPin;
        this->numPixels = numPixels;
        this->strip = Adafruit_NeoPixel(this->numPixels, neopixelPin, NEO_GRB + NEO_KHZ800);
        this->vibrationPin = vibrationPin;
        strip.begin();
    }

    void Gun::attachSevseg(SevsegShiftReg disp){
        this->disp = disp;
    }

    void Gun::bootupSequence(){
        while (bootupCount<=(bootupSoundDuration/10))
        {
            digitalWrite(vibrationPin, HIGH);

            unsigned long currentMillisforbootupSound = millis();
            NewTone(buzzerPin, bootupFreq, bootupSoundInterval);
            if (currentMillisforbootupSound - previousMillisforbootupSound >= bootupSoundInterval) {
                // save the last time you blinked the LED
                previousMillisforbootupSound = currentMillisforbootupSound;
                bootupFreq+=15;
                bootupCount++;
                int num = (bootupSoundDuration/10) / maxBullet;
                if ((currentBullet < maxBullet) && (bootupCount%num == 0))
                {
                    currentBullet++;
                    strip.show();
                }
            }
            disp.display2Digits(currentBullet);

        }

                digitalWrite(vibrationPin, LOW);
    }

    void Gun::shoot(){
        if(currentBullet > 0){
            NewTone(buzzerPin, 1000, 100);
            currentBullet--;
            irsend.sendSony(sendCode, 16);

            digitalWrite(vibrationPin, HIGH);
            delay(200);
            digitalWrite(vibrationPin, LOW);

        }
    }

    void Gun::setSendCode(int sendCode){
        this->sendCode = sendCode;
    }

    int Gun::getMaxBullet(){
        return maxBullet;
    }
    void Gun::setMaxBullet(int maxBullet){
        this->maxBullet = maxBullet;
    }
    int Gun::getCurrentBullet(){
        return currentBullet;
    }
    void Gun::setCurrentBullet(int numBullets){
        this->currentBullet = numBullets;
    }

    void Gun::updateAmmoBar(){
        disp.display2Digits(currentBullet);
}
