#include <QuadDisplay.h>

unsigned long particle_counter = 0;
unsigned long particle_displayed = -1;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop()
{
  if(analogRead(A0) > 200)
  {
    particle_counter++;
    delayMicroseconds(5000); 
  }
  if(particle_counter != particle_displayed)
  {
    displayInt(2, particle_counter);
    particle_displayed = particle_counter;
  }
}

int check_switch_state()
{
  if(digitalRead(3) == LOW) {
    Serial.println(1);
  }
  else if(digitalRead(4) == LOW)
  {
    Serial.println(3);
  }
  else
  {
    Serial.println(2);
  }
}
