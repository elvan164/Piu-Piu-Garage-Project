   /*
 * Pin 2 - Trigger button
 * Pin 3 - IR
 * Pin 4 - Vibration Module
 * Pin 6 - Neopixel
 * Pin 8 - Buzzer
 * Pin 10 - LatchPin
 * Pin 11 - DataPin
 * Pin 12 - ClockPin
 * 
 */
#include <Gun.h>
#include <IR_Comms.h>
#include <SevsegShiftReg.h>
/*defining pin numbers*/

#define BUZZERPIN A0
#define VIBRATIONPIN A1
#define TRIGGERPIN A2  // normally open to trigger pin and com to gnd

#define NUMPIXELS 5
#define NEOPIXELSPIN 6
//Pin connected to ST_CP of 74HC595
#define LATCHPIN 10
////Pin connected to DS of 74HC595
#define DATAPIN 11
//Pin connected to SH_CP of 74HC595
#define CLOCKPIN 12

// variables for pulling trigger of gun
int triggerState = 0;               // variable for reading the trigger status
int maxBullet = 30;                 // Max Ammo for the gun
int minBullet = 0;                  // Min. Ammo for the gun
int currentBullet = 0;              // Current Ammo for the gun
boolean triggerPressed = false;     //boolean to prevent spamming


Gun standardGun = Gun(minBullet, maxBullet, NUMPIXELS, NEOPIXELSPIN, BUZZERPIN, VIBRATIONPIN);
IR_Comms irComms(0x1, 0x1);
SevsegShiftReg disp(LATCHPIN, CLOCKPIN, DATAPIN, 2);

void setup() {
  Serial.begin(9600);
  standardGun.setSendCode(irComms.encrypt());
  disp.setupPins();
  standardGun.attachSevseg(disp);
  pinMode(TRIGGERPIN, INPUT_PULLUP);
  
  pinMode(VIBRATIONPIN, OUTPUT);
}

void loop() {
  //fancy bootup sequence
  standardGun.bootupSequence();
  
  //check if trigger is pressed, and shoot if it is
  triggerState = digitalRead(TRIGGERPIN);
  if(triggerState == HIGH){
    // trigger not pressed
    triggerPressed = false;
    // digital write vibrator low
    digitalWrite(VIBRATIONPIN, LOW);

  }else{
    if(triggerPressed == false){
      standardGun.shoot();
      // digital write vibrator high
      digitalWrite(VIBRATIONPIN, HIGH);
      triggerPressed = true;
    }
  }
  standardGun.updateAmmoBar();
}

