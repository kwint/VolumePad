#include <FastCapacitiveSensor.h>
FastCapacitiveSensor sensor1;
double value;
bool finger;
bool state_top = false;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  sensor1.begin(3, A0, 5.0, 10, 15, 0.2);
}

void loop() {
  value = sensor1.touch();
  finger = value > 300.0;
  Serial.print(value);
  Serial.print("\t");
  Serial.println(finger);
  if (finger) {
    move_fader();
  }
  
}

void move_fader() {
  if (state_top){
    digitalWrite(12, LOW);
  } else {
    digitalWrite(13, LOW);
  }
  Serial.println(state_top);
  delay(1000);
  state_top = !state_top;
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

}
