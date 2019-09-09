#include <IR_Comms.h>
#include <IRremote.h>

IRsend irsend;
IR_Comms irComms(1,1);
int sentCode;
int recvCode = 0x4412;
int shotInfo[4];

void setup()
{
  Serial.begin(9600);
  sentCode = irComms.encrypt();

  int* shotInfoPointer = irComms.decrypt(recvCode);

  shotInfo[4] = *shotInfoPointer;

  Serial.println(shotInfo[0],HEX);
  Serial.println(shotInfo[1],HEX);
  Serial.println(shotInfo[2],HEX);
  Serial.println(shotInfo[3],HEX);
  
}


void loop() 
{
  //Serial.println(sentCode, HEX);
  //irsend.sendSony(sentCode, 16);
  delay(25);  
}
