#include "pwmMotor.cpp"

PMOTOR MOTORA(3,4,5,0);
PMOTOR MOTORB(6,7,8,0);
PMOTOR MOTORC(9,10,11,0);

void setup(){
  pinMode(2, OUTPUT);
}
void loop(){ 
  while(1==1)
  {
     MOTORA.move(-255);
     MOTORB.move(0);
     MOTORC.move(255);
  } 
}
