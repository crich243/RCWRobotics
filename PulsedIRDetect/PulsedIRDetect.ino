/*  I2C DOCUMENTATION:
  DEFAULT ADDRESS: 0xA0 (8-bit), 0x50 (7-bit)
*/
#include <Wire.h>

// * the maximum value (used to average readings)
// * the greater, the more accurate and slow (max = 255)
#define MAX_COUNTER 128

// * more than this needs to change to support other than 12 diodes
// * including the size of the arrays below.
#define SENSORS 12

// * the power pin
#define UNLOCK_PIN 2

// * i2c address (8-bit)
#define ADDRESS_8 0xA0
#define ADDRESS_7 0x50

// * the best IR sensor currently (0 is no sensor)
byte IR_SENSOR;

// * the number of loops (always less than MAX_COUNTER)
byte counter;

// * the current values for each sensor (0 to MAX_COUNTER)
byte values[SENSORS];

// * sensor to pin mapping
// * if a sensor is broken set it to 255
                //SENSOR: 1  2  3  4  5   6   7   8   9  10  11 12
byte sensors[SENSORS] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0};

/**
  Receives an I2C read request and sends back the best sensor.
*/
void i2c_request() {
  Wire.write(IR_SENSOR);
}

void setup() {
  /* Initialize I2C */
  Wire.begin(ADDRESS_7);
  Wire.onRequest(i2c_request);
  
  // for debug stuff
  Serial.begin(9600);
  
  /* Initialize the diodes and LET THERE BE POWER */
  pinMode(UNLOCK_PIN, OUTPUT);
  digitalWrite(UNLOCK_PIN, HIGH);
  for (byte i = 0;i < SENSORS;i++) {
    pinMode(sensors[i], INPUT);
  } 
}

void loop() {
  /* Read the sensors and get the current reading */
  for (byte i = 0;i < SENSORS;i++) {
    if (sensors[i] != 255) {
      values[i] += (digitalRead(sensors[i]) == HIGH ? 0 : 1); 
    }
  }
  
  counter++;
  
  /* If finished a block, calculate the best. */
  if (counter >= MAX_COUNTER) {
    counter = 0;
    
    // * the index of the best sensor
    byte b_index = 0;
    
    
    // * the reading of the best sensor
    byte b_value = 0;
    
    for (byte i = 0;i < SENSORS;i++) {
      if (values[i] > b_value) {
        b_index = i + 1; // diode 1, 2, etc 
        b_value = values[i];
      }

      /* debug stuff - disable in competition as it slows it down
      Serial.print(i + 1, DEC);
      Serial.print("=");
      Serial.print(values[i], DEC);
      Serial.print(" ");
      */
      
      values[i] = 0;
    }
    
    IR_SENSOR   = b_index;

    counter = 0; // a bug in Arduino can mean counter not reset above (why?)
   
   	// reset all sensors by dropping power for 1ms
    digitalWrite(UNLOCK_PIN, LOW);
    delay(1);
    digitalWrite(UNLOCK_PIN, HIGH);
    
    
    /* more debug
    Serial.print("BEST=");
    Serial.print(b_index, DEC);
    Serial.print(" (");
    Serial.print(sensors[b_index-1], DEC);
    Serial.print("): ");
    Serial.println(b_value, DEC);
    */
  }
}
