#include <QuadDisplay.h>

#define CONVERSION_COEF 1.08
#define FILTER_COEF 0.2

unsigned long particle_counter = 0;
unsigned long particle_displayed = -1;
unsigned long particle_start_3 = 0;
unsigned long last_particle_time = 0;
int last_mode = 0;
bool lock_3_mode = false;

unsigned long part_time_avg = 0;

float expRunningAverage(float newVal) {
  static float filVal = 0;
  filVal += (newVal - filVal) * FILTER_COEF;
  return filVal;
}

void setup()
{
  pinMode(A0, INPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  int mode = check_switch_state();
  switch(mode)
  {
    case 1:
      if(particle_counter != particle_displayed || last_mode != 1)
      {
        displayInt(2, particle_counter);
        particle_displayed = particle_counter;
      }
    break;
    case 2:
      if(particle_counter != particle_displayed || last_mode != 2)
      {
        displayFloat(2, (float(60000)/float(part_time_avg))/float(CONVERSION_COEF), 1);
        particle_displayed = particle_counter;
      }
    break;
    case 3:
      if(!lock_3_mode)
      {
        particle_start_3 = particle_counter;
        for(int timer = 5; timer != 0; timer--)
        {
          Serial.println(timer);
          displayInt(2, timer);
          for(unsigned long i = millis(); millis()-i < 1000;)
          {
            if(analogRead(A0) > 200)
            {
              particle_counter++;
              delay(5);
            }
          }
        }
        displayInt(2, particle_counter-particle_start_3);
        Serial.println(particle_counter-particle_start_3);
        lock_3_mode = true;
      }
    break;
  }
  last_mode = mode;
  if(mode != 3) lock_3_mode = false;
  if(analogRead(A0) > 200)
  {
    particle_counter++;
    delayMicroseconds(5000); 
    part_time_avg = expRunningAverage(millis() - last_particle_time);
    last_particle_time = millis();
  }
}

int check_switch_state()
{
  if(digitalRead(3) == LOW) {
    return 1;
  }
  else if(digitalRead(4) == LOW)
  {
    return 3;
  }
  else
  {
    return 2;
  }
}
