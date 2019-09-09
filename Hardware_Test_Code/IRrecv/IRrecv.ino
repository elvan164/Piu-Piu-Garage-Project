#include <IRremote.h>

int RECV_PIN = 10;

IRrecv irrecv(RECV_PIN);

decode_results results;
int recv_val;

void setup()
{

  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  pinMode(6, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    recv_val = results.value;
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    delay(50);
  }
  if (recv_val == 0x1100){
    digitalWrite(6, HIGH);
  }else{
    digitalWrite(6, LOW);
  }
}
