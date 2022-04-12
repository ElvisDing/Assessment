#include <Wire.h>
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h"
#include <Servo.h>


OpenLog myLog; //Create instance
LPS25HB pressureSensor; // Create an object of the LPS25HB class
Servo myservo;  // create servo object to control a servo


int ledPin = LED_BUILTIN; //Status LED connected to digital pin 13   //?
int pos = 0;    // variable to store the servo position
const byte OpenLogAddress = 42; //Default Qwiic OpenLog I2C address

void setup()
{
  pinMode(ledPin, OUTPUT); //?
  pressureSensor.begin();
  Wire.begin();
  myLog.begin(); //Open connection to OpenLog (no pun intended)

  Serial.begin(9600); //9600bps is used for debug statements
  myLog.create("Elvis.txt");
  myLog.append("Elvis.txt");

  myLog.syncFile();

  Serial.println("Done!");  //?
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object   //?
}

void loop() {
  if (pressureSensor.isConnected() == true)
  {
    if (pressureSensor.getStatus() == 0x00).
0000000
  {
    Serial.println("Error with pressureSensor");
    pressureSensor.begin();
  }
  delay(40);                                               // Wait - 40 ms corresponds to the maximum update rate of the sensor (25 Hz)
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
}
