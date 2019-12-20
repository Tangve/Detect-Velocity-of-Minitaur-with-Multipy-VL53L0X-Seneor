/* This example shows how to get single-shot range
 measurements from the VL53L0X. The sensor can optionally be
 configured with different ranging profiles, as described in
 the VL53L0X API user manual, to get better performance for
 a certain application. This code is based on the four
 "SingleRanging" examples in the VL53L0X API.

 The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

VL53L0X sensor1,sensor2,sensor3,sensor4,sensor5,sensor6,sensor7,sensor8;

//parameter
float a=0.5;

float dis1c,dis2c,dis3c,dis4c,dis5c,dis6c,dis7c,dis8c,dis1,dis2,dis3,dis4;

float v1,v2,v3,v4;

float yp1,yp2,yp3,yp4;

float yc1,yc2,yc3,yc4;



// Uncomment this line to use long range mode. This
// increases the sensitivity of the sensor and extends its
// potential range, but increases the likelihood of getting
// an inaccurate reading because of reflections from objects
// other than the intended target. It works best in dark
// conditions.

//#define LONG_RANGE


// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

#define HIGH_SPEED
//#define HIGH_ACCURACY


void setup()
{
  Serial.begin(9600);
  Wire.begin();

  //set analog pin
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  
  pinMode(0, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  

  //reset
  digitalWrite(0,LOW);
  digitalWrite(7,LOW);
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
  digitalWrite(10,LOW);
  digitalWrite(8,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  delay(10);
  
  digitalWrite(0,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);

  //set 1 address
  digitalWrite(7,LOW);
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
  digitalWrite(10,LOW);
  digitalWrite(8,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  lox.begin(0x39);// put any address between 0x29 to 0x7F 

  //set 2 address
  digitalWrite(7,HIGH);
  lox.begin(0x40);

  //set 3 address
  digitalWrite(2,HIGH);
  lox.begin(0x31);

  //set 4 address
  digitalWrite(4,HIGH);
  lox.begin(0x41);

  digitalWrite(10,HIGH);
  lox.begin(0x32);

  digitalWrite(8,HIGH);
  lox.begin(0x42);

  digitalWrite(12,HIGH);
  lox.begin(0x33);

  digitalWrite(13,HIGH);
  lox.begin(0x43);

  //initial
  sensor1.setAddress(0x39);
  sensor2.setAddress(0x40);
  sensor3.setAddress(0x31);
  sensor4.setAddress(0x41);
  sensor5.setAddress(0x32);
  sensor6.setAddress(0x42);
  sensor7.setAddress(0x33);
  sensor8.setAddress(0x43);

  sensor1.init();
  sensor2.init();
  sensor3.init();
  sensor4.init();
  sensor5.init();
  sensor6.init();
  sensor7.init();
  sensor8.init();
  
  sensor1.setTimeout(500);
  sensor2.setTimeout(500);
  sensor3.setTimeout(500);
  sensor4.setTimeout(500);
  sensor5.setTimeout(500);
  sensor6.setTimeout(500);
  sensor7.setTimeout(500);
  sensor8.setTimeout(500);
  
#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor1.setMeasurementTimingBudget(20000);
  sensor2.setMeasurementTimingBudget(20000);
  sensor3.setMeasurementTimingBudget(20000);
  sensor4.setMeasurementTimingBudget(20000);
  sensor5.setMeasurementTimingBudget(20000);
  sensor6.setMeasurementTimingBudget(20000);
  sensor7.setMeasurementTimingBudget(20000);
  sensor8.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
}

void loop()
{
  dis1c=sensor1.readRangeSingleMillimeters();
  dis2c=sensor2.readRangeSingleMillimeters();
  dis3c=sensor3.readRangeSingleMillimeters();
  dis4c=sensor4.readRangeSingleMillimeters();
  dis5c=sensor5.readRangeSingleMillimeters();
  dis6c=sensor6.readRangeSingleMillimeters();
  dis7c=sensor7.readRangeSingleMillimeters();
  dis8c=sensor8.readRangeSingleMillimeters();

  dis1=(dis1c+dis2c)/2;
  dis2=(dis3c+dis4c)/2;
  dis3=(dis5c+dis6c)/2;
  dis4=(dis7c+dis8c)/2;
  

  yc1=a*dis1+(1-a)*yp1;
  yc2=a*dis2+(1-a)*yp2;
  yc3=a*dis3+(1-a)*yp3;
  yc4=a*dis4+(1-a)*yp4;

  v1=(yc1-yp1)/20;
  v2=(yc2-yp2)/20;
  v3=(yc3-yp3)/20;
  v4=(yc4-yp4)/20;
  
  
  //Serial.print(yc1,2);
  //Serial.print('\t');
  //Serial.print(yc2,2);
  //Serial.print('\t');
  //Serial.print(yc3,2);
  //Serial.print('\t');
  //Serial.print(yc4,2); 
  Serial.print(dis1c,2);
  Serial.print('\t');
  Serial.print(dis2c,2);
  Serial.print('\t');
  Serial.print(dis3c,2);
  Serial.print('\t');
  Serial.print(dis4c,2);
  Serial.print('\t');
  Serial.print(dis5c,2);
  Serial.print('\t');
  Serial.print(dis6c,2);
  Serial.print('\t');
  Serial.print(dis7c,2);
  Serial.print('\t');
  Serial.print(dis8c,2);

  analogWrite(3,255*(v1+1.5)/3);
  analogWrite(5,255*(v2+1.5)/3);
  analogWrite(6,255*(v3+1.5)/3);
  analogWrite(9,255*(v4+1.5)/3);
  
  if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  if (sensor3.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  if (sensor4.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  if (sensor5.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  if (sensor6.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  if (sensor7.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  if (sensor8.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  
  Serial.println();

  yp1=yc1;
  yp2=yc2;
  yp3=yc3;
  yp4=yc4;
}
