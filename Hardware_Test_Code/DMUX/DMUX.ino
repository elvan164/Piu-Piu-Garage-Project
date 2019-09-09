#define C 4
#define B 3
#define A 2

int dmux_input[] =  {C, B, A};
void setup() {
  // put your setup code here, to run once:
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i=0; i<=7; i++){
    ledOutput(i);
    delay(125);
  }
}

void ledOutput(int input){
  for(int i = 2; i>=0; i--){
    int state = bitRead(input, i);
    Serial.print("i : ");
    Serial.println(i);
    Serial.print("State: ");
    Serial.print(state);
    Serial.println();
    if(state == 1){
      digitalWrite(dmux_input[i], HIGH);
    }
    else{
      digitalWrite(dmux_input[i], LOW);
    }
  }
  Serial.println();
}

