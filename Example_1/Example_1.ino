#include <Wire.h>
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h"
OpenLog myLog; //Create instance
LPS25HB pressureSensor; // Create an object of the LPS25HB class
int ledPin = LED_BUILTIN; //Status LED connected to digital pin 13

const byte OpenLogAddress = 42; //Default Qwiic OpenLog I2C address

void setup()
{
  pinMode(ledPin, OUTPUT);

  Wire.begin();
  myLog.begin(); //Open connection to OpenLog (no pun intended)

  Serial.begin(9600); //9600bps is used for debug statements
  Serial.println("Run OpenLog Append File Test");
  myLog.println("Run OpenLog Append File Test");

  myLog.println("This is recorded to the default log file");
  myLog.append("appendMe.txt");
  myLog.println("This is recorded to appendMe.txt");
  myLog.println("If this file doesn't exist it is created and");
  myLog.println("anything sent to OpenLog will be recorded to this file");

  myLog.println();
  myLog.println(F("Note: We can use the F(\"\") in sketches to move big print statements into program memory to save RAM"));
  myLog.append("appendMe1.txt");
  myLog.println(F("Note: We can use the F(\"\") in sketches to move big print statements into program memory to save RAM"));
  myLog.println(F("Note: We can use the F(\"\") in sketches to move big print statements into program memory to save RAM"));
  myLog.syncFile();

  Serial.println("Done!");
}

void loop() {
 if(pressureSensor.isConnected()==true)
 {
 if(pressureSensor.getStatus()==0x00)
 {
  pressureSensor.begin();
 }
  Serial.print("Pressure (hPa): "); 
  Serial.print(pressureSensor.getPressure_hPa());          // Get the pressure reading in hPa
  Serial.print(", Temperature (degC): "); 
  Serial.println(pressureSensor.getTemperature_degC());    // Get the temperature in degrees C
}
else
{
  Serial.println("Disconnected");
  pressureSensor.begin();
} 

  delay(40);                                               // Wait - 40 ms corresponds to the maximum update rate of the sensor (25 Hz)
}
