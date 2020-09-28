#include <QuadDisplay.h>

unsigned long particle_counter = 0;
unsigned long particle_displayed_1 = -1;
unsigned long particle_displayed_2 = -1;
unsigned long particle_start_3 = 0;
unsigned long last_particle_time = 0;
int last_mode = 0;

unsigned long part_times[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
      if((particle_counter != particle_displayed_1) || last_mode != 1)
      {
        displayInt(2, particle_counter);
        particle_displayed_1 = particle_counter;
        for(int i = 0; i < 10; i++)
        {
          Serial.print(part_times[i]);
          Serial.print(" ");
        }
        Serial.println("");
      }
    break;
    case 2:
      if(particle_counter < 11 && last_mode != 2)
      {
        displayDigits(2, QD_MINUS, QD_MINUS, QD_MINUS, QD_MINUS); 
      }
      else if(particle_counter >= 11 && particle_displayed_2 != particle_counter)
      {
        displayFloat(2, double(60000)/(double(part_times[0]+part_times[1]+part_times[2]+part_times[3]+part_times[4])/double(6)), 1);
        particle_displayed_2 = particle_counter;
      }
      if(last_mode != 2)
      {
        displayFloat(2, double(60000)/(double(part_times[0]+part_times[1]+part_times[2]+part_times[3]+part_times[4])/double(6)), 1);
        particle_displayed_2 = particle_counter;
      }
    break;
    case 3:
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
      Serial.print("part");
      Serial.println(particle_counter-particle_start_3);
    break;
  }
  last_mode = mode;
  if(analogRead(A0) > 200)
  {
    particle_counter++;
    delayMicroseconds(5000); 
    if(particle_counter < 11)
    {
      part_times[particle_counter-1] = millis() - last_particle_time;
      last_particle_time = millis();
    }
    else
    {
      part_times[0] = part_times[1];
      part_times[1] = part_times[2];
      part_times[2] = part_times[3];
      part_times[3] = part_times[4];
      part_times[4] = part_times[5];
      part_times[5] = part_times[6];
      part_times[6] = part_times[7];
      part_times[7] = part_times[8];
      part_times[8] = part_times[9];
      part_times[9] = millis() - last_particle_time;
      last_particle_time = millis();
    }
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
