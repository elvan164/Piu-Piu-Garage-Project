/*
 * Pin 6 - Neopixel
 * Pin 2 - Trigger button
 * Pin 3 - IR
 * Pin 8 - Buzzer
 */
#include <NewTone.h>
#include <Adafruit_NeoPixel.h>
#include <IRremote.h>

/*defining pin numbers*/
#define PIN      6
#define NUMPIXELS 5
#define TRIGGERPIN 2
#define BUZZERPIN 8

// variables for pulling trigger of gun
int triggerState = 0;               // variable for reading the trigger status
int maxBullet = 30;                 // Max Ammo for the gun
int minBullet = 0;                  // Min. Ammo for the gun
int currentBullet = 0;              // Current Ammo for the gun
boolean triggerPressed = false;     //boolean to prevent spamming

// variables for booting up sequence
unsigned long previousMillisforbootupSound = 0;        // will store last time LED was updated
const long bootupSoundInterval = 10;           // interval for bootupSound to change tone (milliseconds)
int bootupCount=0;
int bootupSoundDuration = 2000;
int bootupFreq=500;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
IRsend irsend;

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(TRIGGERPIN, INPUT_PULLUP);
  Serial.begin(9600);
 
}

void loop() {
  bootupSequence();
  triggerState = digitalRead(TRIGGERPIN);
  if(triggerState == HIGH){
    // trigger not pressed
    triggerPressed = true;
  }else{
    if ((triggerPressed == true) && (currentBullet > 0)){
      shoot();
      triggerPressed = false;
    }
  }
  updateAmmoBar(0, NUMPIXELS, currentBullet, minBullet, maxBullet);
  strip.show();
}

void shoot() {
  NewTone(BUZZERPIN, 1000, 100);
  currentBullet--;
  irsend.sendSony(0xa90, 12);
  Serial.println(currentBullet);
}


void updateAmmoBar(int firstAmmoPixel, int lastAmmoPixel, int currentBullet, int minBullet, int maxBullet) {
  int numberOfPixels = lastAmmoPixel - firstAmmoPixel + 1;
  int numberOfStates = numberOfPixels * 3;
  currentBullet = constrain(currentBullet, minBullet, maxBullet);
  int currentState = map(currentBullet, minBullet, maxBullet, 0, numberOfStates);
  int numberOfBlue = map(currentBullet, minBullet, maxBullet, 0, numberOfPixels);
  int colorOfEdge = currentState % 3;

  for (int i = firstAmmoPixel; i <= lastAmmoPixel; i++) {
    //Serial.print("Ammo pixel number: ");
    //Serial.print(i);
    if (i < firstAmmoPixel + numberOfBlue) {
      strip.setPixelColor(i, strip.Color(0, 50, 50));
      //Serial.println("light blue");
    }
    else if (i == firstAmmoPixel + numberOfBlue) {
      switch (colorOfEdge) {
        case 2:
          //Serial.println("green");
          strip.setPixelColor(i, strip.Color(0, 50, 0));
          break;
        case 1:
          //Serial.println("red");
          strip.setPixelColor(i, strip.Color(50, 0, 0));
          break;
        case 0:
          //Serial.println("Black");
          strip.setPixelColor(i, strip.Color(0, 0, 0));
          break;
      }
    } else {
      //Serial.println("Black");
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  }
}


void bootupSequence() {
  while (bootupCount<=(bootupSoundDuration/10))
  {
    unsigned long currentMillisforbootupSound = millis();
    NewTone(BUZZERPIN, bootupFreq, bootupSoundInterval);
    if (currentMillisforbootupSound - previousMillisforbootupSound >= bootupSoundInterval) {
    // save the last time you blinked the LED
    previousMillisforbootupSound = currentMillisforbootupSound;
    bootupFreq+=15;
    bootupCount++;
    int num = (bootupSoundDuration/10) / maxBullet;
    if ((currentBullet < maxBullet) && (bootupCount%num == 0))
      {
        currentBullet++;
        updateAmmoBar(0, NUMPIXELS, currentBullet, minBullet, maxBullet);
        strip.show();
        Serial.println(currentBullet);
      }
    }
  }
}
