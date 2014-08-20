#include <Wire.h>
#include "Arduino.h"

class PMOTOR
{
  public:
    PMOTOR(int pwm, int d, int b, int dir){
      _pwm = pwm;
      _d = d;
      _b = b;
      pinMode(_pwm,OUTPUT);
      pinMode(_d,OUTPUT);
      pinMode(_b,OUTPUT);

      if(!dir){
        DHIGH = LOW;
        DLOW = HIGH;
      }
      else{
        DHIGH = HIGH;
        DLOW = LOW;
      }
    }
    void move(int input){
      if(input < 0){
        digitalWrite(_b,LOW);
        digitalWrite(_d,DHIGH);		
      }
      else if(input > 0){
        digitalWrite(_b,LOW);
        digitalWrite(_d,DLOW);
      }
      else{
        digitalWrite(_b,HIGH);
      }
      analogWrite(_pwm,abs(input));
    }
  private:
    int _pwm;
    int _d;	
    int _b;
    int DHIGH;
    int DLOW;
};
