#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define triggerPin 2
#define PIN 6
#define NUMPIXELS 14
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int minMana = 0;
int maxMana = 50;
int currentMana = maxMana;

void setup() {
  // put your setup code here, to run once:
  pinMode(triggerPin, INPUT_PULLUP);
  strip.begin();
  strip.show();
  Serial.begin(9600);
  for(int i=0; i<NUMPIXELS; i++){
    strip.setPixelColor(i, strip.Color(150, 150, 0));
    strip.show();
  }
}

void loop() {
  //  test code to display the updateManaBar code
  Serial.println(debounce(triggerPin));
  if(debounce(triggerPin) == HIGH){
    Serial.println("shot");
    updateManaBar(0, NUMPIXELS, currentMana, minMana, maxMana);
    strip.show();
    currentMana--;
  }
}

int debounce(int pin)
{
  int state, previous_state;
  previous_state = digitalRead(pin); 
  // if the state has remained unchanged for 25ms straight, take it as the correct reading
  for(int i = 0; i < 25; i++)
  {
    delay(1);                       
    state = digitalRead(pin);       
    if( state != previous_state)
    {
      i = 0;                  
      previous_state = state;       
    }
  }
  return state;
}

void updateManaBar(int firstManaPixel, int lastManaPixel, int currentMana, int minMana, int maxMana) {
  int numberOfPixels = lastManaPixel - firstManaPixel + 1;
  int numberOfStates = numberOfPixels * 3;
  currentMana = constrain(currentMana, minMana, maxMana);
  int currentState = map(currentMana, minMana, maxMana, 0, numberOfStates);
  int numberOfBlue = map(currentMana, minMana, maxMana, 0, numberOfPixels);
  int colorOfEdge = currentState % 3;

  for (int i = firstManaPixel; i <= lastManaPixel; i++) {
    //Serial.print("Mana pixel number: ");
    //Serial.print(i);
    if (i < firstManaPixel + numberOfBlue) {
      strip.setPixelColor(i, strip.Color(0, 150, 150));
      //Serial.println("light blue");
    }
    else if (i == firstManaPixel + numberOfBlue) {
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
