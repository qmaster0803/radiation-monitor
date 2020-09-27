void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  int sensorVal1 = digitalRead(3);
  int sensorVal2 = digitalRead(4);
  if (sensorVal1 == LOW) {
    Serial.println(1);
  }
  else if(sensorVal2 == LOW)
  {
    Serial.println(3);
  }
  else
  {
    Serial.println(2);
  }
}
