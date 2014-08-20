#include <Wire.h>
#include "pwmMotor.cpp"

PMOTOR MOTORA(3,4,5,0); //Motor A pins (PWM BRK DIR)
PMOTOR MOTORB(6,7,8,0); //Motor B pins (PWM BRK DIR)
PMOTOR MOTORC(9,10,11,0); //Motor C pins (PWM BRK DIR)

int  speeds[][3]= { //Motor Speed Array
{-255, 0, 255},
{-108, -128, 255},
{25, -244, 255},
{146, -255, 146},
{255, -244, 25},
{255, -128, -108},
{255, 0, -255},
{108, 128, -255},
{-25, 244, -255},
{-146, 255, -146},
{-255, 244, -25},
{-255, 128, 108}
};

int solenoidPin = 2; //The Pin the solenoid is connected to 

int sonarLeft
int sonarRight

int irDirection;
int dir;

int compTarget;
int compRelative(int heading) //Function to calculate relative compass heading
{
  int diff = heading - compTarget + 180;
  diff = (diff >= 0 ? diff % 360 : 359 - (-1 - diff) % 360) - 180;
  return constrain(diff, -180, 180);
}

char lcdString[17];

void setup()
{
  Wire.requestFrom(0xC0, 1);
  if (Wire.available())
  {
    compTarget = Wire.read();
  }
  lcdString[16]=0;
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);
}

void loop()
{
  Wire.requestFrom(0xC0, 1);
  if Wire.available())
  {
    heading = Wire.read();
  }
  Wire.requestFrom(0x50, 1);
  if (Wire.available())
  {
    Serial.println(Wire.read(), DEC);
    irDirection = Wire.read();
    dir = irDirection*30;
    if (dir = 360)
    {
      dir = 0;
    }
    MOTORA.move(speeds[dir][0]);
    MOTORB.move(speeds[dir][1]);
    MOTORC.move(speeds[dir][2]);
  }
}
